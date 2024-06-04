#include "Game.h"
#include <random>

Game::Game()
{
	grid = Grid();
	gameOver = false;
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	InitAudioDevice();
	music = LoadMusicStream("Assets/Audio/Tetris.mp3");
	PlayMusicStream(music);

	rotateSound = LoadSound("Assets/Audio/rotate.wav");
	clearSound = LoadSound("Assets/Audio/clear.wav");
}

Game::~Game()
{
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}
	int randomIndex = GetRandomValue(0, blocks.size()-1);
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}

std::vector<Block> Game::GetAllBlocks()
{
	return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
	grid.Draw();
	currentBlock.Draw(0,0);
	switch (nextBlock.id)
	{
	case 3: //i block
		nextBlock.DrawUI( ((Columns-2)*CellSize)-5, (6*CellSize)-5);
		break;
	case 4: //o block
		nextBlock.DrawUI( ((Columns-2)*CellSize)-5, (5*CellSize)+10);
		break;
	default:
		nextBlock.DrawUI( ((Columns-2)*CellSize)+10, (5*CellSize)+10);
		break;
	}
}

void Game::HandleMovement()
{
	if (gameOver || paused)
	{
		return;
	}
	if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
	{
		if (IsKeyDown(KEY_LEFT))
		{
			MoveBlockLeft();
		}
		if (IsKeyDown(KEY_RIGHT))
		{
			MoveBlockRight();
		}
	}
	if (IsKeyDown(KEY_DOWN))
	{
		UpdateScore(0, 1);
		MoveBlockDown();
	}
}

void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();

	if (keyPressed == KEY_P)
	{
		paused = !paused;
	}
	if (keyPressed == KEY_R)
	{
		Reset();
	}

	if (gameOver || paused)
	{
		return;
	}

	switch (keyPressed)
	{
	case KEY_LEFT:
		MoveBlockLeft();
		break;
	case KEY_RIGHT:
		MoveBlockRight();
		break;
	case KEY_DOWN:
		UpdateScore(0,1);
		MoveBlockDown();
		break;

	case KEY_Q:
		RotateLeft();
		break;
	case KEY_E:
		RotateRight();
		break;

	default:
		break;
	}
}

void Game::MoveBlockLeft()
{
	if (gameOver || paused)
	{
		return;
	}
	currentBlock.Move(0, -1);
	if (IsBlockOutside() || !BlockFits())
	{
		currentBlock.Move(0, 1);
	}
}

void Game::MoveBlockRight()
{
	if (gameOver || paused)
	{
		return;
	}
	currentBlock.Move(0, 1);
	if (IsBlockOutside() || !BlockFits())
	{
		currentBlock.Move(0, -1);
	}
}

void Game::MoveBlockDown()
{
	if (gameOver || paused)
	{
		return;
	}
	currentBlock.Move(1, 0);
	if (IsBlockOutside() || !BlockFits())
	{
		currentBlock.Move(-1, 0);
		LockBlock();
	}
}

void Game::RotateLeft()
{
	if (gameOver || paused)
	{
		return;
	}
	currentBlock.RotateLeft();
	if (IsBlockOutside() || !BlockFits())
	{
		currentBlock.RotateRight();
	}
	else
	{
		PlaySound(rotateSound);
	}
}

void Game::RotateRight()
{
	if (gameOver || paused)
	{
		return;
	}
	currentBlock.RotateRight();
	if (IsBlockOutside() || !BlockFits())
	{
		currentBlock.RotateLeft();
	}
	else
	{
		PlaySound(rotateSound);
	}
}

bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item: tiles)
	{
		if (grid.IsCellOutside(item.row, item.column))
		{
			return true;
		}
	}
	return false;
}

void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item: tiles)
	{
		grid.grid[item.row][item.column] = currentBlock.id;
	}

	currentBlock = nextBlock;
	if (!BlockFits())
	{
		gameOver = true;
		StopMusicStream(music);
	}
	nextBlock = GetRandomBlock();

	int rowsCleared = grid.ClearFullRows();
	UpdateScore(rowsCleared,0);
	if (rowsCleared > 0)
	{
		PlaySound(clearSound);
	}
}

bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles)
	{
		if (!grid.IsCellEmpty(item.row, item.column))
		{
			return false;
		}
	}
	return true;
}

void Game::Reset()
{
	grid.Initialize();
	gameOver = false;
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	score = 0;
	PlayMusicStream(music);
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared)
	{
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;

	default:
		break;
	}

	score += moveDownPoints;
}
