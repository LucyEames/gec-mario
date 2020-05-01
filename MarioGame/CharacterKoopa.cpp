#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed) 
	: Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;
	mInjured = false;
	mSingleSpriteWidth = mTexture->GetWidth() / 2; // 2 sprites on this spritesheet in 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
	mIsAlive = true;
	mStompSFX.Load("Audio/stomp.wav");
}

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::TakeDamage()
{
	mStompSFX.Play();
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if(!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;
		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::FlipRightwayUp()
{
	mFacingDirection = FACING_LEFT;
	mInjured = false;
	Jump();
}

void CharacterKoopa::Render()
{
	// Variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	// If injured move the left position to be the left position of the second image on the spritesheet
	if (mInjured)
		left = mSingleSpriteWidth;

	// Get the portion of the spritesheet you want to draw
	//								{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	// Determine where you want it drawn
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	// Then draw it facing the correct direction
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->RenderSpritesheets(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->RenderSpritesheets(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	if (!mInjured)
	{
		// Collision position variables
		int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f * 0.5f)) / TILE_WIDTH;
		int centralYPosition = (int)(mPosition.y + (mTexture->GetHeight() * 0.5f)) / TILE_HEIGHT;
		int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

		// Deal with collisions
		if (mCurrentLevelMap->GetTileAt(mPosition.y / TILE_HEIGHT, centralXPosition) == 1)
		{
			mJumpForce = -100.0f;
		}
		if (mCurrentLevelMap->GetTileAt(centralYPosition, (mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH) == 1)
		{
			mFacingDirection = FACING_LEFT;
		}
		if (mCurrentLevelMap->GetTileAt(centralYPosition, (mPosition.x) / TILE_WIDTH) == 1)
		{
			mFacingDirection = FACING_RIGHT;
		}

		// Deal with gravity
		if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
		{
			AddGravity(deltaTime);
		}

		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingRight = true;
			mMovingLeft = false;
		}

		if (mMovingLeft)
		{
			MoveLeft(deltaTime, KOOPA_SPEED);
		}
		else if (mMovingRight)
		{
			MoveRight(deltaTime, KOOPA_SPEED);
		}
	}
	else
	{
		mMovingRight = false;
		mMovingLeft = false;

		mInjuredTime -= deltaTime;
		if (mInjuredTime <= 0.0)
			FlipRightwayUp();
	}
}
