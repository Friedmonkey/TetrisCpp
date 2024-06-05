#include <iostream>
#include "settings.h"

#include "Game.h"

#define sidepanel ((Columns+1) * CellSize) - 10

double lastGameTickTime {0};
double lastMovementTickTime {0};

bool TickGameSpeed(double interval)
{
	double currentTime = GetTime();

	if (currentTime - lastGameTickTime >= interval)
	{
		lastGameTickTime = currentTime;
		return true;
	}
	return false;
}

bool TickMovementSpeed(double interval)
{
	double currentTime = GetTime();

	if (currentTime - lastMovementTickTime >= interval)
	{
		lastMovementTickTime = currentTime;
		return true;
	}
	return false;
}

int main()
{
	std::cout << "Hello world!" << std::endl;

	InitWindow(SW+200, SH+20, "Tetris game lol");
	SetTargetFPS(60);

	Font font = LoadFontEx("Assets/Fonts/block.ttf", 64, 0, 0);

	Game game = Game();


	while (!WindowShouldClose())
	{
		UpdateMusicStream(game.music);
		// updating

		game.HandleInput();

		if (TickGameSpeed(0.2))
		{
			game.MoveBlockDown();
		}

		if (TickMovementSpeed(0.05))
		{
			game.HandleMovement();
		}


		BeginDrawing();
		// drawing
		ClearBackground(DARKBLUE);
		//score text
		DrawTextEx(font, "Score", {sidepanel, 15}, 25, 2, WHITE);

		//score field
		Rectangle rect = Rectangle {sidepanel-GapSize, 55, 170, 60};
		DrawRectangleRounded(rect, 0.3, 6, LIGHTBLUE);

		//Score value
		char scoreText[10];
		sprintf_s(scoreText, "%i",game.score);
		DrawTextEx(font, scoreText, {sidepanel, 80}, 25, 2, WHITE);

		//Next text
		DrawTextEx(font, "Next", { sidepanel, 130 }, 25, 2, WHITE);

		//next field
		Rectangle rect2 = Rectangle{ sidepanel - GapSize, 160, 170, 150 };
		DrawRectangleRounded(rect2, 0.3, 6, LIGHTBLUE);

		if (game.gameOver)
		{
			//Gameover text
			DrawTextEx(font, "Game over", { sidepanel, 325 }, 25, 2, WHITE);
			DrawTextEx(font, "Press \"U\"", { sidepanel, 350 }, 25, 2, WHITE);
			DrawTextEx(font, "to restart", { sidepanel, 375 }, 25, 2, WHITE);
		}


		game.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}