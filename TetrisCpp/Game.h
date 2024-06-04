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
	void HandleMovement();
	void MoveBlockDown();
	void DropBlockDown();
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

	void Move(int rows, int columns);

	bool IsBlockOutside(Block* pBlock);
	bool BlockFits(Block* pBlock);
	void LockBlock();
	void Reset();
	void UpdateScore(int linesCleared, int moveDownPoints);
	void ApplyShadow();

	void DropShadow();

	Grid grid;
	std::vector<Block> blocks;
	Block currentBlock;
	Block currentBlockShadow;
	Block nextBlock;

	Sound rotateSound;
	Sound clearSound;
	Sound loseSound;
	Sound winSound;
	Sound dropSound;
	Sound lockSound;
	Sound cantSound;
	Sound clickSound;
};

