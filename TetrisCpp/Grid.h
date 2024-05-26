#pragma once
#include "Settings.h"

class Grid
{
public:
	Grid();
	void Initialize();
	void Print();
	void Draw();
	bool IsCellOutside(int row, int column);
	int grid[Rows][Columns];
private:
	std::vector<Color> colors;
};

