#include <iostream>
#include <raylib.h>

#include "settings.h"
#include "Grid.h"

int main()
{
	std::cout << "Hello world!" << std::endl;
	InitWindow(SW, SH, "Tetris game lol");
	SetTargetFPS(60);

	Grid grid = Grid();
	grid.Print();

	while (!WindowShouldClose())
	{
		BeginDrawing();

		// updating


		// drawing
		ClearBackground(DARKBLUE);
		//DrawText("Hello world", 10, SH2, 40, RAYWHITE);
		grid.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}