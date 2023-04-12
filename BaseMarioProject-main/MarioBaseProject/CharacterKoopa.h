#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	bool GetInjured() { return m_injured; }
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void FlipRightWay();

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_movement_speed;
	FACING m_facing_direction;
	bool m_injured;
	float m_injured_time;

	

protected:


};

#endif // !_CHARACTERKOOPA_H