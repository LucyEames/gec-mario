#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	mCollisionRadius = 15.0f;
	mCurrentLevelMap = map;
}

Character::~Character()
{
	mRenderer = NULL;
}

void Character::Render()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
	
}

void Character::Update(float deltaTime, SDL_Event e)
{
}

void Character::MoveLeft(float deltaTime, float speed)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= speed;
	if (mPosition.x <= 0.0f - mCollisionRadius)
	{
		mPosition.x = SCREEN_WIDTH - mCollisionRadius;
		mPosition.y -= 2.0f;
	}
}

void Character::MoveRight(float deltaTime, float speed)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += speed;
	if (mPosition.x + mCollisionRadius >= SCREEN_WIDTH)
	{
		mPosition.x = 0.0f - mCollisionRadius;
		mPosition.y -= 2.0f;
	}
}

void Character::AddGravity(float deltaTime)
{
	mPosition.y += GRAVITY * deltaTime;
}

void Character::Jump()
{
	if (!mJumping)
	{
		mJumpSFX.Play();
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::CancelJump()
{
	mJumpForce = 0;
}

void Character::SetPosition(Vector2D newPosition) { mPosition = newPosition; }
Vector2D Character::GetPosition() { return mPosition; }
float Character::GetCollisionRadius() { return mCollisionRadius; }