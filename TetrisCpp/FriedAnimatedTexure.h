#pragma once
#include <Raylib.h>

class FriedAnimatedTexure
{
public:
	FriedAnimatedTexure();
	FriedAnimatedTexure(Texture2D* ptrTexture, int framesPerLine, int lines);
	void Update();
	void Draw(int x, int y, Color color);
private:
	Texture2D *pTexture;

	int framesPerLine;
	int lines;

	// Init variables for animation
	float frameWidth;
	float frameHeight;
	int currentFrame;
	int currentLine;

	Rectangle frameRec;
	Vector2 position;

	int framesCounter;
};

