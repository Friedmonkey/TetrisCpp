#include "Settings.h"
#include "Block.h"
#include "Position.h"

#define pos(a,b) Position(a,b)
#define center ((Columns/2)-2)

class LBlock : public Block
{
public:
	LBlock()
	{
		id = 1; //green
		cells[0] = {pos(0,2), pos(1,0), pos(1,1), pos(1,2)};
		cells[1] = {pos(0,1), pos(1,1), pos(2,1), pos(2,2)};
		cells[2] = {pos(1,0), pos(1,1), pos(1,2), pos(2,0)};
		cells[3] = {pos(0,0), pos(0,1), pos(1,1), pos(2,1)};
		Move(0, center);

		wallkick[pos(0, 1)] = { pos(0, 0), pos(-1, 0), pos(-1, -1), pos(0, +2), pos(-1, +2) };
		wallkick[pos(1, 0)] = { pos(0, 0), pos(+1, 0), pos(+1, +1), pos(0, -2), pos(+1, -2) };
		wallkick[pos(1, 2)] = { pos(0, 0), pos(+1, 0), pos(+1, +1), pos(0, -2), pos(+1, -2) };
		wallkick[pos(2, 1)] = { pos(0, 0), pos(-1, 0), pos(-1, -1), pos(0, +2), pos(-1, +2) };
		wallkick[pos(2, 3)] = { pos(0, 0), pos(+1, 0), pos(+1, -1), pos(0, +2), pos(+1, +2) };
		wallkick[pos(3, 2)] = { pos(0, 0), pos(-1, 0), pos(-1, +1), pos(0, -2), pos(-1, -2) };
		wallkick[pos(3, 0)] = { pos(0, 0), pos(-1, 0), pos(-1, +1), pos(0, -2), pos(-1, -2) };
		wallkick[pos(0, 3)] = { pos(0, 0), pos(+1, 0), pos(+1, -1), pos(0, +2), pos(+1, +2) };
	}
};

class JBlock : public Block
{
public:
	JBlock()
	{
		id = 2; //red
		cells[0] = { pos(0,0), pos(1,0), pos(1,1), pos(1,2) };
		cells[1] = { pos(0,1), pos(0,2), pos(1,1), pos(2,1) };
		cells[2] = { pos(1,0), pos(1,1), pos(1,2), pos(2,2) };
		cells[3] = { pos(0,1), pos(1,1), pos(2,0), pos(2,1) };
		Move(0, center);

		wallkick[pos(0, 1)] = { pos(0, 0), pos(-1, 0), pos(-1, -1), pos(0, +2), pos(-1, +2) };
		wallkick[pos(1, 0)] = { pos(0, 0), pos(+1, 0), pos(+1, +1), pos(0, -2), pos(+1, -2) };
		wallkick[pos(1, 2)] = { pos(0, 0), pos(+1, 0), pos(+1, +1), pos(0, -2), pos(+1, -2) };
		wallkick[pos(2, 1)] = { pos(0, 0), pos(-1, 0), pos(-1, -1), pos(0, +2), pos(-1, +2) };
		wallkick[pos(2, 3)] = { pos(0, 0), pos(+1, 0), pos(+1, -1), pos(0, +2), pos(+1, +2) };
		wallkick[pos(3, 2)] = { pos(0, 0), pos(-1, 0), pos(-1, +1), pos(0, -2), pos(-1, -2) };
		wallkick[pos(3, 0)] = { pos(0, 0), pos(-1, 0), pos(-1, +1), pos(0, -2), pos(-1, -2) };
		wallkick[pos(0, 3)] = { pos(0, 0), pos(+1, 0), pos(+1, -1), pos(0, +2), pos(+1, +2) };
	}
};

class IBlock : public Block
{
public:
	IBlock()
	{
		id = 3; //orange
		cells[0] = { pos(1,0), pos(1,1), pos(1,2), pos(1,3) };
		cells[1] = { pos(0,2), pos(1,2), pos(2,2), pos(3,2) };
		cells[2] = { pos(2,0), pos(2,1), pos(2,2), pos(2,3) };
		cells[3] = { pos(0,1), pos(1,1), pos(2,1), pos(3,1) };
		Move(-1, center);

		wallkick[pos(0, 1)] = { pos(0, 0), pos(-2, 0), pos(+1, 0), pos(-2, +1), pos(+1, -2) };
		wallkick[pos(1, 0)] = { pos(0, 0), pos(+2, 0), pos(-1, 0), pos(+2, -1), pos(-1, +2) };
		wallkick[pos(1, 2)] = { pos(0, 0), pos(-1, 0), pos(+2, 0), pos(-1, -2), pos(+2, +1) };
		wallkick[pos(2, 1)] = { pos(0, 0), pos(+1, 0), pos(-2, 0), pos(+1, +2), pos(-2, -1) };
		wallkick[pos(2, 3)] = { pos(0, 0), pos(+2, 0), pos(-1, 0), pos(+2, -1), pos(-1, +2) };
		wallkick[pos(3, 2)] = { pos(0, 0), pos(-2, 0), pos(+1, 0), pos(-2, +1), pos(+1, -2) };
		wallkick[pos(3, 0)] = { pos(0, 0), pos(+1, 0), pos(-2, 0), pos(+1, +2), pos(-2, -1) };
		wallkick[pos(0, 3)] = { pos(0, 0), pos(-1, 0), pos(+2, 0), pos(-1, -2), pos(+2, +1) };

	}
};

class OBlock : public Block
{
public:
	OBlock()
	{
		id = 4; //yellow
		cells[0] = { pos(0,0), pos(0,1), pos(1,0), pos(1,1) };
		//cells[1] = { pos(0,0), pos(0,1), pos(1,0), pos(1,1) };
		//cells[2] = { pos(0,0), pos(0,1), pos(1,0), pos(1,1) };
		//cells[3] = { pos(0,0), pos(0,1), pos(1,0), pos(1,1) };
		Move(0, center+1);

		wallkick[pos(0, 1)] = { pos(0, 0) };
		wallkick[pos(1, 0)] = { pos(0, 0) };
		wallkick[pos(1, 2)] = { pos(0, 0) };
		wallkick[pos(2, 1)] = { pos(0, 0) };
		wallkick[pos(2, 3)] = { pos(0, 0) };
		wallkick[pos(3, 2)] = { pos(0, 0) };
		wallkick[pos(3, 0)] = { pos(0, 0) };
		wallkick[pos(0, 3)] = { pos(0, 0) };
	}
};

class SBlock : public Block
{
public:
	SBlock()
	{
		id = 5; //purple
		cells[0] = { pos(0,1), pos(0,2), pos(1,0), pos(1,1) };
		cells[1] = { pos(0,1), pos(1,1), pos(1,2), pos(2,2) };
		cells[2] = { pos(1,1), pos(1,2), pos(2,0), pos(2,1) };
		cells[3] = { pos(0,0), pos(1,0), pos(1,1), pos(2,1) };
		Move(0, center);

		wallkick[pos(0, 1)] = { pos(0, 0), pos(-1, 0), pos(-1, -1), pos(0, +2), pos(-1, +2) };
		wallkick[pos(1, 0)] = { pos(0, 0), pos(+1, 0), pos(+1, +1), pos(0, -2), pos(+1, -2) };
		wallkick[pos(1, 2)] = { pos(0, 0), pos(+1, 0), pos(+1, +1), pos(0, -2), pos(+1, -2) };
		wallkick[pos(2, 1)] = { pos(0, 0), pos(-1, 0), pos(-1, -1), pos(0, +2), pos(-1, +2) };
		wallkick[pos(2, 3)] = { pos(0, 0), pos(+1, 0), pos(+1, -1), pos(0, +2), pos(+1, +2) };
		wallkick[pos(3, 2)] = { pos(0, 0), pos(-1, 0), pos(-1, +1), pos(0, -2), pos(-1, -2) };
		wallkick[pos(3, 0)] = { pos(0, 0), pos(-1, 0), pos(-1, +1), pos(0, -2), pos(-1, -2) };
		wallkick[pos(0, 3)] = { pos(0, 0), pos(+1, 0), pos(+1, -1), pos(0, +2), pos(+1, +2) };
	}
};

class TBlock : public Block
{
public:
	TBlock()
	{
		id = 6; //cyan
		cells[0] = { pos(0,1), pos(1,0), pos(1,1), pos(1,2) };
		cells[1] = { pos(0,1), pos(1,1), pos(1,2), pos(2,1) };
		cells[2] = { pos(1,0), pos(1,1), pos(1,2), pos(2,1) };
		cells[3] = { pos(0,1), pos(1,0), pos(1,1), pos(2,1) };
		Move(0, center);

		wallkick[pos(0, 1)] = { pos(0, 0), pos(-1, 0), pos(-1, -1), pos(0, +2), pos(-1, +2) };
		wallkick[pos(1, 0)] = { pos(0, 0), pos(+1, 0), pos(+1, +1), pos(0, -2), pos(+1, -2) };
		wallkick[pos(1, 2)] = { pos(0, 0), pos(+1, 0), pos(+1, +1), pos(0, -2), pos(+1, -2) };
		wallkick[pos(2, 1)] = { pos(0, 0), pos(-1, 0), pos(-1, -1), pos(0, +2), pos(-1, +2) };
		wallkick[pos(2, 3)] = { pos(0, 0), pos(+1, 0), pos(+1, -1), pos(0, +2), pos(+1, +2) };
		wallkick[pos(3, 2)] = { pos(0, 0), pos(-1, 0), pos(-1, +1), pos(0, -2), pos(-1, -2) };
		wallkick[pos(3, 0)] = { pos(0, 0), pos(-1, 0), pos(-1, +1), pos(0, -2), pos(-1, -2) };
		wallkick[pos(0, 3)] = { pos(0, 0), pos(+1, 0), pos(+1, -1), pos(0, +2), pos(+1, +2) };
	}
};

class ZBlock : public Block
{
public:
	ZBlock()
	{
		id = 7; //blue
		cells[0] = { pos(0,0), pos(0,1), pos(1,1), pos(1,2) };
		cells[1] = { pos(0,2), pos(1,1), pos(1,2), pos(2,1) };
		cells[2] = { pos(1,0), pos(1,1), pos(2,1), pos(2,2) };
		cells[3] = { pos(0,1), pos(1,0), pos(1,1), pos(2,0) };
		Move(0, center);

		wallkick[pos(0, 1)] = { pos(0, 0), pos(-1, 0), pos(-1, -1), pos(0, +2), pos(-1, +2) };
		wallkick[pos(1, 0)] = { pos(0, 0), pos(+1, 0), pos(+1, +1), pos(0, -2), pos(+1, -2) };
		wallkick[pos(1, 2)] = { pos(0, 0), pos(+1, 0), pos(+1, +1), pos(0, -2), pos(+1, -2) };
		wallkick[pos(2, 1)] = { pos(0, 0), pos(-1, 0), pos(-1, -1), pos(0, +2), pos(-1, +2) };
		wallkick[pos(2, 3)] = { pos(0, 0), pos(+1, 0), pos(+1, -1), pos(0, +2), pos(+1, +2) };
		wallkick[pos(3, 2)] = { pos(0, 0), pos(-1, 0), pos(-1, +1), pos(0, -2), pos(-1, -2) };
		wallkick[pos(3, 0)] = { pos(0, 0), pos(-1, 0), pos(-1, +1), pos(0, -2), pos(-1, -2) };
		wallkick[pos(0, 3)] = { pos(0, 0), pos(+1, 0), pos(+1, -1), pos(0, +2), pos(+1, +2) };
	}
};