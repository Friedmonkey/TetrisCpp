#include "Game.h"
#include <random>

#define LoadPowerup(name) \
Image image##name = LoadImage("Assets/Images/" #name ".png"); \
ImageResize(&image##name, CellSize, CellSize); \
name = LoadTextureFromImage(image##name); \
UnloadImage(image##name)

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


	LoadPowerup(NormalPowerup);
	LoadPowerup(FreezePowerup);
	LoadPowerup(BombPowerup);
	LoadPowerup(LineBombPowerup);
	LoadPowerup(ColorBombPowerup);

}

Game::~Game()
{
	UnloadTexture(NormalPowerup);
	UnloadTexture(FreezePowerup);
	UnloadTexture(BombPowerup);
	UnloadTexture(LineBombPowerup);
	UnloadTexture(ColorBombPowerup);

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
	currentBlockShadow.id += 9; //add 9 to the id to give it a darker color
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

	PowerupType powerup {BlockNormal};
	int randomPowerup = GetRandomValue(0,10);
	if (randomPowerup <= 4)
	{
		powerup = static_cast<PowerupType>(randomPowerup);
	}

	block.powerup = powerup;

	return block;
}

std::vector<Block> Game::GetAllBlocks()
{
	return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock(), DBlock()};
}
void Game::DrawBlock(Block *pBlock)
{
	pBlock->Draw();
	if (pBlock->powerup != BlockNormal)
	{
		std::vector<Position> tiles = pBlock->GetCellPositions();
		for (Position item : tiles)
		{
			if (item.row < BufferRows) continue;
			int x = item.column * CellSize + GapSize + OffSet;
			int y = (item.row - BufferRows) * CellSize + GapSize + OffSet;
			int w = CellSize - GapSize;
			int h = CellSize - GapSize;
			DrawPowerUp(pBlock->powerup, x, y, w, h);
		}
	}
}
void Game::DrawBlockUI(Block* pBlock, int offX, int offY)
{
	pBlock->DrawUI(offX, offY);
	if (pBlock->powerup != BlockNormal)
	{
		std::vector<Position> tiles = pBlock->GetCellPositions();
		for (Position item : tiles)
		{
			int x = item.column * CellSize + GapSize + OffSet + offX;
			int y = item.row * CellSize + GapSize + OffSet + offY;
			int w = CellSize - GapSize;
			int h = CellSize - GapSize;
			DrawPowerUp(pBlock->powerup, x,y,w,h);
		}
	}
}

void Game::DrawPowerUp(PowerupType powerup, int x, int y, int w, int h)
{
	switch (powerup)
	{
	case BlockNormal:
		DrawTexture(NormalPowerup, x, y, WHITE);
		break;
	case BlockFreeze:
		DrawTexture(FreezePowerup, x, y, WHITE);
		break;
	case BlockBomb:
		DrawTexture(BombPowerup, x, y, WHITE);
		break;
	case BlockLineBomb:
		DrawTexture(LineBombPowerup, x, y, WHITE);
		break;
	case BlockColorBomb:
		DrawTexture(ColorBombPowerup, x, y, WHITE);
		break;
	default:
		break;
	}
}

void Game::Draw()
{
	grid.Draw();

	DrawBlock(&currentBlock);
	DrawBlock(&currentBlockShadow);
	switch (nextBlock.id)
	{
	case 3: //i block
		DrawBlockUI(&nextBlock, ((Columns - 2) * CellSize) - 5, (6 * CellSize) - 5);
		break;
	case 4: //o block
		DrawBlockUI(&nextBlock, ((Columns - 2) * CellSize) - 5, (5 * CellSize) + 10);
		break;
	case 8: //d block
		DrawBlockUI(&nextBlock, ((Columns - 3) * CellSize) + 5, (6 * CellSize) - 5);
		break;
	default:
		DrawBlockUI(&nextBlock, ((Columns-2)*CellSize)+10, (5*CellSize)+10);
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
	bool success = SRSRotateLeft(&currentBlock);
	if (success)
	{
		PlaySound(rotateSound);
		currentBlockShadow.RotateLeft();
		DropShadow();
	}
	else
	{
		PlaySound(cantSound);
	}
}

void Game::RotateRight()
{
	if (gameOver || paused)
	{
		return;
	}
	bool success = SRSRotateRight(&currentBlock);
	if (success)
	{
		PlaySound(rotateSound);
		currentBlockShadow.RotateRight();
		DropShadow();
	}
	else
	{
		PlaySound(cantSound);
	}
}
bool Game::SRSRotateRight(Block* pBlock)
{
	int start = pBlock->rotationState;
	int end = start;
	end++;
	if (end == (int)pBlock->cells.size())
	{
		end = 0;
	}

	auto kick = rot(start, end);
	auto kickdata = pBlock->wallkick[kick];

	int orgRow = pBlock->rowOffset;
	int orgColumn = pBlock->colummnOffset;

	pBlock->RotateRight();
	bool success = false;
	for (Position offset: kickdata)
	{
		//tries++;
		pBlock->Move(offset.row, offset.column);
		if (IsBlockOutside(pBlock) || !BlockFits(pBlock))
		{
			pBlock->rowOffset = orgRow;
			pBlock->colummnOffset = orgColumn;
			continue;
		}
		else
		{
			success = true;
			break;
		}
	}
	//std::cout << "it took " << tries << " tries" << std::endl;

	if (!success)
	{
		pBlock->RotateLeft();
	}


	return success;
}


bool Game::SRSRotateLeft(Block* pBlock)
{
	int start = pBlock->rotationState;
	int end = start;
	end--;
	if (end == -1)
	{
		end = (int)pBlock->cells.size() - 1;
	}

	auto kick = rot(start, end);
	auto kickdata = pBlock->wallkick[kick];

	int orgRow = pBlock->rowOffset;
	int orgColumn = pBlock->colummnOffset;

	pBlock->RotateLeft();
	bool success = false;
	//int tries = 0;
	for (Position offset : kickdata)
	{
		//tries++;
		pBlock->Move(offset.row, offset.column);
		if (IsBlockOutside(pBlock) || !BlockFits(pBlock))
		{
			pBlock->rowOffset = orgRow;
			pBlock->colummnOffset = orgColumn;
			continue;
		}
		else
		{
			success = true;
			break;
		}
	}
	//std::cout << "it took " << tries << " tries" << std::endl;

	if (!success)
	{
		pBlock->RotateRight();
	}

	return success;
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
