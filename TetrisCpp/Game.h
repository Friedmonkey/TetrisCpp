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


private:
	bool IsBlockOutside();
	void LockBlock();
	bool BlockFits();
	void Reset();
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
};

