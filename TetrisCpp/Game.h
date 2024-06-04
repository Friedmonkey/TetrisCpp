#pragma once
#include "Grid.h"
#include "Blocks.cpp"

class Game
{
public:
	Game();
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void Draw();
	void HandleInput();
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockDown();
	void RotateLeft();
	void RotateRight();
	Grid grid;
	bool gameOver;
	int score;


private:
	bool IsBlockOutside();
	void LockBlock();
	bool BlockFits();
	void Reset();
	void UpdateScore(int linesCleared, int moveDownPoints);
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
};

