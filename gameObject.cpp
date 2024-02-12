#include "Gameobject.h"

void newXY(point arr[3], int d);
int columnCheck(point arr[5][5], int dir);
bool rotationcheck(board gb, point cord[3], point shap[5][5], int dir);
void Deletion(point cord[3], point shap[5][5]);

/*A function that gets the player number,
and accordingly resets its shape coordinates to the corresponding board and side. */
void gameobject::initXY(int& p)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 10; col > cols; col--)
		{
			if (p == 1)
				this->object[row][col - 6].initXY(col + offSetColPlayer2, row);
			else
				this->object[row][col - 6].initXY(col + offSetColPlayer1, row);
		}
	}
}

void gameobject::DemoinitXY(int p,int offSet)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 10; col > cols; col--)
		{
			if (p == 1)
				this->object[row][col - 6].initXY(col + offSetColPlayer2 + offSet, row);
			else
				this->object[row][col - 6].initXY(col + offSetColPlayer1 + offSet, row);
		}
	}
}
void gameobject::printObject()//We will print the object only for the non-empty spaces,
//to avoid incorrect deletion of shapes on the screen. 
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (this->object[row][col].getChar() != ' ')
				this->object[row][col].draw();
		}
	}
}
/*Functions that create the constant arry of shapes */
/********************************************************/
void gameobject::creatI()//The pivot point is (2,2)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (row == 2 && col != 0)
				this->object[row][col].initChar(Square);
		}
	}

}

void gameobject::creatJ()//The pivot point is (2,2)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (row == 3 && col == 1)
				this->object[row][col].initChar(Square);
			else if (col == 2 && row < 4 && row > 0)
				this->object[row][col].initChar(Square);
		}
	}
}

void gameobject::creatL()//The pivot point is (2,2)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (row == 3 && col == 3)
				this->object[row][col].initChar(Square);
			else if (col == 2 && row < 4 && row > 0)
				this->object[row][col].initChar(Square);
		}
	}
}

void gameobject::creatO()//The pivot point is (2,2)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (row == col && row < 4 && row > 1)
				this->object[row][col].initChar(Square);
			else if ((col == 3 || col == 2) && row < 4 && row > 1)
				this->object[row][col].initChar(Square);
		}
	}
}

void gameobject::creatS()//The pivot point is (2,2)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (col == 2 && row < 3 && row > 0)
				this->object[row][col].initChar(Square);
			else if (col == 3 && row > 1 && row < 4)
				this->object[row][col].initChar(Square);
		}
	}
}

void gameobject::creatT()//The pivot point is (2,2)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (col == 2 && row > 0 && row < 4)
				this->object[row][col].initChar(Square);
			else if (row == 2 && col == 3)
				this->object[row][col].initChar(Square);
		}
	}
}

void gameobject::creatZ()//The pivot point is (2,2)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (col == 2 && row > 1 && row < 4)
				this->object[row][col].initChar(Square);
			else if (col == 3 && row > 0 && row < 3)
				this->object[row][col].initChar(Square);
		}
	}
}
/********************************************************/

/*The function receives the selected shape from the array of shapes and the rotation version of that shape.
And depending on the locations of the squares of the shape and depending on the type selected,
the squares in the new coordinates will be inserted into the object according to the chosen version. */
void gameobject::initStarting(const gameobject g, int& d)

{
	point cord[3];//Array of the new coordinates 
	int num = 0;
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (g.object[row][col].getChar() != ' ')
			{
				if (row == 2 && col != 2 || row != 2)//The pivot point never changes 
				{
					cord[num].initXY(col, row);
					num++;
				}
			}
		}
	}
	newXY(cord, d);
	this->object[cord[0].getY()][cord[0].getX()].initChar(Square);
	this->object[cord[1].getY()][cord[1].getX()].initChar(Square);
	this->object[cord[2].getY()][cord[2].getX()].initChar(Square);
	this->object[2][2].initChar(Square);
}

/*Calculate the new coordinates of the shape after rotation clockwise */
/*If the parameter d is 0 there will be no change and we will take the shape as it appears in the array of shaps */
void newXY(point arr[3], int d)
{
	if (d = !0)
	{
		for (int i = 0; i < d; i++)
		{
			arr[0].XYClockwiserotation();
			arr[1].XYClockwiserotation();
			arr[2].XYClockwiserotation();
		}
	}
}

void gameobject::TheBomb()
{
	object[2][2].initChar(04);
}

/*The function calculates the new cortinettes after rotation,
inserts the squares into these points in the array and deletes the squares in the old places. */
void gameobject::rotation(int dir, board& gameboard)
{
	point cord[3];//Array of the new coordinates 
	int num = 0;
	if (this->Lowbordercheck(gameboard))//If the shape is about to stop we do not want it to rotate because it can create a collision 
	{
		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				if (this->object[row][col].getChar() != ' ')
				{
					if (row == 2 && col != 2 || row != 2)//The pivot point never changes 
					{
						cord[num].initXY(col, row);
						num++;
					}
				}
			}
		}
		/*We will examine whether the coordinates after the rotation create
		a collision with another shape if it does, we do not allow the rotation. */
		if (rotationcheck(gameboard, cord, this->object, dir))
		{
			if (dir == 0)//Clockwise 
			{
				cord[0].XYClockwiserotation();
				cord[1].XYClockwiserotation();
				cord[2].XYClockwiserotation();
			}
			else//counterclockwise
			{
				cord[0].XYRotationcounterclockwise();
				cord[1].XYRotationcounterclockwise();
				cord[2].XYRotationcounterclockwise();
			}
		}

		this->object[cord[0].getY()][cord[0].getX()].initChar(Square);
		this->object[cord[1].getY()][cord[1].getX()].initChar(Square);
		this->object[cord[2].getY()][cord[2].getX()].initChar(Square);
	}

}

/*The function checks whether the rotation is valid */
bool rotationcheck(board gb, point cord[3], point shap[5][5], int dir)
{
	point temp;
	int row, col;
	for (int i = 0; i < 3; i++)
	{
		temp.initXY(cord[i].getX(), cord[i].getY());
		if (dir == 0)//Clockwise 
		{
			temp.XYClockwiserotation();
		}
		else//counterclockwise
		{
			temp.XYRotationcounterclockwise();
		}
		row = shap[temp.getY()][temp.getX()].getY();
		col = shap[temp.getY()][temp.getX()].getX();
		if (gb.cheakRotation(row, col) != true)
			return false;
		row = shap[cord[i].getY()][cord[i].getX()].getY();
		col = shap[cord[i].getY()][cord[i].getX()].getX();
		/*Checks if the shape is too close to another shape and its rotation can collide with it. */
		if (dir == 0)
		{
			if (gb.cheakRotation(row, (col - 1)) != true)
				return false;
		}
		else
		{
			if (gb.cheakRotation(row, (col + 1)) != true)
				return false;
		}
	}
	Deletion(cord, shap);
	return true;

}
/*Deleting the points before the rotation if the rotation is valid */
void Deletion(point cord[3], point shap[5][5])
{
	for (int i = 0; i < 3; i++)
	{
		shap[cord[i].getY()][cord[i].getX()].initChar(' ');
		shap[cord[i].getY()][cord[i].getX()].Delite();
	}
}

/*The function checks according to the direction it receives from the player,
whether the movement is legal and if so does it */
void gameobject::move(char& ch, board& gameBoard)
{
	int col;
	if (ch == 'a' || ch == 'A' || ch == 'j' || ch == 'J')//move to the left
	{
		if (this->object[0][(col = columnCheck(this->object, left))].checkLimits(left))//Check if the shape stays within the boundaries after moving 
		{
			int x, y;
			x = this->object[0][col].getX();
			if (x > offSetColPlayer2)//is it player 2
				x = x - offSetColPlayer2;
			else//player 1
				x = x - offSetColPlayer1;
			y = this->object[0][col].getY();
			if (gameBoard.checkBoardCol(y - offSetRow, x, left))
			{
				if (this->Lowbordercheck(gameBoard))//Check if the shape needs to stop 
				{
					for (int row = 0; row < rows; row++)
					{
						for (int col = 0; col < cols; col++)
						{
							this->object[row][col].move(left);
							if (this->object[row][col].getChar() != ' ')
								this->object[row][col].DeliteMove(left);
						}
					}
				}
			}
		}
	}
	if (ch == 'd' || ch == 'D' || ch == 'l' || ch == 'L')//move to the right
	{
		if (this->object[0][(col = columnCheck(this->object, right))].checkLimits(2))
		{
			int x, y;
			x = this->object[0][col].getX();
			if (x > offSetColPlayer2)
				x = x - offSetColPlayer2;
			else
				x = x - offSetColPlayer1;
			y = this->object[0][col].getY();
			if (gameBoard.checkBoardCol(y - offSetRow, x, right))
			{
				if (this->Lowbordercheck(gameBoard))//Check if the shape needs to stop 
				{
					for (int row = 0; row < rows; row++)
					{
						for (int col = 0; col < cols; col++)
						{
							this->object[row][col].move(right);
							if (this->object[row][col].getChar() != ' ')
								this->object[row][col].DeliteMove(right);
						}
					}
				}
			}
		}
	}
}

/*Returns the column number for which not all cells are empty */
int gameobject :: columnCheck(point arr[5][5], int dir)
{
	if (dir == 1)//from the left
	{
		for (int col = 0; col < cols; col++)
		{
			for (int row = rows - 1; row >= 0; row--)
			{
				if (arr[row][col].getChar() != ' ')
					return col;
			}
		}
	}
	else//from the right
	{
		for (int col = 4; col >= 0; col--)
		{
			for (int row = rows - 1; row >= 0; row--)
			{
				if (arr[row][col].getChar() != ' ')
					return col;
			}
		}
	}
}

/*A function that creates the falling motion of the shape */
void gameobject::falling(int& nPos)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{

			this->object[row][col].falling();
			if (this->object[row][col].getChar() != ' ')
			{
				if (this->object[row - 1][col].getChar() == ' ')
					this->object[row][col].Delitefall();
				else if((row==0) && (nPos==0))
					this->object[row][col].Delitefall();
				this->object[row][col].draw();
			}
		}
	}
}

/*A function that checks whether the shape should stop,
that is, whether there is another shape below it or whether it has reached the lower
border of the board. */
bool gameobject::Lowbordercheck(board& player_board)
{
	for (int row = rows - 1; row >= 0; row--)
	{
		for (int col = 0; col < cols; col++)
		{
			if (this->object[row][col].getChar() != ' ')
			{
				if (player_board.checkBoard(this->object[row][col].getY() + 1, this->object[row][col].getX()) != true)//First we will check if the next place below the shape is free on the board 
					return false;
				if (this->object[row][col].Lowbordercheck() != true)//We will check if the shape has reached the bottom of the board 
					return false;
			}
		}
	}
	return true;
}

/*A function that resets a shape */
void gameobject::deliteShap()
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			this->object[row][col].initChar(empty_space);
		}
	}
}
/*Function that updates the board after a shap stoped */
void gameobject::BoardUpdate(board& Board,char color, int count)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (this->object[row][col].getChar() != empty_space)
				Board.BoardUpdate(this->object[row][col].getY(), this->object[row][col].getX(),color,count);
		}
	}
}
/*Function that checks whether the coordinates of one of the shapes,
need to be changed so that they fall from same height */
int gameobject::isOffSetNeeded()
{
	int row = rows - 1;
	int col = 0;
	while (object[row][col].getChar() == empty_space)//The loop finds the lowest row that has a block in the shap
	{
		col++;
		if (col == cols)
		{
			col = 0;
			row--;
		}
	}
	return row;
}

/*A function that lowers the shape in one more row that will match the other shape.*/
void gameobject::offSetStarting()
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			object[row][col].falling();
		}
	}
}

/*A function that makes the drop of the shape,
it uses the same function of the fall but we reduce the sleep
so the fall is done faster and hence the drop effect.
The function will return the true when performed drop,
so in the main loop we will know not to check whether the form should be stopped
because Drop's condition is the same condition.
And thus did it will not re-enter the same function later. */
bool gameobject::Drop(board& player_bord, int& nPos)
{
	while (this->Lowbordercheck(player_bord))
	{
		this->falling(nPos);
		Sleep(10);
	}
	return true;
}

bool gameobject::DemoDrop(board& player_bord, int& nPos)
{
	while (this->Lowbordercheck(player_bord))
	{
		this->DemoFalling(nPos);
	}
	return true;
}

void gameobject::DemoFalling(int& nPos)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{

			this->object[row][col].falling();
			if (this->object[row][col].getChar() != ' ')
			{
				if (this->object[row - 1][col].getChar() == ' ')
					this->object[row][col].Delitefall();
				else if ((row == 0) && (nPos == 0))
					this->object[row][col].Delitefall();
			}
		}
	}
}

