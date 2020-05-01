#pragma once
#include "Character.h"

class CharacterMario : public Character
{
private:
	// Variables
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	bool mIsAlive = true;
	float mDeathTime;
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	// Prototypes
	void Update(float deltaTime, SDL_Event e);
	void SetAlive(bool alive) { mIsAlive = alive; }
	bool GetAlive() { return mIsAlive; }
};

