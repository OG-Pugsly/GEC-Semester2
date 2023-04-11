#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Character.h"
#include "Collisions.h"
#include "PowBlock.h"



GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;

	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete mario_character;
	mario_character = nullptr;

	delete luigi_character;
	luigi_character = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;
}

void GameScreenLevel1::Render()
{
	//Draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//Update Character
	mario_character->Render();
	luigi_character->Render();

	//Update Pow Blocks
	m_pow_block->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Do the Screen shake if required
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//End shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}


	//Update Character
	mario_character->Update(deltaTime, e);
	luigi_character->Update(deltaTime, e);

	//Circle collision detection
	if (Collisions::Instance()->Circle(mario_character->GetPosition(), mario_character->GetCollisionRadius(), luigi_character->GetPosition(), luigi_character->GetCollisionRadius()))
	{

	}
	
	//Box collision detection
	if (Collisions::Instance()->Box(mario_character->GetCollisionBox(), luigi_character->GetCollisionBox()))
	{
		
	}

	//Update Pow block
	UpdatePowBlock();
}

bool GameScreenLevel1::SetUpLevel()
{

	//Load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Backgrounds/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	SetLevelMap();

	//Set up Player Character
	mario_character = new CharacterMario(m_renderer, "Images/Sprites/Mario.png", Vector2D(64, 330), m_level_map);
	luigi_character = new CharacterLuigi(m_renderer, "Images/Sprites/Luigi.png", Vector2D(128, 330), m_level_map);

	
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{ 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	//Clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//Set the new one
	m_level_map = new LevelMap(map);

	//Initialise Pow block
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	//Initialise Screen shake variables
	m_screenshake = false;
	m_background_yPos = 0.0f;

}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(mario_character->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//Collided with Pow block while jumping
			if (mario_character->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				mario_character->CancelJump();
			}
		}
	}

	if (Collisions::Instance()->Box(luigi_character->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//Collided with Pow block while jumping
			if (luigi_character->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				luigi_character->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}
