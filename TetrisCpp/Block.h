#pragma once
#include <Vector>
#include <Map>
#include "Position.h"

class Block
{
public:
	Block();
	int id;
	std::map<int, std::vector<Position>> cells;
private:
	int cellsize;
	int rotationState;
};

