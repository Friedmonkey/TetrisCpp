#include "Game.h"
#include <random>

Game::Game()
{
	grid = Grid();
	gameOver = false;
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	ApplyShadow();
	nextBlock = GetRandomBlock();
	InitAudioDevice();
	music = LoadMusicStream("Assets/Audio/Tetris.mp3");
	PlayMusicStream(music);

	rotateSound = LoadSound("Assets/Audio/rotate.wav");
	clearSound = LoadSound("Assets/Audio/clear.wav");
	loseSound = LoadSound("Assets/Audio/lose.wav");
	winSound = LoadSound("Assets/Audio/win.wav");
	dropSound = LoadSound("Assets/Audio/drop.wav");
	lockSound = LoadSound("Assets/Audio/lock.wav");
	cantSound = LoadSound("Assets/Audio/cant.wav");
	clickSound = LoadSound("Assets/Audio/click.wav");
}

Game::~Game()
{
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadSound(loseSound);
	UnloadSound(winSound);
	UnloadSound(dropSound);
	UnloadSound(lockSound);
	UnloadSound(cantSound);
	UnloadSound(clickSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}

void Game::ApplyShadow()
{
	//set the shadow to be the same type of block as currentBlock
	currentBlockShadow = Block(currentBlock);
	currentBlockShadow.id += 8; //add 8 to the id to give it a darker color
	DropShadow();
}

void Game::DropShadow()
{
	//set the shadow to the exact position as the block
	currentBlockShadow.rowOffset = currentBlock.rowOffset;
	currentBlockShadow.colummnOffset = currentBlock.colummnOffset;

	//keep moving the shadow down until it hit something
	while (!IsBlockOutside(&currentBlockShadow) && BlockFits(&currentBlockShadow))
	{
		currentBlockShadow.Move(1, 0);
	}
	//move it back up one to unclip it
	currentBlockShadow.Move(-1, 0);
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
	currentBlockShadow.Draw(0,0);
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
	if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL) || IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT))
	{
		if (IsKeyDown(KEY_LEFT))
		{
			MoveBlockLeft();
			PlaySound(clickSound);
		}
		if (IsKeyDown(KEY_RIGHT))
		{
			MoveBlockRight();
			PlaySound(clickSound);
		}
	}
	if (IsKeyDown(KEY_DOWN))
	{
		UpdateScore(0, 1);
		MoveBlockDown();
		PlaySound(clickSound);
	}
}

void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();

	if (keyPressed == KEY_P)
	{
		paused = !paused;
	}
	if (keyPressed == KEY_U)
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
	//case KEY_DOWN:
	//	UpdateScore(0,1);
	//	MoveBlockDown();
	//	break;
	case KEY_SPACE:
		DropBlockDown();
		break;

	case KEY_Q:
		RotateLeft();
		break;
	case KEY_E:
	case KEY_UP:
		RotateRight();
		break;

	default:
		break;
	}
}

void Game::Move(int rows, int columns)
{
	currentBlock.Move(rows, columns);
	DropShadow();
}

void Game::MoveBlockLeft()
{
	if (gameOver || paused)
	{
		return;
	}
	Move(0, -1);
	if (IsBlockOutside(&currentBlock) || !BlockFits(&currentBlock))
	{
		Move(0, 1);
		PlaySound(cantSound);
	}
}

void Game::MoveBlockRight()
{
	if (gameOver || paused)
	{
		return;
	}
	Move(0, 1);
	if (IsBlockOutside(&currentBlock) || !BlockFits(&currentBlock))
	{
		Move(0, -1);
		PlaySound(cantSound);
	}
}

void Game::DropBlockDown()
{
	if (gameOver || paused)
	{
		return;
	}
	DropShadow(); //drop the shadow again to make sure it is up to date

	//calculate the distance it will drop
	int dropDistance = currentBlockShadow.rowOffset - currentBlock.rowOffset;

	PlaySound(dropSound);
	//drop the block by overwriting its y value
	currentBlock.rowOffset = currentBlockShadow.rowOffset;
	
	//update the socre by twice the dropdistance because you did it instantly
	UpdateScore(0, dropDistance * 2);
}

void Game::MoveBlockDown()
{
	if (gameOver || paused)
	{
		return;
	}
	Move(1, 0);
	if (IsBlockOutside(&currentBlock) || !BlockFits(&currentBlock))
	{
		Move(-1, 0);
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
	if (IsBlockOutside(&currentBlock) || !BlockFits(&currentBlock))
	{
		currentBlock.RotateRight();
		PlaySound(cantSound);
	}
	else
	{
		PlaySound(rotateSound);
		currentBlockShadow.RotateLeft();
		DropShadow();
	}
}

void Game::RotateRight()
{
	if (gameOver || paused)
	{
		return;
	}
	currentBlock.RotateRight();
	if (IsBlockOutside(&currentBlock) || !BlockFits(&currentBlock))
	{
		currentBlock.RotateLeft();
		PlaySound(cantSound);
	}
	else
	{
		PlaySound(rotateSound);
		currentBlockShadow.RotateRight();
		DropShadow();
	}
}


void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item: tiles)
	{
		grid.grid[item.row][item.column] = currentBlock.id;
	}

	currentBlock = nextBlock;
	ApplyShadow();
	if (!BlockFits(&currentBlock))
	{
		gameOver = true;
		StopMusicStream(music);
		PlaySound(loseSound);
	}
	PlaySound(lockSound);
	nextBlock = GetRandomBlock();

	int rowsCleared = grid.ClearFullRows();
	UpdateScore(rowsCleared,0);
	if (rowsCleared > 2)
	{
		PlaySound(winSound);
		PlaySound(clearSound);
	}
	else if (rowsCleared > 0)
	{
		PlaySound(clearSound);
	}
}

bool Game::IsBlockOutside(Block* pBlock)
{
	std::vector<Position> tiles = pBlock->GetCellPositions();
	for (Position item : tiles)
	{
		if (grid.IsCellOutside(item.row, item.column))
		{
			return true;
		}
	}
	return false;
}

bool Game::BlockFits(Block *pBlock)
{
	std::vector<Position> tiles = pBlock->GetCellPositions();
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
	paused = false;
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	ApplyShadow();
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
	case 4:
		score += 1000;
		break;
	default:
		break;
	}

	score += moveDownPoints;
}
