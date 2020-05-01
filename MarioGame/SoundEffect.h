#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>

class SoundEffect
{
private:
	int _channel;
	Mix_Chunk* _sfx;
public:
	SoundEffect();
	~SoundEffect();
	void Load(std::string path);
	void Play();
};