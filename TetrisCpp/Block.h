#pragma once
#include "Settings.h"

#include <Map>
#include "Position.h"

class Block
{
public:
	Block();
	void Draw(int offsetX, int offsetY);
	void DrawUI(int offsetX, int offsetY);
	void Move(int rows, int columns);
	std::vector<Position> GetCellPositions();
	void RotateRight();
	void RotateLeft();
	int id;
	std::map<int, std::vector<Position>> cells;

	int rowOffset;
	int colummnOffset;
private:
	int rotationState;
	std::vector<Color> colors;
};

