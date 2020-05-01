#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"

using namespace::std;

// Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;
Mix_Music* gMusic = NULL;
bool gGameOver = false;

// Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(string path);

int main(int argc, char* args[])
{
	InitSDL();
	gameScreenManager = new GameScreenManager(gRenderer, SCREEN_INTRO);
	gOldTime = SDL_GetTicks();
	bool quit = false;

	// Game Loop
	while (!quit)
	{
		Render();
		quit = Update();
	}
	
	// Close Window and free resources
	CloseSDL();

	return 0;
}

bool InitSDL()
{
	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		// All good, so attempt to create the window
		gWindow = SDL_CreateWindow("Games Engine Creation - Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		// Did the window get created?
		if (gWindow == NULL)
		{
			// Nope
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer != NULL)
		{
			// Initialise PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		// Initialise the Mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mix could not initialise. Error: " << Mix_GetError();
			return false;
		}
		
		LoadMusic("Audio/Hammer Brothers.mp3");
	}
	return true;
}

void CloseSDL()
{
	// Release the window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Destroy the game screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;

	// Release the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	// Release music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	SDL_Event e;
	SDL_PollEvent(&e);
	Uint32 newTime = SDL_GetTicks();

	// Handle any events
	switch (e.type)
	{
		// Click the 'X' to quit
		case SDL_QUIT:
			return true;
		break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
				// Click the Q key to quit
				case SDLK_q:
					return true;
				break;
				case SDLK_RETURN:
					gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
					if (Mix_PlayingMusic() == 0)
					{
						Mix_PlayMusic(gMusic, -1);
					}
				break;
			}
		break;
	}
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);

	// Set the current time to be the old time
	gOldTime = newTime;

	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();

	SDL_RenderPresent(gRenderer);
}

void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());
	if (gMusic == NULL)
	{
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}
}