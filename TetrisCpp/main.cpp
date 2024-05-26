#include <iostream>
#include <raylib.h>

#include "settings.h"

int main()
{
	std::cout << "Hello world!" << std::endl;
	InitWindow(SW, SH, "Tetris game lol");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		// updating


		// drawing
		ClearBackground(GREEN);
		DrawText("Hello world", 10, SH2, 40, RAYWHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}