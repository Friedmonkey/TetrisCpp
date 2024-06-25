#include "settings.h"

#include "Game.h"
#include <iomanip>
#include <sstream>
#include "StreamBuffer.h"

#define sidepanel ((Columns+1) * CellSize) - 10

double lastGameTickTime {0};
double lastMovementTickTime {0};
bool Menu = true;

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

void HandleGameLogic(Game *pGame, const Font *pFont)
{
	UpdateMusicStream(pGame->music);
	// updating

	pGame->UpdateAnimations();
	pGame->HandleInput();

	if (TickGameSpeed(pGame->gameSpeed))
	{
		pGame->MoveBlockDown();
	}

	if (TickMovementSpeed(0.05))
	{
		pGame->HandleMovement();
	}


	BeginDrawing();
	// drawing
	ClearBackground(DARKBLUE);
	//score text
	DrawTextEx(*pFont, "Score", { sidepanel, 15 }, 25, 2, WHITE);

	//score field
	Rectangle scoreRect = Rectangle{ sidepanel - GapSize, 55, 170, 60 };
	DrawRectangleRounded(scoreRect, 0.3, 6, LIGHTBLUE);

	//Score value
	char scoreText[10];
	sprintf_s(scoreText, "%i", pGame->score);
	DrawTextEx(*pFont, scoreText, { sidepanel, 80 }, 25, 2, WHITE);

	//Next text
	DrawTextEx(*pFont, "Next", { sidepanel, 130 }, 25, 2, WHITE);

	//next field
	Rectangle rect2 = Rectangle{ sidepanel - GapSize, 160, 170, 150 };
	DrawRectangleRounded(rect2, 0.3, 6, LIGHTBLUE);

	if (pGame->gameOver)
	{
		//Gameover text
		DrawTextEx(*pFont, "Game over", { sidepanel, 325 }, 25, 2, WHITE);
		DrawTextEx(*pFont, "Press \"U\"", { sidepanel, 350 }, 25, 2, WHITE);
		DrawTextEx(*pFont, "to restart", { sidepanel, 375 }, 25, 2, WHITE);
	}


	//speed text
	DrawTextEx(*pFont, "Speed", { sidepanel, 415 }, 25, 2, WHITE);

	//speed field
	Rectangle speedRect = Rectangle{ sidepanel - GapSize, 455, 170, 60 };
	DrawRectangleRounded(speedRect, 0.3, 6, LIGHTBLUE);

	//speed value
	char   speedText[20];
	omemstream out(speedText);

	out << std::fixed << std::setprecision(4) << pGame->gameSpeed;
	DrawTextEx(*pFont, speedText, { sidepanel, 480 }, 25, 2, WHITE);


	pGame->Draw();

	EndDrawing();
}

void WriteCenter(const char *text, float height, const Font* pFont, int fontSize, int fontSpacing, Color color)
{
	const int widthCenter = (SW + 200) / 2;
	const int heightCenter = (SH + 20) / 2;

	Vector2 textSize = MeasureTextEx(*pFont, text, fontSize, fontSpacing);
	DrawTextEx(*pFont, text, { widthCenter - (textSize.x / 2), height}, fontSize, fontSpacing, color);

}

void HandleMenuLogic(Game* pGame, const Font* pFont)
{

	BeginDrawing();
	ClearBackground(DARKBLUE);



	WriteCenter("Tetris", 50, pFont, 50, 2, WHITE);

	EndDrawing();

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
		if (Menu)
		{
			HandleMenuLogic(&game, &font);
		}
		else
		{
			HandleGameLogic(&game, &font);
		}
	}

	CloseWindow();

	return 0;
}