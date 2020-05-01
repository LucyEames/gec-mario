#include "GameScreenLevel1.h"
#include <iostream>
#include <fstream>
#include "Texture2D.h"
#include "Collisions.h"
#include "POWBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mBackgroundTexture = NULL;
	myCharacter = NULL;
	myCharacter2 = NULL;
	mPOWBlock = NULL;
	mLevelMap = NULL;
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete myCharacter;
	myCharacter = NULL;
	delete myCharacter2;
	myCharacter2 = NULL;
	delete mPOWBlock;
	mPOWBlock = NULL;
	mEnemies.clear();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (mScreenshake)
	{
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		// End the shake after the duration
		if (mScreenshakeTime <= 0.0f)
		{
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	myCharacter->Update(deltaTime, e);
	myCharacter2->Update(deltaTime, e);

	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);

	mEnemySpawnTime -= deltaTime;
	if (mEnemySpawnTime <= 0.0f)
	{
		CreateKoopa(Vector2D(20, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(492, 32), FACING_LEFT, KOOPA_SPEED);
		mEnemySpawnTime = KOOPA_SPAWN_DURATION;
	}

	if (!myCharacter->GetAlive() && !myCharacter2->GetAlive())
	{
		
		mOverTime -= deltaTime;
		if (mOverTime < 0.0f)
			mGameOver = true;
	}
}

void GameScreenLevel1::Render()
{
	// Draw the enemies
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	// Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	// Draw the player
	myCharacter->Render();
	myCharacter2->Render();

	// Draw the POW
	mPOWBlock->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	myCharacter = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	myCharacter2 = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(134, 330), mLevelMap);

	mPOWBlock = new POWBlock(mRenderer, mLevelMap);
	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	CreateKoopa(Vector2D(20, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(492, 32), FACING_LEFT, KOOPA_SPEED);

	mEnemySpawnTime = KOOPA_SPAWN_DURATION;
	mOverTime = 3.0f;
	mDeathSFX.Load("Audio/death.wav");
	mKickSFX.Load("Audio/kick.wav");

	// Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load background texture.";
		return false;
	}
	else
	{
		return true;
	}
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH];
	ifstream readFile;
	readFile.open("levelmap.txt");
	if (readFile.is_open())
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				readFile >> map[i][j];
			}
		}
		// Clear up any old map
		if(mLevelMap != NULL)
		{
			delete mLevelMap;
		}

		// Set the new one
		mLevelMap = new LevelMap(map);
	}
	else
	{
		cout << "Failed to load Level 1 Map.";
	}
	readFile.close();
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(mPOWBlock->GetCollisionBox(), myCharacter->GetCollisionBox()) && mPOWBlock->IsAvailable())
	{
		if (myCharacter->IsJumping())
		{
			DoScreenshake();
			mPOWBlock->TakeAHit();
			myCharacter->CancelJump();
		}
	}
	if (Collisions::Instance()->Box(mPOWBlock->GetCollisionBox(), myCharacter2->GetCollisionBox()) && mPOWBlock->IsAvailable())
	{
		if (myCharacter2->IsJumping())
		{
			DoScreenshake();
			mPOWBlock->TakeAHit();
			myCharacter2->CancelJump();
		}
	}
}

void GameScreenLevel1::DoScreenshake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			// Check if enemy is on the bottom row of the tiles
			if (mEnemies[i]->GetPosition().y > 340.0f)
			{
				// Is the enemy behind the pipes to the left / right?
				if (mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
					mEnemies[i]->SetPosition({ 0.0f, 0.0f });
				else if (mEnemies[i]->GetPosition().x < 0.0f - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
					mEnemies[i]->SetPosition({ SCREEN_WIDTH - TILE_WIDTH, 0.0f });
			}

			mEnemies[i]->Update(deltaTime, e);

			if (myCharacter->GetAlive())
			{
				if (Collisions::Instance()->Circle(mEnemies[i], myCharacter))
					if (mEnemies[i]->GetInjured())
					{
						mEnemies[i]->SetAlive(false);
						mKickSFX.Play();
					}
					else
					{
						myCharacter->SetAlive(false);
						mDeathSFX.Play();
					}
			}
			if (myCharacter2->GetAlive())
			{
				if (Collisions::Instance()->Circle(mEnemies[i], myCharacter2))
					if (mEnemies[i]->GetInjured())
					{
						mEnemies[i]->SetAlive(false);
						mKickSFX.Play();
					}
					else
					{
						myCharacter2->SetAlive(false);
						mDeathSFX.Play();
					}
			}

			// If the enemy is no longer alive, then schedule it for deletion
			if (!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
		// Remove a dead enemy - 1 each update
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, position, direction, speed);
	mEnemies.push_back(koopaCharacter);
}
		