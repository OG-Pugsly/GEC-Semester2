#pragma once
#ifndef _CHARACTERCOIN_H
#define _CHARACTERCOIN_H

#include "Character.h"

class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing);
	~CharacterCoin();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	bool m_collected;
	float m_single_sprite_w;
	float m_single_sprite_h;
	FACING m_facing_direction;
	float m_frame_delay;
	int m_current_frame;

protected:


};

#endif // !_CHARACTERCOIN_H