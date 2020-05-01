#pragma once
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"

class Texture2D;

class GameScreenIntro : GameScreen
{
private:
	// Variables
	Texture2D* mBackgroundTexture;
public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();

	// Prototypes
	void Render();
	void Update(float deltaTime, SDL_Event e);
	bool SetUpLevel();
};

