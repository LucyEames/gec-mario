#pragma once
#include <SDL.h>

class GameScreen
{
protected:
	// Variables
	SDL_Renderer* mRenderer;
	bool mGameOver;

public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	// Prototypes
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual bool IsGameOver() { return mGameOver; }
};