#include "GameScreenGameover.h"
#include <iostream>
#include "Texture2D.h"

GameScreenGameover::GameScreenGameover(SDL_Renderer* renderer) : GameScreen(renderer)
{
	Mix_HaltMusic();
	mBackgroundTexture = NULL;
	mGameoverSFX.Load("Audio/gameover.wav");
	SetUpLevel();
	mGameoverSFX.Play();
}

GameScreenGameover::~GameScreenGameover()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenGameover::Update(float deltaTime, SDL_Event e)
{
}

void GameScreenGameover::Render()
{
	// Draw the background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

bool GameScreenGameover::SetUpLevel()
{
	// Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundOVER.png"))
	{
		cout << "Failed to load background texture.";
		return false;
	}
	else
		return true;

}