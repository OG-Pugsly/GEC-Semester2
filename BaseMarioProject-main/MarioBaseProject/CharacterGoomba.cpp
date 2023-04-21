#include "CharacterGoomba.h"

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, start_facing, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth();
	m_single_sprite_h = m_texture->GetHeight() / 2;

	m_sprite_sheet_rows = 2;
}

CharacterGoomba::~CharacterGoomba()
{

}

void CharacterGoomba::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();

}

void CharacterGoomba::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

void CharacterGoomba::FlipRightWay()
{
	if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction = FACING_RIGHT;
	}
	else
	{
		m_facing_direction = FACING_LEFT;
	}
	m_injured = false;
	Jump();
}

void CharacterGoomba::Render()
{
	//Get the portion of the sprite sheet you want to draw
	// {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect portion_of_sprite = { 0, m_single_sprite_h * m_current_frame, m_single_sprite_w, m_single_sprite_h };

	//Determine where you want it to be drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//Draw the coin	
	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);

	//Draw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}

}

void CharacterGoomba::Update(float deltaTime, SDL_Event e)
{

	//Use the code in the base class
	Character::Update(deltaTime, e);

	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		//Reset fram delay count
		m_frame_delay = COIN_ANIMATION_DELAY;

		//Move to next frame
		m_current_frame++;

		//Loop frame to first if it goes beyond maximum number of frames
		if (m_current_frame > 1)
		{
			m_current_frame = 0;
		}
	}

	if ((m_facing_direction == FACING_LEFT))
	{
		m_moving_left = true;
		m_moving_right = false;
	}
	else if (m_facing_direction == FACING_RIGHT)
	{
		m_moving_right = true;
		m_moving_left = false;
	}
}
