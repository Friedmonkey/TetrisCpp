#include "Game.h"
#include <random>
#include <cmath>

#define LoadPowerup(name) \
Image image##name = LoadImage("Assets/Images/" #name ".png"); \
ImageResize(&image##name, CellSize-GapSize, CellSize-GapSize); \
name = LoadTextureFromImage(image##name); \
UnloadImage(image##name)

#define LoadAnimiatedPowerup(name, framesPerLine, lines) \
Image image##name = LoadImage("Assets/Images/" #name "Atlas.png"); \
ImageResize(&image##name, (CellSize-GapSize)*framesPerLine, (CellSize-GapSize)*lines); \
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
	gameSpeed = baseSpeed;

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
	LoadPowerup(SandPowerup);

	LoadAnimiatedPowerup(FirePowerup, 32, 1); //uses Atlas.png


	FireAnimation = FriedAnimatedTexure(&FirePowerup, 32, 1);

	//imFirePowerup = LoadImageAnim("Assets/Images/FirePowerup.gif", &fireanimFrames);
	//ImageResize(&imFirePowerup, CellSize - GapSize, CellSize - GapSize);
	//FirePowerup = LoadTextureFromImage(imFirePowerup);

}

Game::~Game()
{
	UnloadTexture(NormalPowerup);
	UnloadTexture(FreezePowerup);
	UnloadTexture(BombPowerup);
	UnloadTexture(LineBombPowerup);
	UnloadTexture(ColorBombPowerup);
	UnloadTexture(SandPowerup);

	UnloadTexture(FirePowerup);

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

void Game::PlayClick()
{
	PlaySound(clickSound);
}
void Game::PlayLock()
{
	PlaySound(lockSound);
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

void Game::UpdateGameSpeed(int linesCleared)
{
	gameSpeed -= 0.0012f * (linesCleared*2); // Increase speed every 10 lines
	if (gameSpeed < minSpeed)
	{
		gameSpeed = minSpeed;
	}
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

	if (!powerupsEnabled) return block;


	PowerupType powerup {BlockNormal};
	int randomPowerup = GetRandomValue(0,12);
	if (randomPowerup <= AmountPowerups)
	{
		powerup = static_cast<PowerupType>(randomPowerup);
	}

	block.powerup = powerup;

	return block;
}

std::vector<Block> Game::GetAllBlocks()
{
	if (powerupsEnabled)
	{
		return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock(), DBlock()};
	}
	else
	{
		return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
	}
}
void Game::DrawBlock(Block *pBlock)
{
	pBlock->Draw();
	if (!powerupsEnabled) return;
	if (pBlock->powerup != BlockNormal)
	{
		std::vector<Position> tiles = pBlock->GetCellPositions();
		for (Position item : tiles)
		{
			if (item.row < BufferRows) continue;
			int x = item.column * CellSize + GapSize + OffSet;
			int y = (item.row - BufferRows) * CellSize + GapSize + OffSet;
			DrawPowerUp(pBlock->powerup, x, y, (pBlock->id > 8));
		}
	}
}
void Game::DrawBlockUI(Block* pBlock, int offX, int offY)
{
	pBlock->DrawUI(offX, offY);
	if (!powerupsEnabled) return;
	if (pBlock->powerup != BlockNormal)
	{
		std::vector<Position> tiles = pBlock->GetCellPositions();
		for (Position item : tiles)
		{
			int x = item.column * CellSize + GapSize + OffSet + offX;
			int y = item.row * CellSize + GapSize + OffSet + offY;
			DrawPowerUp(pBlock->powerup, x,y, (pBlock->id > 8));
		}
	}
}
void Game::UpdateAnimations()
{
	FireAnimation.Update();
}


#ifdef bals
void Game::DrawPowerUp(PowerupType powerup, int x, int y, bool isShadow){}
#endif
void Game::DrawPowerUp(PowerupType powerup, int x, int y, bool isShadow)
{

	Color color;
	if (isShadow)
	{
		color = {255, 255, 255, cshadow;
	}
	else
	{
		color = {255, 255, 255, cnormal;
	}
	switch (powerup)
	{
	case BlockNormal:
		DrawTexture(NormalPowerup, x, y, color);
		break;
	case BlockFreeze:
		DrawTexture(FreezePowerup, x, y, color);
		break;
	case BlockBomb:
		DrawTexture(BombPowerup, x, y, color);
		break;
	case BlockLineBomb:
		DrawTexture(LineBombPowerup, x, y, color);
		break;
	case BlockColorBomb:
		DrawTexture(ColorBombPowerup, x, y, color);
		break;
	case BlockFire:
		FireAnimation.Draw(x,y ,color);
		//DrawTextureRec(FirePowerup, frameRec, {static_cast<float>(x),static_cast<float>(y) }, color);
		//DrawTexture(FirePowerup, x, y, color);
		break;
	case BlockSand:
		DrawTexture(SandPowerup, x, y, color);
		break;
	default:
		break;
	}
}

void Game::DrawGridMenu(bool powerups, int xOffset, int yOffset)
{
	for (size_t r = BufferRows; r < Rows; r++)
	{
		for (size_t c = 0; c < Columns; c++)
		{
			int cellValue = grid.grid[r][c];
			int x = c * CellSize + GapSize + OffSet;
			int y = (r - BufferRows) * CellSize + GapSize + OffSet;

			x += xOffset;
			y += yOffset;
			cellValue += 9;

			int w = CellSize - GapSize;
			int h = CellSize - GapSize;
			DrawRectangle(x, y, w, h, currentBlock.colors[cellValue]);

			if (powerups)
			{
				PowerupType cellValue = grid.powerups[r][c];
				DrawPowerUp(cellValue, x, y, true);
			}
		}
	}
}

void Game::DrawGrid()
{
	grid.Draw();
	if (!powerupsEnabled) return;
	for (size_t r = BufferRows; r < Rows; r++)
	{
		for (size_t c = 0; c < Columns; c++)
		{
			PowerupType cellValue = grid.powerups[r][c];
			int x = c * CellSize + GapSize + OffSet;
			int y = (r - BufferRows) * CellSize + GapSize + OffSet;

			DrawPowerUp(cellValue, x, y, false);
		}
	}
}

void Game::TitleGrid()
{
	Reset();
	powerupsEnabled = true;

	for (size_t i = 0; i < 20; i++)
	{
		currentBlock = GetRandomBlock();
		if (currentBlock.id == 8) //skip the single block
		{
			i--;
			continue;
		}

		int directionChoise[2]{ -1, 1 };
		int direction = directionChoise[GetRandomValue(0,1)];
		int cells = GetRandomValue(0, Columns/2);

		if (direction > 0)
		{
			RotateRight();
			for (size_t j = 0; j < cells; j++)
			{
				MoveBlockRight();
			}
		}
		else
		{
			RotateLeft();
			for (size_t j = 0; j < cells; j++)
			{
				MoveBlockLeft();
			}
		}

		ApplyShadow();
		DropBlockDown();
		LockBlock();
	}

	powerupsEnabled = false;
}

void Game::Draw()
{
	DrawGrid();

	if (sandBlockSplitted)
	{
		for (Block block : currentBlocks)
		{
			DrawBlock(&block);
		}
	}
	else
	{
		DrawBlock(&currentBlock);
		DrawBlock(&currentBlockShadow);
	}
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
	if (gameOver || sandBlockSplitted)
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


	if (keyPressed == KEY_H)
	{
		currentBlock.powerup = BlockSand;
	}
	if (keyPressed == KEY_U)
	{
		Reset();
	}

	if (gameOver || sandBlockSplitted)
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
	if (gameOver || sandBlockSplitted)
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
	if (gameOver || sandBlockSplitted)
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
	if (gameOver || sandBlockSplitted)
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
	if (gameOver)
	{
		return;
	}
	if (sandBlockSplitted)
	{
		for (auto it = currentBlocks.begin(); it != currentBlocks.end();)
		{
			it->Move(1, 0);

			if (IsBlockOutside(&(*it)) || !BlockFits(&(*it)))
			{
				it->Move(-1, 0);
				sandBlocksLocked++;
				for (Position item : it->GetCellPositions())
				{
					grid.grid[item.row][item.column] = it->id;
					grid.powerups[item.row][item.column] = it->powerup;
				}
				it = currentBlocks.erase(it); // Erase and get the next iterator
			}
			else
			{
				++it;
			}
		}
		if (currentBlocks.empty())
		{
			LockBlock();
		}
	}
	else
	{
		Move(1, 0);
		if (IsBlockOutside(&currentBlock) || !BlockFits(&currentBlock))
		{
			Move(-1, 0);
			LockBlock();
		}
	}
}

void Game::RotateLeft()
{
	if (gameOver || sandBlockSplitted)
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
	if (gameOver || sandBlockSplitted)
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

	if (!sandBlockSplitted)
	{
		if (currentBlock.powerup == BlockSand)
		{
			// Sort the vector using std::sort and the custom comparator
			std::sort(tiles.begin(), tiles.end(), [](Position& a, Position& b) { return a.row > b.row; });

			currentBlocks = std::vector<Block>();
			for (auto tile : tiles)
			{
				Block tileBlock = DBlock();
				tileBlock.rowOffset = tile.row;
				tileBlock.colummnOffset = tile.column;
				tileBlock.id = currentBlock.id;
				tileBlock.powerup = currentBlock.powerup;
				currentBlocks.push_back(tileBlock);
			}
			sandBlockSplitted = true;
			sandBlocksLocked = 0;
			return;
		}

		for (Position item : tiles)
		{
			grid.grid[item.row][item.column] = currentBlock.id;
			grid.powerups[item.row][item.column] = currentBlock.powerup;
		}
	}
	else
	{
		sandBlockSplitted = false;
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
	UpdateGameSpeed(rowsCleared);
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
	gameSpeed = baseSpeed;
	gameOver = false;
	sandBlockSplitted = false;
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
