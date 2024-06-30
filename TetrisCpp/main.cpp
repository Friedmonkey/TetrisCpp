#include "settings.h"

#include <RayMath.h>
#include <cmath>
#include "Game.h"
#include <iomanip>
#include <sstream>
#include "StreamBuffer.h"
#include "MenuPage.h"

#define sidepanel ((Columns+1) * CellSize) - 10

double lastGameTickTime {0};
double lastMovementTickTime {0};
bool Menu = true;
MenuPage menuPage = MenuMain;
bool hoverMain = false;
bool hoverBack = false;
bool hoverPowerup = false;
Music titleMusic;

float menuHue = 0.0f; // New variable for hue
float splashOscillationTime = 0.0f; // Time variable for oscillation

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

void WriteCenter(const char *text, float height, const Font* pFont, int fontSize, int fontSpacing, Color color)
{
	const int widthCenter = (SW + 200) / 2;
	const int heightCenter = (SH + 20) / 2;

	Vector2 textSize = MeasureTextEx(*pFont, text, fontSize, fontSpacing);
	DrawTextEx(*pFont, text, { widthCenter - (textSize.x / 2), height}, fontSize, fontSpacing, color);
}
// Function to draw a centered button with text and return its rectangle
Rectangle ButtonCenter(const char* text, float height, const Font* pFont, const int fontSize, const int fontSpacing, const Color color, const Color buttonColor, Game *pGame)
{
	const int widthCenter = (SW + 200) / 2;
	Vector2 textSize = MeasureTextEx(*pFont, text, fontSize, fontSpacing);

	// Calculate button size and position
	float padding = 20.0f;
	float buttonWidth = textSize.x + padding * 2;
	float buttonHeight = textSize.y + padding;
	Rectangle buttonRect = { widthCenter - buttonWidth / 2, height - padding / 2, buttonWidth, buttonHeight };

	Color newButtonColor = Color(buttonColor);
	if (CheckCollisionCircleRec(GetMousePosition(), 1, buttonRect))
	{
		newButtonColor.a = buttonColor.a/2;
	}

	// Draw the button rectangle with rounded corners
	DrawRectangleRounded(buttonRect, 0.25f, 6, newButtonColor);

	// Draw the centered text
	DrawTextEx(*pFont, text, { widthCenter - (textSize.x / 2), height }, fontSize, fontSpacing, color);

	return buttonRect;
}
// Function to draw a centered button with text and return its rectangle
Rectangle DrawButton(const char* text, float width, float height, const Font* pFont, const int fontSize, const int fontSpacing, const Color color, const Color buttonColor, Game* pGame)
{
	Vector2 textSize = MeasureTextEx(*pFont, text, fontSize, fontSpacing);

	// Calculate button size and position
	float padding = 20.0f;
	float buttonWidth = textSize.x + padding * 2;
	float buttonHeight = textSize.y + padding;
	Rectangle buttonRect = { width - buttonWidth / 2, height - padding / 2, buttonWidth, buttonHeight };

	Color newButtonColor = Color(buttonColor);
	if (CheckCollisionCircleRec(GetMousePosition(), 1, buttonRect))
	{
		newButtonColor.a = buttonColor.a / 2;
	}

	// Draw the button rectangle with rounded corners
	DrawRectangleRounded(buttonRect, 0.25f, 6, newButtonColor);

	// Draw the centered text
	DrawTextEx(*pFont, text, { width - (textSize.x / 2), height }, fontSize, fontSpacing, color);

	return buttonRect;
}
void checkHover(Game* pGame, bool *pHover)
{
	if (!*pHover)
	{
		*pHover = true;
		pGame->PlayClick();
	}
}

// Function to convert HSL to RGB
Color HSLtoRGB(float h, float s, float l) {
	float r, g, b;

	if (s == 0.0f) {
		r = g = b = l; // achromatic
	}
	else {
		auto hue2rgb = [](float p, float q, float t) {
			if (t < 0.0f) t += 1.0f;
			if (t > 1.0f) t -= 1.0f;
			if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
			if (t < 1.0f / 2.0f) return q;
			if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
			return p;
			};

		float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
		float p = 2.0f * l - q;
		r = hue2rgb(p, q, h + 1.0f / 3.0f);
		g = hue2rgb(p, q, h);
		b = hue2rgb(p, q, h - 1.0f / 3.0f);
	}

	return Color{ (unsigned char)(r * 255), (unsigned char)(g * 255), (unsigned char)(b * 255), 255 };
}

void DrawTitle(const Font* pFont)
{
	const int textSize = (SW + 200) / 7;

	//thanks chatgpt :D
#pragma region Tetris logo
	const char* logoText = "Fried Tetris";

	// Draw the "Tetris" title
	WriteCenter(logoText, 50, pFont, textSize + 10, 0, BLACK);
	menuHue += 0.1f * GetFrameTime(); // Increment hue value
	if (menuHue > 1.0f) menuHue -= 1.0f; // Wrap around the hue value
	Color color = HSLtoRGB(menuHue, 1.0f, 0.5f); // Convert HSL to RGB
	WriteCenter(logoText, 50, pFont, textSize, 2, color);
#pragma endregion


	//thanks chatgpt :D
#pragma region splash Text
	// Oscillate the splash text size
	splashOscillationTime += 3.0f * GetFrameTime(); // Speed of oscillation
	float splashScale = 1.0f + 0.1f * sinf(splashOscillationTime); // Oscillate between 0.9 and 1.1

	const char* splashText = "Made by FriedMonkey";

	// Measure text size for centering
	Vector2 splashSize = MeasureTextEx(*pFont, splashText, 20, 1);
	Vector2 splashPosition = { (SW / 2.0f) + 20, 140 }; // Adjust Y position to avoid covering "Tetris" logo

	// Draw the shadow
	Vector2 shadowOffset = { 5, 5 };
	Vector2 origin = { splashSize.x / 2.0f, splashSize.y / 2.0f };
	DrawTextPro(*pFont, splashText, Vector2Add(splashPosition, shadowOffset), origin, -10.0f, 20 * splashScale, 2, GRAY); // Shadow

	// Draw the main text
	DrawTextPro(*pFont, splashText, splashPosition, origin, -10.0f, 20 * splashScale, 2, YELLOW); // Main text
#pragma endregion
}
void DrawBackButton(Game* pGame, const Font* pFont, bool gamed = false)
{
	int width = SW + 200;
	int height = SH + 20;

	width -= 50;
	height -= 50;
	// Draw a centered button
	Color buttonColor = { 0, 121, 241, 255 }; // Blue button color

	Rectangle backRect = DrawButton("Back", width, height, pFont, 20, 1, WHITE, buttonColor, pGame);
	if (CheckCollisionCircleRec(GetMousePosition(), 1, backRect))
	{
		checkHover(pGame, &hoverBack);
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) //if you clicked
		{

			Menu = true;
			menuPage = MenuMain;
			pGame->PlayLock();
			if (gamed)
			{
				pGame->TitleGrid();
			}
			return;
		}
	}
	else
	{
		hoverBack = false;
	}
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
	DrawBackButton(pGame, pFont, true);
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

void HandleMenuLogic(Game* pGame, const Font* pFont)
{
	pGame->DrawGridMenu(hoverPowerup, 100, 0);
	hoverPowerup = false;
	DrawTitle(pFont);

	// Draw a centered button
	Color buttonColor = { 0, 121, 241, 255 }; // Blue button color

	Rectangle normalRect = ButtonCenter("Play Normal", 300, pFont, 20, 1, WHITE, buttonColor, pGame);
	Rectangle powerupRect = ButtonCenter("Play Powerups", 360, pFont, 20, 1, WHITE, buttonColor, pGame);
	Rectangle controlsRect = ButtonCenter("How to play", 420, pFont, 20, 1, WHITE, buttonColor, pGame);
	Rectangle highscoresRect = ButtonCenter("Highscores", 480, pFont, 20, 1, WHITE, buttonColor, pGame);


	//if you clicked on normal button
	if (CheckCollisionCircleRec(GetMousePosition(), 1, normalRect))
	{
		checkHover(pGame, &hoverMain);
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) //if you clicked
		{
			pGame->Reset();
			pGame->powerupsEnabled = false;
			pGame->PlayLock();
			Menu = false;
			return;
		}
	}
	else if (CheckCollisionCircleRec(GetMousePosition(), 1, powerupRect))
	{
		hoverPowerup = true;
		checkHover(pGame, &hoverMain);
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) //if you clicked
		{
			pGame->Reset();
			pGame->powerupsEnabled = true;
			pGame->PlayLock();
			Menu = false;
			return;
		}
	}
	else if (CheckCollisionCircleRec(GetMousePosition(), 1, controlsRect))
	{
		checkHover(pGame, &hoverMain);
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) //if you clicked
		{
			pGame->PlayLock();
			menuPage = MenuControls;
			return;
		}
	}
	else if (CheckCollisionCircleRec(GetMousePosition(), 1, highscoresRect))
	{
		checkHover(pGame, &hoverMain);
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) //if you clicked
		{
			pGame->PlayLock();
			menuPage = MenuHighscores;
			return;
		}
	}
	else
	{
		hoverMain = false;
	}
}

void HandleControlsMenuLogic(Game* pGame, const Font* pFont)
{
	DrawTitle(pFont);
	WriteCenter("Use the left and right arrow keys", 200, pFont, 25, 2, WHITE);
	WriteCenter("to move the tetronomino left or right", 225, pFont, 25, 2, WHITE);

	WriteCenter("Use down arrow to speed up the falling", 275, pFont, 25, 2, WHITE);
	WriteCenter("use space to drop the block instantly", 300, pFont, 25, 2, WHITE);

	WriteCenter("Use the up arrow to rotate the pice", 350, pFont, 25, 2, WHITE);
	WriteCenter("clockwise, or use q/e to rotate other", 375, pFont, 25, 2, WHITE);

	WriteCenter("Use any shift or control key to speed up", 425, pFont, 25, 2, WHITE);
	WriteCenter("hold the key down to go faster", 450, pFont, 25, 2, WHITE);
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
	Game game = Game(); //init audio device

	if (Menu)
	{
		game.TitleGrid();
	}

	titleMusic = LoadMusicStream("Assets/Audio/Title.mp3");
	PlayMusicStream(titleMusic);

	while (!WindowShouldClose())
	{
		if (Menu)
		{
			UpdateMusicStream(titleMusic);
			
			BeginDrawing();
			ClearBackground(DARKBLUE);

			switch (menuPage)
			{
			case MenuMain:
				HandleMenuLogic(&game, &font);
				break;
			case MenuControls:
				HandleControlsMenuLogic(&game, &font);
				DrawBackButton(&game, &font);
				break;
			case MenuHighscores:
				DrawTitle(&font);
				DrawBackButton(&game, &font);
				break;

			default:
				HandleMenuLogic(&game, &font);
				break;
			}


			EndDrawing();

		}
		else
		{
			HandleGameLogic(&game, &font);
		}
	}

	CloseWindow();

	return 0;
}