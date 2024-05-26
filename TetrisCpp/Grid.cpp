#include "Grid.h"
#include <iostream>

Grid::Grid()
{
	Initialize();
	colors = GetCellColors();
}

std::vector<Color> Grid::GetCellColors()
{
	Color darkGrey = { 26, 31, 40, 255 };
	Color green = { 47, 230, 23, 255 };
	Color red = { 232, 18, 18, 255 };
	Color orange = { 226, 116, 17, 255 };
	Color yellow = { 237, 234, 4, 255 };
	Color purple = { 166, 0, 247, 255 };
	Color cyan = { 21, 204, 209, 255 };
	Color blue = { 13, 64, 216, 255 };

	return { darkGrey, green, red, orange, yellow, purple, cyan, blue };
}

void Grid::Draw()
{
	for (size_t r = 0; r < Rows; r++)
	{
		for (size_t c = 0; c < Columns; c++)
		{
			int cellValue = grid[r][c];
			DrawRectangle(c*CellSize, r*CellSize, CellSize, CellSize, colors[cellValue]);
		}
	}
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