#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include <conio.h>
#include "gotoxy.h"


void gotoxy(int, int);

class point {
private:
	int x, y;
	char ch = ' ';
	
public:
	enum { minX_p1 = 2, maxX_p1 = 15, maxY = 23, minX_p2 = 19, maxX_p2 = 32 };
	void draw();
	void initChar(char c);
	void initXY(int a, int b);
	void XYClockwiserotation();
	void XYRotationcounterclockwise();
	void move(int dir);
	void DeliteMove(int dir);
	void Delitefall();
	void Delite();
	bool Lowbordercheck();
	bool checkLimits(int dir);
	void falling();
	/*Because the parameters are private we will write functions that return the value from the class */
	inline char getChar() const
	{
		return ch;
	}
	inline int getX() const
	{
		return x;
	}
	inline int getY() const
	{
		return y;
	}
	
};

#endif
