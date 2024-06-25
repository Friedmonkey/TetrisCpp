#include "FriedAnimatedTexure.h"


FriedAnimatedTexure::FriedAnimatedTexure() {}
FriedAnimatedTexure::FriedAnimatedTexure(Texture2D* ptrTexture, int framesPerLine, int lines)
{	
	this->framesPerLine = framesPerLine;
	this->lines = lines;
	this->pTexture = ptrTexture;

	// Init variables for animation
	frameWidth = (float)(ptrTexture->width / framesPerLine);   // Sprite one frame rectangle width
	frameHeight = (float)(ptrTexture->height / lines);           // Sprite one frame rectangle height
	currentFrame = 0;
	currentLine = 0;

	frameRec = { 0, 0, frameWidth, frameHeight };
	position = { 0.0f, 0.0f };

	framesCounter = 0;
}

void FriedAnimatedTexure::Update()
{
	// Compute explosion animation frames
	framesCounter++;

	if (framesCounter > 2)
	{
		currentFrame++;

		if (currentFrame >= framesPerLine)
		{
			currentFrame = 0;
			currentLine++;

			if (currentLine >= lines)
			{
				currentLine = 0;
			}
		}

		framesCounter = 0;
	}

	frameRec.x = frameWidth * currentFrame;
	frameRec.y = frameHeight * currentLine;
}

void FriedAnimatedTexure::Draw(int x, int y, Color color)
{
	DrawTextureRec(*pTexture, frameRec, { static_cast<float>(x),static_cast<float>(y) }, color);
}
