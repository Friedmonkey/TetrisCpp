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
	if (completed > 0)
	{
		//FindConnectedTNT()
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
			for (size_t column = 0; column < Columns; column++)
			{
				grid[row][column] = 0;

				powerups[row][column] = BlockNormal;
			}
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

std::vector<Position> Grid::FindConnectedTNT(int startRow, int startColumn, PowerupType targetPowerup) {
	std::vector<Position> connectedBlocks;
	std::vector<std::vector<bool>> visited(Rows, std::vector<bool>(Columns, false));

	FloodFillTNT(connectedBlocks, startRow, startColumn, targetPowerup, visited);

	return connectedBlocks;
}

void Grid::FloodFillTNT(std::vector<Position>& connectedBlocks, int row, int column, PowerupType targetPowerup, std::vector<std::vector<bool>>& visited) {
	// Directions for checking adjacent cells (up, down, left, right)
	std::vector<Position> directions = {
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}
	};

	// Mark the current cell as visited
	visited[row][column] = true;

	// Check all four adjacent directions
	for (auto dir : directions) {
		int newRow = row + dir.row;
		int newColumn = column + dir.column;

		// Check if the adjacent cell is within bounds and not visited
		if (newRow >= 0 && newRow < Rows && newColumn >= 0 && newColumn < Columns
			&& !visited[newRow][newColumn] && powerups[newRow][newColumn] == targetPowerup) {
			// Recursively flood fill from the adjacent cell
			FloodFillTNT(connectedBlocks, newRow, newColumn, targetPowerup, visited);
		}
	}

	// Add the current position to connectedBlocks if it matches the target powerup
	if (powerups[row][column] == targetPowerup) {
		connectedBlocks.push_back({ row, column });
	}
}
