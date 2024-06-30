#pragma once
#include "Settings.h"
#include "PowerupType.h"
#include "Position.h"

class Grid
{
public:
	Grid();
	void Initialize();
	void Draw();
	bool IsCellOutside(int row, int column);
	bool IsCellEmpty(int row, int column);
	int ClearFullRows();
	int LineClearBombRows(std::vector<int> rows);
	int grid[Rows][Columns];
	PowerupType powerups[Rows][Columns];
	std::vector<Position> FindConnectedTNT(int startRow, int startColumn, PowerupType targetPowerup);
	void FloodFillTNT(std::vector<Position>& connectedBlocks, int row, int column, PowerupType targetPowerup, std::vector<std::vector<bool>>& visited);
private:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int amount);

	std::vector<Color> colors;
};

