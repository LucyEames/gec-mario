#pragma once
#include "Character.h"

class CharacterLuigi : public Character
{
private:
	// Variables
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	bool mIsAlive = true;
	float mDeathTime;
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

	// Prototypes
	void Update(float deltaTime, SDL_Event e);
	void SetAlive(bool alive) { mIsAlive = alive; }
	bool GetAlive() { return mIsAlive; }
};

