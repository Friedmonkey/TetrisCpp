#pragma once
#include "Settings.h"

class Grid
{
public:
	Grid();
	void Draw();
	void Print();
	void Initialize();
	int grid[Rows][Columns];
private:
	std::vector<Color> colors;
};

