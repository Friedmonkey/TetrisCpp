#pragma once

#include <Vector>
#include <Raylib.h>

#define Rows 20
#define Columns 10

#define GapSize 3
#define OffSet 10

#define CellSize 35

#define SW Columns*CellSize+GapSize
#define SH Rows*CellSize+GapSize



#define DARKBLUE Color {44, 44, 127, 255}

#define darkGrey Color { 26, 31, 40, 255 }
#define green Color { 47, 230, 23, 255 }
#define red Color { 232, 18, 18, 255 }
#define orange Color { 226, 116, 17, 255 }
#define yellow Color { 237, 234, 4, 255 }
#define purple Color { 166, 0, 247, 255 }
#define cyan Color { 21, 204, 209, 255 }
#define blue Color { 13, 64, 216, 255 }


static std::vector<Color> GetCellColors()
{
	return { darkGrey, green, red, orange, yellow, purple, cyan, blue };
}

