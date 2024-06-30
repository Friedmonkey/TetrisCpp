#pragma once
class Position
{
public:
	Position(int row, int column);
	int row;
	int column;
	inline bool operator ==(const Position& other) const
	{
		return (row == other.row) && (column == other.column);
	}
};

