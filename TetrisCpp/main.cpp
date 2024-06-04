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

	InitWindow(SW+200, SH+20, "Tetris game lol");
	SetTargetFPS(60);

	Font font = LoadFontEx("Graphics/Fonts/block.ttf", 64, 0, 0);

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
		//score text
		DrawTextEx(font, "Score", { Columns * (CellSize + GapSize), 15}, 25, 2, WHITE);

		//score field
		Rectangle rect = Rectangle {Columns*(CellSize+GapSize)-GapSize, 55, 170, 60};
		DrawRectangleRounded(rect, 0.3, 6, LIGHTBLUE);

		//Score value
		char scoreText[10];
		sprintf_s(scoreText, "%i",game.score);
		DrawTextEx(font, scoreText, {Columns * (CellSize + GapSize), 80}, 25, 2, WHITE);

		//Next text
		DrawTextEx(font, "Next", { Columns * (CellSize + GapSize), 130 }, 25, 2, WHITE);

		//next field
		Rectangle rect2 = Rectangle{ Columns * (CellSize + GapSize) - GapSize, 160, 170, 150 };
		DrawRectangleRounded(rect2, 0.3, 6, LIGHTBLUE);

		if (game.gameOver)
		{
			//Gameover text
			DrawTextEx(font, "Game over", { Columns * (CellSize + GapSize), 325 }, 25, 2, WHITE);
		}


		game.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}