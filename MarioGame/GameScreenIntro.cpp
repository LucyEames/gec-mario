#include "GameScreenIntro.h"
#include <iostream>
#include "Texture2D.h"

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mBackgroundTexture = NULL;
	SetUpLevel();
}


GameScreenIntro::~GameScreenIntro()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
}

void GameScreenIntro::Render()
{
	// Draw the background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

bool GameScreenIntro::SetUpLevel()
{
	// Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/title.png"))
	{
		cout << "Failed to load background texture.";
		return false;
	}
	else
		return true;
}