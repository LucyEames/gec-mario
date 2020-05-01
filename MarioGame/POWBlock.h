#pragma once
#include <SDL.h>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include <iostream>

class POWBlock
{
private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	int mNumberOfHitsLeft;
public:
	POWBlock(SDL_Renderer* renderer, LevelMap* map);
	~POWBlock();
	
	void Render();
	Rect2D GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight); }
	void TakeAHit();
	bool IsAvailable() { return mNumberOfHitsLeft > 0; }
};

