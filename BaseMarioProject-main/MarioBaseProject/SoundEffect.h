#pragma once
#ifndef _SOUNDEFFECT_H
#define _SOUNDEFFECT_H

#include <SDL.h>
#include <string>
#include <iostream>
#include <SDL_mixer.h>

using namespace std;


class SoundEffect
{
public:
	static SoundEffect* Instance();
	~SoundEffect();


	void Play(string filePath, bool isLooping);
	void Load(string filePath);

private:
	Mix_Chunk* g_soundEffect = nullptr;
	static SoundEffect* m_instance;

protected:


};

#endif // !_SOUNDEFFECT_H