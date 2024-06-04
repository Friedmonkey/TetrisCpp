#include "Block.h"

Block::Block()
{
	rotationState = 0;
	colors = GetCellColors();

	id = 0;
	colummnOffset = 0;
	rowOffset = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
	std::vector<Position> tiles = GetCellPositions();
	for (Position item: tiles)
	{
		if (item.row < BufferRows)
		{
			continue;
		}
		DrawRectangle(
			item.column*CellSize+GapSize+OffSet, 
			(item.row-BufferRows)*CellSize+GapSize+OffSet,
			CellSize-GapSize, 
			CellSize-GapSize, 
			colors[id]
		);
	}
}

void Block::DrawUI(int offsetX, int offsetY)
{
	std::vector<Position> tiles = GetCellPositions();
	for (Position item : tiles)
	{
		DrawRectangle(
			item.column * CellSize + GapSize + OffSet + offsetX,
			item.row * CellSize + GapSize + OffSet + offsetY,
			CellSize - GapSize,
			CellSize - GapSize,
			colors[id]
		);
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
