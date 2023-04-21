#pragma once
#ifndef _CHARACTERGOOMBA_H
#define _CHARACTERGOOMBA_H

#include "Character.h"

class CharacterGoomba : public Character
{
public:
	CharacterGoomba(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterGoomba();
	void TakeDamage();
	void Jump();
	bool GetInjured() { return m_injured; }
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void FlipRightWay();
	float timeSinceFlip = KOOPA_FLIP_TIME_DELAY;

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_movement_speed;
	FACING m_facing_direction;
	bool m_injured;
	float m_injured_time;
	float m_frame_delay;
	int m_current_frame;

protected:


};

#endif // !_CHARACTERGOOMBA_H