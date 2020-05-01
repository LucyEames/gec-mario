#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>
#include <string>
using namespace::std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mTexture = NULL;

	mWidth = 0;
	mHeight = 0;
}
Texture2D::~Texture2D()
{
	Free();

	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(string path)
{
	// Remove the memory used for a previous texture
	Free();

	mTexture = NULL;

	// Load the image
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		// Colour key the image - the colour to be transparent
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		
		// Create the texture from the pixels on the surface
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		else
		{
			// Set dimensions
			mWidth = pSurface->w;
			mHeight = pSurface->h;
		}

		// Remove the loaded surface now that we have the texture
		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}

	// Return whether the process was successful
	return mTexture != NULL;
}

void Texture2D::Free()
{
	// Check if the texture exists before removing it
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);
}

void Texture2D::RenderSpritesheets(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}