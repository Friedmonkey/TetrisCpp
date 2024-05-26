#pragma once
#include "Settings.h"
#include <Vector>
#include <Raylib.h>

class Grid
{
public:
	Grid();
	void Draw();
	void Print();
	void Initialize();
	int grid[Rows][Columns];
private:
	std::vector<Color> GetCellColors();
	std::vector<Color> colors;
};

