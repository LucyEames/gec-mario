#include "POWBlock.h"
#include <iostream>

POWBlock::POWBlock(SDL_Renderer* renderer, LevelMap* map)
{
	string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load texture: " << imagePath << endl;
		return;
	}

	mLevelMap = map;
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);
}

POWBlock::~POWBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = nullptr;
	mLevelMap = NULL;
}

void POWBlock::Render()
{
	if (mNumberOfHitsLeft > 0)
	{
		// Get the portion of the spritesheet you want to draw.
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

		//								{ XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite }
		SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		// Determine where you want it drawn
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		// Then draw it
		mTexture->RenderSpritesheets(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}

void POWBlock::TakeAHit()
{
	mNumberOfHitsLeft -= 1;
	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;
		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}
}