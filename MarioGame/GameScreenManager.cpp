#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenGameover.h"
#include "GameScreenIntro.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;

	// Ensure the first screen is set up
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
	if (mCurrentScreen->IsGameOver())
	{
		ChangeScreen(SCREEN_GAMEOVER);
	}
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	// Clear up the old screen
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	// Pointers
	GameScreenIntro* tempScreenIntro;
	GameScreenLevel1* tempScreen1;
	GameScreenGameover* tempScreenGameover;

	switch (newScreen)
	{
	case SCREEN_INTRO:
		tempScreenIntro = new GameScreenIntro(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenIntro;
		tempScreenIntro = NULL;
	break;
	case SCREEN_LEVEL1:
		tempScreen1 = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen1;
		tempScreen1 = NULL;
	break;
	case SCREEN_GAMEOVER:
		tempScreenGameover = new GameScreenGameover(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenGameover;
		tempScreenGameover = NULL;
	}
}