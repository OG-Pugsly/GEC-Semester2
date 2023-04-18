#include "CharacterCoin.h"


CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing) : Character(renderer, imagePath, start_position, start_facing, map)
{
	m_facing_direction = start_facing;
	m_position = start_position;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();

	m_collected = false;
}

CharacterCoin::~CharacterCoin()
{

}

void CharacterCoin::Render()
{
	//Get the portion of the sprite sheet you want to draw
	// {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };

	//Determine where you want it to be drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//Draw the coin	
	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		//Reset fram delay count
		m_frame_delay = COIN_ANIMATION_DELAY;

		//Move to next frame
		m_current_frame++;

		//Loop frame to first if it goes beyond maximum number of frames
		if (m_current_frame > 2)
		{
			m_current_frame = 0;
		}


	}
}