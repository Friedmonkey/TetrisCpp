#include <iostream>
#include "settings.h"

#include "Game.h"

double lastUpdateTime {0};

bool EventTriggerd(double interval)
{
	double currentTime = GetTime();

	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

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

		if (EventTriggerd(0.2))
		{
			game.MoveBlockDown();
		}

		// drawing
		ClearBackground(DARKBLUE);
		game.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}