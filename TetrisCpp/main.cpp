#include <iostream>
#include "settings.h"

#include "Grid.h"

int main()
{
	std::cout << "Hello world!" << std::endl;
	InitWindow(SW, SH, "Tetris game lol");
	SetTargetFPS(60);

	Grid grid = Grid();
	grid.grid[0][0] = 1;
	grid.grid[3][5] = 4;
	grid.grid[17][8] = 7;
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