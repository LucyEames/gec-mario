#pragma once
#include <SDL.h>
#include <vector>
#include "Commons.h"
#include "GameScreen.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include "CharacterKoopa.h"

using namespace std;

class Texture2D;
class CharacterMario;
class CharacterLuigi;
class POWBlock;

class GameScreenLevel1 : GameScreen
{
private:
	// Variables
	Texture2D* mBackgroundTexture;
	CharacterMario* myCharacter;
	CharacterLuigi* myCharacter2;
	LevelMap* mLevelMap;
	POWBlock* mPOWBlock;
	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;
	float mEnemySpawnTime;
	float mOverTime;
	SoundEffect mDeathSFX;
	SoundEffect mKickSFX;
	vector<CharacterKoopa*> mEnemies;

	void SetLevelMap();
	void DoScreenshake();

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	// Prototypes
	void Render();
	void Update(float deltaTime, SDL_Event e);
	bool SetUpLevel();
	void UpdatePOWBlock();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	bool IsGameOver() { return mGameOver; }
};