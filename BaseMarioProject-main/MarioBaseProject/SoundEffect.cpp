#include "SoundEffect.h"

SoundEffect* SoundEffect::m_instance = nullptr;

SoundEffect* SoundEffect::Instance()
{
	if(!m_instance)
	{
		m_instance = new SoundEffect;
	}
	return m_instance;
}

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(g_soundEffect);
	g_soundEffect = nullptr;
}

void SoundEffect::Play(std::string filePath, bool isLooping)
{
	Load(filePath);

	if (isLooping)
	{
		Mix_PlayChannel(-1, g_soundEffect, -1);
	}
	else
	{
		Mix_PlayChannel(-1, g_soundEffect, 0);
	}
}

void SoundEffect::Load(std::string filePath)
{
	g_soundEffect = Mix_LoadWAV(filePath.c_str());
	if (g_soundEffect == nullptr)
	{
		cout << "Failed to load music. Error: " << Mix_GetError() << endl;
	}
}