#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include <vector>
#include "CharacterKoopa.h"
#include "CharacterGoomba.h"
#include "CharacterCoin.h"

class Texture2D;
//class CharacterMario;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float delta, SDL_Event e) override;
	void UpdatePowBlock();

private:
	Texture2D* m_background_texture;
	CharacterMario* mario_character;
	CharacterLuigi* luigi_character;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	vector<CharacterKoopa*> m_koopas;
	vector<CharacterGoomba*> m_goombas;
	float m_enemy_spawn_timer;
	float m_koopa_spawn_timer;
	int m_enemy_spawn_count;
	vector<CharacterCoin*> m_coins;

	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenShake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateGoomba(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position, FACING direction);

protected:


};

#endif // _GAMESCREENLEVEL1_H