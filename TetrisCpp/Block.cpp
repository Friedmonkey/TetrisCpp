#include "Block.h"

Block::Block()
{
	rotationState = 0;
	colors = GetCellColors();
}

void Block::Draw()
{
	std::vector<Position> tiles = cells[rotationState];
	for (Position item: tiles)
	{
		DrawRectangle(
			item.column*CellSize+GapSize, 
			item.row*CellSize+GapSize, 
			CellSize-GapSize, 
			CellSize-GapSize, 
			colors[id]
		);
	}
}