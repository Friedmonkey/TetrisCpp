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
	void Update();
	Grid grid;


private:
	bool IsBlockOutside();
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
};

