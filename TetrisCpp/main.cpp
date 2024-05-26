#include <iostream>
#include "settings.h"

#include "Grid.h"
#include "Blocks.cpp"

int main()
{
	std::cout << "Hello world!" << std::endl;
	InitWindow(SW, SH, "Tetris game lol");
	SetTargetFPS(60);

	Grid grid = Grid();
	TBlock block = TBlock();
	grid.Print();

	while (!WindowShouldClose())
	{
		BeginDrawing();

		// updating


		// drawing
		ClearBackground(DARKBLUE);
		//DrawText("Hello world", 10, SH2, 40, RAYWHITE);
		grid.Draw();
		block.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}