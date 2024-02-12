#ifndef _GOTOXY_H_
#define _GOTOXY_H_

#include <iostream>
#include <windows.h>
#include <process.h>
using std::cout;
// function definition -- requires windows.h
inline void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
#endif
