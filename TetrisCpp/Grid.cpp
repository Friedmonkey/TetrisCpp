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
			DrawRectangle(c*CellSize+GapSize+OffSet, r*CellSize+GapSize+OffSet, CellSize-GapSize, CellSize-GapSize, colors[cellValue]);
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

bool Grid::IsCellEmpty(int row, int column)
{
	if (grid[row][column] == 0)
	{
		return true;
	}
	return false;
}

int Grid::ClearFullRows()
{
	int completed {0};
	for (int row = (Rows - 1); row >= 0; row--)
	{
		if (IsRowFull(row))
		{
			ClearRow(row);
			completed++;
		}
		else if (completed > 0)
		{
			MoveRowDown(row, completed);
		}
	}
	return completed;
}

bool Grid::IsRowFull(int row)
{
	for (size_t column = 0; column < Columns; column++)
	{
		if (grid[row][column] == 0)
		{
			return false;
		}
	}
	return true;
}

void Grid::ClearRow(int row)
{
	for (size_t column = 0; column < Columns; column++)
	{
		grid[row][column] = 0;
	}
}

void Grid::MoveRowDown(int row, int amount)
{
	for (size_t column = 0; column < Columns; column++)
	{
		grid[row + amount][column] = grid[row][column];
		grid[row][column] = 0;
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