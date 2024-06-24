#include "Block.h"

Block::Block()
{
	rotationState = 0;
	colors = GetCellColors();

	id = 0;
	colummnOffset = 0;
	rowOffset = 0;
	powerup = BlockNormal;
}

void Block::Draw()
{
	std::vector<Position> tiles = GetCellPositions();
	for (Position item: tiles)
	{
		if (item.row < BufferRows)
		{
			continue;
		}
		int x = item.column * CellSize + GapSize + OffSet;
		int y = (item.row-BufferRows)*CellSize+GapSize+OffSet;
		int w = CellSize - GapSize;
		int h = CellSize - GapSize;
		DrawRectangle(x, y, w, h, colors[id]);
	}
}

void Block::DrawUI(int offsetX, int offsetY)
{
	std::vector<Position> tiles = GetCellPositions();
	for (Position item : tiles)
	{
		int x = item.column * CellSize + GapSize + OffSet + offsetX;
		int y = item.row * CellSize + GapSize + OffSet + offsetY;
		int w = CellSize - GapSize;
		int h = CellSize - GapSize;

		DrawRectangle(x, y, w, h, colors[id]);
	}
}

void Block::Move(int rows, int columns)
{
	rowOffset += rows;
	colummnOffset += columns;
}

std::vector<Position> Block::GetCellPositions()
{
	std::vector<Position> tiles = cells[rotationState];
	std::vector<Position> movedTiles;
	for (Position item : tiles)
	{
		Position newPos = Position(item.row + rowOffset, item.column + colummnOffset);
		movedTiles.push_back(newPos);
	}
	return movedTiles;
}

void Block::RotateRight()
{
	rotationState++;
	if (rotationState == (int)cells.size())
	{
		rotationState = 0;
	}
}


void Block::RotateLeft()
{
	rotationState--;
	if (rotationState == -1)
	{
		rotationState = (int)cells.size() - 1;
	}
}
