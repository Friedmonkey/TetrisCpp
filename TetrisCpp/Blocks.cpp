#include "Settings.h"
#include "Block.h"
#include "Position.h"

#define pos(a,b) Position(a,b)

class LBlock : public Block
{
public:
	LBlock()
	{
		id = 1;
		cells[0] = {pos(0,2), pos(1,0), pos(1,1), pos(1,2)};
		cells[1] = {pos(0,1), pos(1,1), pos(2,1), pos(2,2)};
		cells[2] = {pos(1,0), pos(1,1), pos(1,2), pos(2,0)};
		cells[3] = {pos(0,0), pos(0,1), pos(1,1), pos(2,1)};
	}
};