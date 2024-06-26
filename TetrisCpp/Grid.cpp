#include "Grid.h"

Grid::Grid()
{
	Initialize();
	colors = GetCellColors();
}

void Grid::Draw()
{
	for (size_t r = BufferRows; r < Rows; r++)
	{
		for (size_t c = 0; c < Columns; c++)
		{
			int cellValue = grid[r][c];
			int x = c * CellSize + GapSize + OffSet;
			int y = (r - BufferRows) * CellSize + GapSize + OffSet;
			int w = CellSize - GapSize;
			int h = CellSize - GapSize;
			DrawRectangle(x, y, w, h, colors[cellValue]);
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

int Grid::LineClearBombRows(std::vector<int> rows)
{
	int completed{ 0 };
	for (int row = (Rows - 1); row >= 0; row--)
	{
		if (std::find(rows.begin(), rows.end(), row) != rows.end())
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

		powerups[row][column] = BlockNormal;
	}
}

void Grid::MoveRowDown(int row, int amount)
{
	for (size_t column = 0; column < Columns; column++)
	{
		grid[row + amount][column] = grid[row][column];
		grid[row][column] = 0;

		powerups[row + amount][column] = powerups[row][column];
		powerups[row][column] = BlockNormal;
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
			powerups[r][c] = BlockNormal;
		}
	}
}