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

	for (int enemy = 0; enemy < m_koopas.size(); enemy++)
	{
		delete m_koopas[enemy];
	}
	m_koopas.clear();

	for (int coin = 0; coin < m_coins.size(); coin++)
	{
		delete m_coins[coin];
	}
	m_coins.clear();
}

void GameScreenLevel1::Render()
{
	//Draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//Draw the Koopas
	for (int enemy = 0; enemy < m_koopas.size(); enemy++)
	{
		m_koopas[enemy]->Render();
	}

	//Draw the Goombas
	for (int enemy = 0; enemy < m_goombas.size(); enemy++)
	{
		m_goombas[enemy]->Render();
	}

	//Draw the coins
	for (int coin = 0; coin < m_coins.size(); coin++)
	{
		m_coins[coin]->Render();
	}

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

	//Update Koopa Spawn Timer
	m_koopa_spawn_timer -= deltaTime;
	if (m_koopa_spawn_timer <= 0.0f)
	{
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		m_koopa_spawn_timer = KOOPA_SPAWN_TIMER;
	}

	//Update Enemy Spawn Timer
	m_enemy_spawn_timer -= deltaTime;
	if (m_enemy_spawn_timer <= 0.0f)
	{
		if (m_enemy_spawn_count % 5 == 0)
		{
			CreateGoomba(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		}
		else
		{
			CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		}
		m_enemy_spawn_timer = ENEMY_SPAWN_TIMER;
	}

	//Update Enemies
	UpdateEnemies(deltaTime, e);

	//Update Coins
	UpdateCoins(deltaTime, e);
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

	//Add Koopa enemies
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);	

	//Initialise Enemy spawn timer
	m_enemy_spawn_timer = ENEMY_SPAWN_TIMER;

	//Initialise Koopa Spawn Timer
	m_koopa_spawn_timer = KOOPA_SPAWN_TIMER;

	//Set up Coins
	CreateCoin(Vector2D(200, 130), FACING_LEFT);
	CreateCoin(Vector2D(150, 130), FACING_LEFT);
	CreateCoin(Vector2D(250, 130), FACING_LEFT);
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

	for (unsigned int enemy = 0; enemy < m_koopas.size(); enemy++)
	{
		m_koopas[enemy]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_koopas.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int enemy = 0; enemy < m_koopas.size(); enemy++)
		{
			m_koopas[enemy]->timeSinceFlip += deltaTime;

			//Check if enemy is on the bottom row of tiles
			if (m_koopas[enemy]->GetPosition().y < 355.0f)
			{
				//Is the enemy off screen to the left or right?
				if (m_koopas[enemy]->GetPosition().x < 0.0f || m_koopas[enemy]->GetPosition().x > SCREEN_WIDTH - (float)(m_koopas[enemy]->GetCollisionBox().width * 0.55f))
				{
					if (m_koopas[enemy]->timeSinceFlip >= KOOPA_FLIP_TIME_DELAY)
					{
						m_koopas[enemy]->timeSinceFlip = 0.0f;
						m_koopas[enemy]->FlipRightWay();
					}
				}
			}

			//Now do the update
			m_koopas[enemy]->Update(deltaTime, e);

			//Check to see if the enemy collides with player
			if ((m_koopas[enemy]->GetPosition().y > 300.0f || m_koopas[enemy]->GetPosition().y <= 64.0f) && (m_koopas[enemy]->GetPosition().x < 64.0f || m_koopas[enemy]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//Ignore Collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_koopas[enemy]->GetPosition(), m_koopas[enemy]->GetCollisionRadius(), mario_character->GetPosition(), mario_character->GetCollisionRadius()))
				{
					if (m_koopas[enemy]->GetInjured())
					{
						m_koopas[enemy]->SetAlive(false);
					}
					else
					{
						//Kill Mario
					}
				}

				if (Collisions::Instance()->Circle(m_koopas[enemy]->GetPosition(), m_koopas[enemy]->GetCollisionRadius(), luigi_character->GetPosition(), luigi_character->GetCollisionRadius()))
				{
					if (m_koopas[enemy]->GetInjured())
					{
						m_koopas[enemy]->SetAlive(false);
					}
					else
					{
						//Kill Luigi
					}
				}
			}

			//If the enemy is no longer alive then schedule it for deletion
			if (!m_koopas[enemy]->GetAlive())
			{
				enemyIndexToDelete = enemy;
			}
		}

		//Remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_koopas.erase(m_koopas.begin() + enemyIndexToDelete);
		}
	}

	if (!m_goombas.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int enemy = 0; enemy < m_goombas.size(); enemy++)
		{
			m_goombas[enemy]->timeSinceFlip += deltaTime;

			//Check if enemy is on the bottom row of tiles
			if (m_goombas[enemy]->GetPosition().y < 355.0f)
			{
				//Is the enemy off screen to the left or right?
				if (m_goombas[enemy]->GetPosition().x < 0.0f || m_goombas[enemy]->GetPosition().x > SCREEN_WIDTH - (float)(m_goombas[enemy]->GetCollisionBox().width * 0.55f))
				{
					if (m_goombas[enemy]->timeSinceFlip >= KOOPA_FLIP_TIME_DELAY)
					{
						m_goombas[enemy]->timeSinceFlip = 0.0f;
						m_goombas[enemy]->FlipRightWay();
					}
				}
			}

			//Now do the update
			m_goombas[enemy]->Update(deltaTime, e);

			//Check to see if the enemy collides with player
			if ((m_goombas[enemy]->GetPosition().y > 300.0f || m_goombas[enemy]->GetPosition().y <= 64.0f) && (m_goombas[enemy]->GetPosition().x < 64.0f || m_goombas[enemy]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//Ignore Collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_goombas[enemy]->GetPosition(), m_goombas[enemy]->GetCollisionRadius(), mario_character->GetPosition(), mario_character->GetCollisionRadius()))
				{
					if (m_goombas[enemy]->GetInjured())
					{
						m_goombas[enemy]->SetAlive(false);
					}
					else
					{
						//Kill Mario
					}
				}

				if (Collisions::Instance()->Circle(m_goombas[enemy]->GetPosition(), m_goombas[enemy]->GetCollisionRadius(), luigi_character->GetPosition(), luigi_character->GetCollisionRadius()))
				{
					if (m_goombas[enemy]->GetInjured())
					{
						m_goombas[enemy]->SetAlive(false);
					}
					else
					{
						//Kill Luigi
					}
				}
			}

			//If the enemy is no longer alive then schedule it for deletion
			if (!m_goombas[enemy]->GetAlive())
			{
				enemyIndexToDelete = enemy;
			}
		}

		//Remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_goombas.erase(m_goombas.begin() + enemyIndexToDelete);
		}
	}

}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int coin = 0; coin < m_coins.size(); coin++)
		{
			//Now do the update
			m_coins[coin]->Update(deltaTime, e);

			//Check to see if the coin collides with player
			if ((m_coins[coin]->GetPosition().y > 300.0f || m_coins[coin]->GetPosition().y <= 64.0f) && (m_coins[coin]->GetPosition().x < 64.0f || m_coins[coin]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//Ignore Collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_coins[coin]->GetPosition(), m_coins[coin]->GetCollisionRadius(), mario_character->GetPosition(), mario_character->GetCollisionRadius()))
				{
					m_coins[coin]->SetAlive(false);
					mario_character->AddToScore(1);
				}

				if (Collisions::Instance()->Circle(m_coins[coin]->GetPosition(), m_coins[coin]->GetCollisionRadius(), luigi_character->GetPosition(), luigi_character->GetCollisionRadius()))
				{
					m_coins[coin]->SetAlive(false);
					luigi_character->AddToScore(1);
				}
			}

			//If the coin is collected then schedule it for deletion
			if (!m_coins[coin]->GetAlive())
			{
				coinIndexToDelete = coin;
			}
		}

		//Remove coin -1 each update
		if (coinIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	//Set up Koopa Character
	CharacterKoopa* koopa = new CharacterKoopa(m_renderer, "Images/Sprites/Koopa.png", position, m_level_map, direction, speed);
	m_koopas.push_back(koopa);
	m_enemy_spawn_count += 1;
}

void GameScreenLevel1::CreateGoomba(Vector2D position, FACING direction, float speed)
{
	//Set up Koopa Character
	CharacterGoomba* goomba = new CharacterGoomba(m_renderer, "Images/Sprites/Goomba.png", position, m_level_map, direction, speed);
	m_goombas.push_back(goomba);
	m_enemy_spawn_count += 1;
}

void GameScreenLevel1::CreateCoin(Vector2D position, FACING direction)
{
	//Set up Koopa Character
	CharacterCoin* coin = new CharacterCoin(m_renderer, "Images/Sprites/Coin.png", position, m_level_map, direction);
	m_coins.push_back(coin);
}
