#ifndef _COLOR_H_
#define _COLOR_H_
#include <windows.h>

enum Color
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGREY = 7,
	DARKGREY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};

inline void setTextColor(Color colorToSet) 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}

inline void setTextColor(int colorToSet)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorToSet);
}


#endif
