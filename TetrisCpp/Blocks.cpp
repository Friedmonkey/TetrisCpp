#include "Settings.h"
#include "Block.h"
#include "Position.h"

#define pos(a,b) Position(a,b)

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
	}
};

class SBlock : public Block
{
public:
	SBlock()
	{
		id = 5; //purple
		cells[0] = { pos(0,1), pos(0,2), pos(1,0), pos(1,1) };
		cells[1] = { pos(0,0), pos(1,1), pos(1,2), pos(2,2) };
		cells[2] = { pos(1,1), pos(1,2), pos(2,0), pos(2,1) };
		cells[3] = { pos(0,0), pos(1,0), pos(1,1), pos(2,1) };
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
	}
};