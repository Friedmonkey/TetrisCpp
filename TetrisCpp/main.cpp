#include "settings.h"

#include <RayMath.h>
#include <cmath>
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

// Function to draw a centered button with text and return its rectangle
Rectangle ButtonCenter(const char* text, float height, const Font* pFont, const int fontSize, const int fontSpacing, const Color color, const Color buttonColor)
{
	const int widthCenter = (SW + 200) / 2;
	Vector2 textSize = MeasureTextEx(*pFont, text, fontSize, fontSpacing);

	// Calculate button size and position
	float padding = 20.0f;
	float buttonWidth = textSize.x + padding * 2;
	float buttonHeight = textSize.y + padding;
	Rectangle buttonRect = { widthCenter - buttonWidth / 2, height - padding / 2, buttonWidth, buttonHeight };

	Color newButtonColor = Color(buttonColor);
	if (CheckCollisionCircleRec(GetMousePosition(), 2, buttonRect))
	{
		newButtonColor.a = buttonColor.a/2;
	}

	// Draw the button rectangle with rounded corners
	DrawRectangleRounded(buttonRect, 0.5f, 6, newButtonColor);

	// Draw the centered text
	DrawTextEx(*pFont, text, { widthCenter - (textSize.x / 2), height }, fontSize, fontSpacing, color);

	return buttonRect;
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

float menuHue = 0.0f; // New variable for hue
float splashOscillationTime = 0.0f; // Time variable for oscillation

void HandleMenuLogic(Game* pGame, const Font* pFont)
{
	const int textSize = (SW + 200) / 7;

	BeginDrawing();
	ClearBackground(DARKBLUE);

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
	Vector2 splashPosition = { (SW / 2.0f)+20, 140 }; // Adjust Y position to avoid covering "Tetris" logo

	// Draw the shadow
	Vector2 shadowOffset = { 5, 5 };
	Vector2 origin = { splashSize.x / 2.0f, splashSize.y / 2.0f };
	DrawTextPro(*pFont, splashText, Vector2Add(splashPosition, shadowOffset), origin, -10.0f, 20 * splashScale, 2, GRAY); // Shadow

	// Draw the main text
	DrawTextPro(*pFont, splashText, splashPosition, origin, -10.0f, 20 * splashScale, 2, YELLOW); // Main text
#pragma endregion


	// Draw a centered button
	Color buttonColor = { 0, 121, 241, 255 }; // Blue button color
	Rectangle normalRect = ButtonCenter("Play Normal", 300, pFont, 20, 1, WHITE, buttonColor);

	Rectangle powerupRect = ButtonCenter("Play Powerups", 350, pFont, 20, 1, WHITE, buttonColor);

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) //if you clicked
	{
		//if you clicked on normal button
		if (CheckCollisionCircleRec(GetMousePosition(), 2, normalRect))
		{
			pGame->powerupsEnabled = false;
			Menu = false;
			return;
		}
		else if (CheckCollisionCircleRec(GetMousePosition(), 2, powerupRect))
		{
			pGame->powerupsEnabled = true;
			Menu = false;
			return;
		}
	}


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