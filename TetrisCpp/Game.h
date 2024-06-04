#pragma once
#include "Grid.h"
#include "Blocks.cpp"

class Game
{
public:
	Game();
	~Game();
	void Draw();
	void HandleInput();
	void MoveBlockDown();
	void RotateLeft();
	void RotateRight();
	bool gameOver;
	bool paused;
	int score;
	Music music;

private:
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void MoveBlockLeft();
	void MoveBlockRight();

	bool IsBlockOutside();
	void LockBlock();
	bool BlockFits();
	void Reset();
	void UpdateScore(int linesCleared, int moveDownPoints);

	Grid grid;
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;

	Sound rotateSound;
	Sound clearSound;
};

