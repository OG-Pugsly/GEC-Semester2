#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Character.h"
#include "Collisions.h"



GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
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
}

void GameScreenLevel1::Render()
{
	//Draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//Update Character
	mario_character->Render();
	luigi_character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Update Character
	mario_character->Update(deltaTime, e);
	luigi_character->Update(deltaTime, e);

	//Collision detection
	if (Collisions::Instance()->Circle(mario_character->GetPosition(), mario_character->GetCollisionRadius(), luigi_character->GetPosition(), luigi_character->GetCollisionRadius()))
	{
		//cout << "Circle Hit!" << endl;
	}

	if (Collisions::Instance()->Box(mario_character->GetCollisionBox(), luigi_character->GetCollisionBox()))
	{
		cout << "Box Hit!" << endl;
	}

}

bool GameScreenLevel1::SetUpLevel()
{
	//Load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	//Set up Player Character
	mario_character = new CharacterMario(m_renderer, "Images/Sprites/Mario.png", Vector2D(64, 330));
	luigi_character = new CharacterLuigi(m_renderer, "Images/Sprites/Luigi.png", Vector2D(128, 330));
}
