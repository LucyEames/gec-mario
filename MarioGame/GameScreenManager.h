#pragma once
#include <SDL.h>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
private:
	// Variables
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	// Prototypes
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void ChangeScreen(SCREENS newScreen);
};