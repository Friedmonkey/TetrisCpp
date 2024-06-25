#include "settings.h"

#include "Game.h"
#include <iomanip>
#include <sstream>
#include "StreamBuffer.h"

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
//int WinMain()
{
	//std::cout << "Hello world!" << std::endl;

	InitWindow(SW+200, SH+20, "Tetris game lol");
	Image icon = LoadImage("Assets/Images/Tetris.png");
	SetWindowIcon(icon);
	SetTargetFPS(60);

	Font font = LoadFontEx("Assets/Fonts/block.ttf", 64, 0, 0);

	Game game = Game();


	while (!WindowShouldClose())
	{
		UpdateMusicStream(game.music);
		// updating

		game.UpdateAnimations();
		game.HandleInput();

		if (TickGameSpeed(game.gameSpeed))
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
		Rectangle scoreRect = Rectangle {sidepanel-GapSize, 55, 170, 60};
		DrawRectangleRounded(scoreRect, 0.3, 6, LIGHTBLUE);

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


		//speed text
		DrawTextEx(font, "Speed", { sidepanel, 415 }, 25, 2, WHITE);

		//speed field
		Rectangle speedRect = Rectangle{ sidepanel - GapSize, 455, 170, 60 };
		DrawRectangleRounded(speedRect, 0.3, 6, LIGHTBLUE);

		//speed value
		char   speedText[20];
		omemstream out(speedText);

		out << std::fixed << std::setprecision(4) << game.gameSpeed;
		DrawTextEx(font, speedText, { sidepanel, 480 }, 25, 2, WHITE);


		game.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}