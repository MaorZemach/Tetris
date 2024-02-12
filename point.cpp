#include "point.h"
using std::cout;
using std::endl;

void point::draw()//Prints the object on the screen 
{
	gotoxy(x, y);
	cout << ch;
}

void point::Delitefall()//Erasing the trail of the fall 
{
	gotoxy(x, y - 1);
	cout << ' ';
}

void point::Delite()//Deletion 
{
	gotoxy(x, y);
	cout << ' ';
}

void point::DeliteMove(int dir)//Delete the right or left move trail 
{
	if (dir == 1)
	{
		gotoxy(x + 1, y);
		cout << ' ';
	}
	else
	{
		gotoxy(x - 1, y);
		cout << ' ';
	}
}

void point::initChar(char c)//Inserts the desired character into the array (' ' or Square).
{
	ch = c;
}

void point::initXY(int a, int b)//Updating x and y.
{
	x = a;
	y = b;
}

/*We do the rotation of the shapes with the help of the pivot point which is fixed.
We were assisted by the transformation vector of the shape.
That is to say to create a 90 degree rotation we want to look at the vector from the center of the axis
and we will calculate the new coordinates according to the new vector obtained from the rotation. */

/*That is, if the center of the axis is the point of rotation
we would actually like to look at each point from the center of the axis.
so we will subtract from the point the value of the center of the axis in our case is (2,2).
We will then multiply the matrix of the new point by a matrix that helps us calculate the change by 90 degrees.
And then we will want to move the point back to its position relative to the center of the original axis so we will add back to (2,2). */

//The matrices are: 
//Clockwise rotation:
/*| 0 1|
  |-1 0|*/

//counter clockwise:
/*| 0 -1|
  | 1  0|*/

void point::XYClockwiserotation()
{
	int tempX, tempY;
	x = x - 2;
	x = (x * 0) + (x * 1);
	x = x + 2;
	tempX = x;
	
	y = y - 2;
	y = (y * (-1)) + (y * 0);
	y = y + 2;
	tempY = y;

	x = tempY;
	y = tempX;
}

void point::XYRotationcounterclockwise()
{
	int tempX, tempY;
	x = x - 2;
	x = (x * 0) + (x * (-1));
	x = x + 2;
	tempX = x;

	y = y - 2;
	y = (y * 1) + (y * 0);
	y = y + 2;
	tempY = y;

	x = tempY;
	y = tempX;
}

void point::move(int dir)/*Updates the point according to the right or left movement.
						 1 for left shift, 2 for right shift. */
{
	switch(dir)
	{
	case 1://left
			x = x - 1;
		break;

	case 2://right
			x = x + 1;
		break;

	}
}

bool point::checkLimits(int dir)//1 for the left border, 2 for the right border.
{
	switch (dir)
	{
	case 1:
		return (((x - 1) > minX_p1 && (x - 1) < maxX_p1) || ((x - 1) > minX_p2 && (x - 1) < maxX_p2));

	case 2:
		return (((x + 1) > minX_p1 && (x + 1) < maxX_p1) || ((x + 1) > minX_p2 && (x + 1) < maxX_p2));

	}
}

/*Updates the Y of the falling shape, i.e. creates the fall.*/
void point::falling()
{
	y++;
}

/*Check whether the Y after the fall is at the boundary of the board */
bool point::Lowbordercheck()
{
	return ((y + 1) < this->maxY);
}
