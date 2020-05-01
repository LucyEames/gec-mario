#pragma once
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "SoundEffect.h"

class Texture2D;

class GameScreenGameover : GameScreen
{
private:
	// Variables
	Texture2D* mBackgroundTexture;
	SoundEffect mGameoverSFX;
public:
	GameScreenGameover(SDL_Renderer* renderer);
	~GameScreenGameover();

	// Prototypes
	void Render();
	void Update(float deltaTime, SDL_Event e);
	bool SetUpLevel();
};

