#pragma once
#include "Settings.h"

#include <Map>
#include "Position.h"

class Block
{
public:
	Block();
	void Draw();
	int id;
	std::map<int, std::vector<Position>> cells;
private:
	int rotationState;
	std::vector<Color> colors;
};

