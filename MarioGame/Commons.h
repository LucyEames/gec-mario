#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D()
	{
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
	}
	Rect2D(float initialX, float initialY, float initialWidth, float initialHeight)
	{
		x = initialX;
		y = initialY;
		width = initialWidth;
		height = initialHeight;
	}
};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_LEVEL1,
	SCREEN_GAMEOVER
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};