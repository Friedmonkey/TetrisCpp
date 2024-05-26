#include "Game.h"
#include <random>

Game::Game()
{
	grid = Grid();
	gameOver = false;
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
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
	currentBlock.Draw();
}

void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();

	if (gameOver && keyPressed != 0)
	{
		gameOver = false;
		Reset();
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
	if (gameOver)
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
	if (gameOver)
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
	if (gameOver)
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
	if (gameOver)
	{
		return;
	}
	currentBlock.RotateLeft();
	if (IsBlockOutside() || !BlockFits())
	{
		currentBlock.RotateRight();
	}
}

void Game::RotateRight()
{
	if (gameOver)
	{
		return;
	}
	currentBlock.RotateRight();
	if (IsBlockOutside() || !BlockFits())
	{
		currentBlock.RotateLeft();
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
	}
	nextBlock = GetRandomBlock();

	grid.ClearFullRows();
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
}
