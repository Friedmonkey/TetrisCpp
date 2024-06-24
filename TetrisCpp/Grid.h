#pragma once
#include "Settings.h"
#include "PowerupType.h"

class Grid
{
public:
	Grid();
	void Initialize();
	void Draw();
	bool IsCellOutside(int row, int column);
	bool IsCellEmpty(int row, int column);
	int ClearFullRows();
	int grid[Rows][Columns];
	PowerupType powerups[Rows][Columns];
private:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int amount);

	std::vector<Color> colors;
};

