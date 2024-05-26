#include <iostream>
#include "settings.h"

#include "Game.h"

int main()
{
	std::cout << "Hello world!" << std::endl;
	InitWindow(SW, SH, "Tetris game lol");
	SetTargetFPS(60);

	Game game = Game();


	while (!WindowShouldClose())
	{
		BeginDrawing();

		// updating
		game.HandleInput();

		// drawing
		ClearBackground(DARKBLUE);
		//DrawText("Hello world", 10, SH2, 40, RAYWHITE);
		game.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}