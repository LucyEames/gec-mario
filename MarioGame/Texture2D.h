#pragma once
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include <SDL.h>
#include <string>
#include "Commons.h"
using namespace std;

class Texture2D
{
private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;

public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(string path);
	void Free();
	void Render(Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f);
	void RenderSpritesheets(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle = 0.0f);
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
};

#endif //_TEXTURE2D_H