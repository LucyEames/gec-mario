#include "CharacterLuigi.h"
#include "Texture2D.h"
#include "Constants.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	mJumpSFX.Load("Audio/jump.wav");
	mBumpSFX.Load("Audio/bump.wav");
	mDeathTime = 3.0f;
}

CharacterLuigi::~CharacterLuigi()
{
	mRenderer = NULL;
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	if (mIsAlive)
	{
		// Collision position variables
		int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
		int centralYPosition = (int)(mPosition.y + (mTexture->GetHeight() * 0.5f)) / TILE_HEIGHT;
		int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

		// Deal with collisions
		if (mCurrentLevelMap->GetTileAt(mPosition.y / TILE_HEIGHT, centralXPosition) == 1)
		{
			mJumpForce = -100.0f;
			mBumpSFX.Play();
		}
		if (mCurrentLevelMap->GetTileAt(centralYPosition, (mPosition.x + mTexture->GetWidth()) / TILE_WIDTH) == 1)
		{
			mMovingRight = false;
		}
		if (mCurrentLevelMap->GetTileAt(centralYPosition, (mPosition.x) / TILE_WIDTH) == 1)
		{
			mMovingLeft = false;
		}

		// Deal with gravity
		if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
		{
			AddGravity(deltaTime);
		}
		else if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 1)
		{
			mCanJump = true;
		}

		if (mJumping)
		{
			mPosition.y -= mJumpForce * deltaTime;
			mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

			if (mJumpForce <= 0.0f)
			{
				mJumping = false;
			}
		}

		if (mMovingLeft)
		{
			MoveLeft(deltaTime, MOVEMENT_SPEED);
		}
		else if (mMovingRight)
		{
			MoveRight(deltaTime, MOVEMENT_SPEED);
		}

		switch (e.type)
		{
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				mMovingLeft = false;
				break;
			case SDLK_d:
				mMovingRight = false;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				Character::Jump();
				break;
			case SDLK_s:
				break;
			case SDLK_a:
				mMovingRight = false;
				mMovingLeft = true;
				break;
			case SDLK_d:
				mMovingLeft = false;
				mMovingRight = true;
				break;
			default:
				break;
			}
			break;
		}
	}
	else
	{
		mDeathTime -= deltaTime;
		if (mDeathTime > 2.0f)
		{
			mPosition.y -= 0.01f;
		}
		else if (mDeathTime > 0.0f)
		{
			mPosition.y += 0.05f;
		}
	}
}