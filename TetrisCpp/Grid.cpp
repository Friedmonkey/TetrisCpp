#include "Grid.h"
#include <iostream>

Grid::Grid()
{
	Initialize();
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