#pragma once
#include "Grid.h"
#include "Blocks.cpp"
#include "FriedAnimatedTexure.h"

class Game
{
public:
	Game();
	~Game();
	void Draw(); //draw the objects
	void HandleInput(); //handle single key presses
	void UpdateAnimations(); //call this to update all animations
	void PlayClick(); //play the click sound
	void PlayLock(); //play the lock sound

	void DrawGridMenu(bool powerups, int xOffset, int yOffset); //draw the grid but used as background
	void TitleGrid(); //simulate a quick game to use as background

	void Reset(); //reset the game

	void HandleMovement(); //handle continues movement for holding keys down
	bool ShouldMoveBlockDown(); //check weather or not this block is supposed to fall
	void MoveBlockDown(); //move the block down
	void DropBlockDown(); //drop a block down

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

	void CheckFreezeBlock(Block* pBlock); //check if the block is frozen and move it down to make it visable

	bool SRSRotateLeft(Block* pBlock); //Super Rotation System rotating
	bool SRSRotateRight(Block *pBlock); //Super Rotation System rotating

	void Move(int rows, int columns); // move the current block somewhere
	void MoveSandBlocksDown(); //move all sand blocks down

	void DrawBlock(Block* pBlock); //draw a block
	void DrawBlockUI(Block* pBlock, int offX, int offY); //draw a block used for ui purposes
	void DrawPowerUp(PowerupType powerup, int x, int y, bool isShadow); //draw a powerup

	//handle powerups
	void PowerupMagic(std::vector<Position> &tiles);
	void PowerupSand(std::vector<Position> &tiles);
	void PowerupLineBomb(std::vector<Position> &tiles);
	void PowerupExplosion(std::vector<Position> &tiles);

	bool IsBlockOutside(Block* pBlock); //if the block is outside of the grid
	bool BlockFits(Block* pBlock); //if the block fits onto the grid
	void LockBlock(); //check powerups and then place the block onto the grid
	void UpdateScore(int linesCleared, int moveDownPoints); //update the score based on parameters
	void ApplyClearPoints(int rowsCleared); //apply points and score + sounds based on rows cleared

	void ApplyShadow(); //setup the shadow block

	void DropShadow(); //move the shadow all the way to the bottom

	void UpdateGameSpeed(int linesCleared); // make the game more difficult over time
	float baseSpeed = 0.3f;
	float minSpeed = 0.08f;

	Texture2D NormalPowerup;
	Texture2D FreezePowerup;
	Texture2D BombPowerup;
	Texture2D LineBombPowerup;
	Texture2D MagicPowerup;
	Texture2D SandPowerup;

	Texture2D FirePowerup;
	FriedAnimatedTexure FireAnimation;


	Grid grid;
	std::vector<Block> blocks;
	Block currentBlock;
	std::vector<Block> sandBlocks;
	bool sandBlockSplitted; //if the sand block powerup has been splitted into multiple blocks or not
	Block currentBlockShadow;
	Block nextBlock;

	Sound sandSound;

	Sound rotateSound;
	Sound clearSound;
	Sound loseSound;
	Sound winSound;
	Sound dropSound;
	Sound lockSound;
	Sound cantSound;
	Sound clickSound;
};

