#pragma once
#include "Character.h"

class CharacterKoopa : public Character
{
private:
	FACING mFacingDirection;
	float mMovementSpeed;
	bool mMovingLeft;
	bool mMovingRight;
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mInjured;
	float mInjuredTime;
	bool mIsAlive;

public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();
	void FlipRightwayUp();
	void SetAlive(bool alive) { mIsAlive = alive; }
	bool GetAlive() { return mIsAlive; }
	bool GetInjured() { return mInjured; }

	void Render();
	void Update(float deltaTime, SDL_Event e);
};

