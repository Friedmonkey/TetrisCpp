#include "Grid.h"
#include <iostream>

Grid::Grid()
{
	Initialize();
	colors = GetCellColors();
}

void Grid::Draw()
{
	for (size_t r = 0; r < Rows; r++)
	{
		for (size_t c = 0; c < Columns; c++)
		{
			int cellValue = grid[r][c];
			DrawRectangle(c*CellSize+GapSize, r*CellSize+GapSize, CellSize-GapSize, CellSize-GapSize, colors[cellValue]);
		}
	}
}

bool Grid::IsCellOutside(int row, int column)
{
	if (row >= 0 && row < Rows && column >= 0 && column < Columns)
	{
		return false;
	}
	return true;
}


void Grid::Print()
{
	for (size_t r = 0; r < Rows; r++)
	{
		for (size_t c = 0; c < Columns; c++)
		{
			std::cout << grid[r][c] << " ";
		}
		std::cout << std::endl;
	}
}

void Grid::Initialize()
{
	// init the grid to contain full zeros
	for (size_t r = 0; r < Rows; r++)
	{
		for (size_t c = 0; c < Columns; c++)
		{
			grid[r][c] = 0;
		}
	}
}