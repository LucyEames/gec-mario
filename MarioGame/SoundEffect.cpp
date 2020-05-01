#include "SoundEffect.h"

SoundEffect::SoundEffect()
{
	_sfx = NULL;
	_channel = -1;
}

SoundEffect::~SoundEffect()
{
	Mix_HaltChannel(_channel);
	delete _sfx;
}

void SoundEffect::Load(std::string path)
{
	_sfx = Mix_LoadWAV(path.c_str());
}

void SoundEffect::Play()
{
	Mix_PlayChannel(_channel, _sfx, 0);
}