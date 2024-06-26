#pragma once
#include "Grid.h"
#include "Blocks.cpp"
#include "FriedAnimatedTexure.h"

class Game
{
public:
	Game();
	~Game();
	void Draw();
	void HandleInput();
	void UpdateAnimations();
	void PlayClick();
	void PlayLock();
	void DrawGridMenu(bool powerups, int xOffset, int yOffset);
	void TitleGrid();

	void Reset();

	void HandleMovement();
	void MoveBlockDown();
	void DropBlockDown();
	bool gameOver;
	bool powerupsEnabled = false;
	int score;
	float gameSpeed = baseSpeed;
	Music music;


private:
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void MoveBlockLeft();
	void MoveBlockRight();
	void RotateLeft();
	void RotateRight();
	void DrawGrid();


	bool SRSRotateLeft(Block* pBlock);
	bool SRSRotateRight(Block *pBlock);

	void Move(int rows, int columns);

	void DrawBlock(Block* pBlock);
	void DrawBlockUI(Block* pBlock, int offX, int offY);
	void DrawPowerUp(PowerupType powerup, int x, int y, bool isShadow);


	bool IsBlockOutside(Block* pBlock);
	bool BlockFits(Block* pBlock);
	void LockBlock();
	void UpdateScore(int linesCleared, int moveDownPoints);
	void ApplyShadow();

	void DropShadow();

	void UpdateGameSpeed(int linesCleared);
	float baseSpeed = 0.3f;
	float minSpeed = 0.08f;

	Texture2D NormalPowerup;
	Texture2D FreezePowerup;
	Texture2D BombPowerup;
	Texture2D LineBombPowerup;
	Texture2D ColorBombPowerup;
	Texture2D SandPowerup;

	Texture2D FirePowerup;
	FriedAnimatedTexure FireAnimation;


	Grid grid;
	std::vector<Block> blocks;
	Block currentBlock;
	std::vector<Block> currentBlocks;
	bool sandBlockSplitted;
	int sandBlocksLocked = 0;
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

