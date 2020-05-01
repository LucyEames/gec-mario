#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "SoundEffect.h"

using namespace std;

class Texture2D;

class Character
{
private:
	// Variables
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;

protected:
	// Variables
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	bool mJumping;
	bool mCanJump;
	float mJumpForce;
	float mCollisionRadius;
	LevelMap* mCurrentLevelMap;
	SoundEffect mJumpSFX;
	SoundEffect mBumpSFX;
	SoundEffect mStompSFX;

	// Prototypes
	virtual void MoveLeft(float deltaTime, float speed);
	virtual void MoveRight(float deltaTime, float speed);

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	// Prototypes
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void AddGravity(float deltaTime);
	void Jump();
	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();
	float GetCollisionRadius();
	Rect2D GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight()); }
	bool IsJumping() { return mJumping; }
	void CancelJump();
};

