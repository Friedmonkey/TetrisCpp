#pragma once

#include <Vector>
#include <Raylib.h>

#define BufferRows 3
#define Rows (20 + BufferRows)
#define Columns 10

#define GapSize 3
#define OffSet 10

#define CellSize 35

#define SW Columns*CellSize+GapSize
#define SH (Rows-BufferRows)*CellSize+GapSize



#define LIGHTBLUE Color {59, 85, 162, 255}
#define DARKBLUE Color {44, 44, 127, 255}

#define darkGrey Color { 26, 31, 40,	
#define green Color { 47, 230, 23,
#define red Color { 232, 18, 18,
#define orange Color { 226, 116, 17,	
#define yellow Color { 237, 234, 4,
#define purple Color { 166, 0, 247,
#define cyan Color { 21, 204, 209,
#define blue Color { 13, 64, 216,
#define white Color { 255, 255, 255,

#define cnormal 255 }
#define cshadow 100 }



static std::vector<Color> GetCellColors()
{
	return 
	{
		darkGrey cnormal, green cnormal, red cnormal, orange cnormal, yellow cnormal, purple cnormal, cyan cnormal, blue cnormal, white cnormal,
		darkGrey cshadow, green cshadow, red cshadow, orange cshadow, yellow cshadow, purple cshadow, cyan cshadow, blue cshadow, white cshadow
	};
}

