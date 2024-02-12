#include "board.h"
#include <string>
#include "Color.h"


/*The function prints the player's board according to the player's coordinates.
The function gets a number that indicates which player it is. */
void board::ptintboard(int n)
{
	for (int row = 0; row < this->Maxrow + 1; row++)
	{
		for (int col = 0; col < this->Maxcol + 2; col++)
		{
			if (n % 2 == 1)//player 1
			{
				gotoxy(col + offSetColPlayer1, row + offSetRow);
				setTextColor((gamebord[row][col][1]));
				cout << this->gamebord[row][col][0];
			}
			else//player 2
			{
				gotoxy(col + offSetColPlayer2, row + offSetRow);
				setTextColor((gamebord[row][col][1]));
				cout << this->gamebord[row][col][0];
			}
		}
	}
	if (n % 2 == 1)//player 1
	{
		setTextColor(Color::WHITE);
		gotoxy(2, Maxrow + offSetRow);
		cout << std::string(14, lowBorder);

	}
	else//player 2
	{
		setTextColor(Color::WHITE);
		gotoxy(19, Maxrow + offSetRow);
		cout << std::string(14, lowBorder);
	}

}

/*A function that resets the board */
void board::initboared()
{
	for (int row = 0; row < this->Maxrow + 1; row++)
	{
		this->gamebord[row][0][0] = squer;
		this->gamebord[row][0][1] = WHITE;
		this->gamebord[row][0][2] = 0;
		this->gamebord[row][13][0] = squer;
		this->gamebord[row][13][1] = WHITE;
		this->gamebord[row][13][2] = 0;
		for (int col = 1; col <= Maxcol; col++)
		{
			if (row != Maxrow)
			{
				this->gamebord[row][col][0] = empty_space;
				this->gamebord[row][col][1] = WHITE;
				this->gamebord[row][col][2] = 0;
			}
			else
			{
				this->gamebord[row][col][0] = lowBorder;
				this->gamebord[row][col][1] = WHITE;
				this->gamebord[row][col][2] = 0;
			}
		}
	}
}

/*A function that gets coordinates of the falling shape,
and checks whether in the next fall of the shape it will encounter another shape
or the end of the board.
We subtract the rows by 5 because the board is 5 rows below its coordinates,
and in order for it to match the coordinates of the board itself we need to subtract by 5
and depending on the player, subtract by 2 if it is the first player
or by 19 if it is the second player. */
bool board::checkBoard(int row, int col)
{
	char c = gameSquer;
	if (col > offSetColPlayer2)
	{
		if (this->gamebord[row - offSetRow][col - offSetColPlayer2][0] == c)
			return false;
		else if (this->gamebord[row - offSetRow][col][0] == empty_space || this->gamebord[row - 1][col][0] != squer || this->gamebord[row - 1][col][0] != '_')
			return true;
	}
	else
	{
		if (this->gamebord[row - offSetRow][col - offSetColPlayer1][0] == c)
			return false;
		else if (this->gamebord[row - offSetRow][col][0] == empty_space || this->gamebord[row - 1][col][0] != squer || this->gamebord[row - 1][col][0] != '_')
			return true;
	}
}

/*Depending on the direction of the shape we check whether in the next move
of the shape we will create a collision with another shape or with the board itself. */
bool board::checkBoardCol(int row, int col, int dir)
{
	int temprow = row;
	if (row < 0)
		temprow = 0;
	switch (dir)
	{
	case 1://move to the left
		for (temprow; ((temprow < (row + 5)) && temprow < Maxrow); temprow++)
		{
			if (this->gamebord[temprow][col - 1][0] != empty_space)
				return false;
		}
		return true;
		break;

	case 2://move to the right
		for (temprow; ((temprow < (row + 5)) && temprow < Maxrow); temprow++)
		{
			if (this->gamebord[temprow][col + 1][0] != empty_space)
				return false;
		}
		return true;
		break;
	}
}

/*Updates the board after the shape stops */
void board::BoardUpdate(int row, int col, char color, int count)
{
	if (col > offSetColPlayer2)
	{
		this->gamebord[row - offSetRow][col - offSetColPlayer2][0] = gameSquer;
		this->gamebord[row - offSetRow][col - offSetColPlayer2][1] = color;
		this->gamebord[row - offSetRow][col - offSetColPlayer2][2] = (char)count;
	}
	else
	{
		this->gamebord[row - offSetRow][col - offSetColPlayer1][0] = gameSquer;
		this->gamebord[row - offSetRow][col - offSetColPlayer1][1] = color;
		this->gamebord[row - offSetRow][col - offSetColPlayer1][2] = (char)count;
	}
}

/*The function checks if there are rows to delete after the shape stoped,
if so it will call a function that deletes the row and updates the board.
We will continue to run and check the rows until there are no more rows to delete.
because after deleting one row there may be more rows to delete.
The function will return a Boolean value of true if a row was deleted,
to know whether the board needs to be reprinted to avoid unnecessary flashes of the game. */
bool board::BoardUpdate_line(int& Score, char ch)
{
	bool flage = false;//flag for whether we should continue to check the rows 
	bool returnFlage = false;//A flag indicating whether a row has been deleted and and the board needs to be reprinted
	do {
		flage = true;
		for (int row = Maxrow - 1; row > 0; row--)//Checking the rows is done from the end 
		{
			int col = 1;
			while (col <= Maxcol)
			{
				if (gamebord[row][col][0] == ch)
					break;
				col++;
			}

			if (col == (Maxcol + 1))
			{
				Score += 12;
				DeleteLine(row);
				flage = false;
				returnFlage = true;
			}
		}
	} while (flage == false);

	return returnFlage;
}

/*A function that checks whether we have reached the end of a game */
bool board::IsGameOver()
{

	for (int col = 1; col < Maxcol; col++)
	{
		if (gamebord[0][col][0] != empty_space)
			return true;
	}
	return false;
}

/*A function that deletes the entire row and updates the board */
void board::DeleteLine(int position)
{
	// Moves all the upper lines one row down
	for (int row = position; row > 0; row--)
	{
		for (int col = 1; col <= Maxcol; col++)
		{
			gamebord[row][col][0] = gamebord[row - 1][col][0];
			gamebord[row][col][1] = gamebord[row - 1][col][1];
			gamebord[row][col][2] = gamebord[row - 1][col][2];
		}
	}
}
/*The function deletes from the board all the places that need to be deleted after the bomb */
//void board::Explosion(int row, int col, int n)
void board::Explosion(int row, int col)
{
	int tempRow;
	int tempCol;
	int tempMaxcol;
	if (col > 19)
	{
		tempCol = (col - 19) - 4;
		tempMaxcol = col - 19;
	}
	else
	{
		tempCol = (col - 2) - 4;
		tempMaxcol = col - 2;
	}
	for (; tempCol <= (tempMaxcol + 4); tempCol++)
	{
		if ((tempCol > 0) && (tempCol <= Maxcol))
			for ((tempRow = row - 9); tempRow <= ((row - 5) + 4); tempRow++)
			{
				if ((tempRow >= 0) && (tempRow <= Maxrow))
				{
					gamebord[tempRow][tempCol][0] = empty_space;
					gamebord[tempRow][tempCol][1] = WHITE;
					gamebord[tempRow][tempCol][2] = 0;
				}
			}
		//this->ptintboard(n);
	}
	Sleep(20);

}
/*The function reduces the shapes after the bomb explodes */
void board::UpdateAfterBomb()
{
	int maxRow = 0;
	int col = 1;
	bool flag;
	while (maxRow < Maxrow)//Finding the maximum non-empty row 
	{
		if (gamebord[maxRow][col][0] == empty_space)
		{
			col++;
			if (col > Maxcol)
			{
				col = 1;
				maxRow++;
			}
		}
		else
		{
			break;
		}

	}
	DeleteEmptyRows(maxRow);//Delete empty rows created after the bomb 
	if (maxRow < (Maxrow-1))
	{
		ReductionLeftToRight(maxRow);
		ReductionRightToLeft(maxRow);

	}

}

/*The function goes through each column and looks for whether there is a shap
that needs to be reduced */
void board::ReductionLeftToRight(int maxRow)
{
	bool flag = false;
	bool flagrecu;
	int arr[4][2];
	int arrSize = 0;
	int col = 1;

	for (int col = 1; col <= Maxcol; col++)
	{
		for (int row = (Maxrow - 1); row >= maxRow; row--)
		{
			if ((gamebord[row][col][0] == empty_space) && (flag == false))
			{
				flag = true;
			}
			else if ((flag == true) && (gamebord[row][col][0] == (char)gameSquer))
			{
				flagrecu = CheckIfReductionIsValide(row, col, row, col, arr, arrSize);
				if ((flagrecu == true) && (arrSize > 1))
					sortArr(arr, arrSize);
				while (flagrecu == true)//Work with the array to avoid recursion each time 
				{
					LoweringArr(arr, arrSize);
					flagrecu = IsLoweringValid(arr, arrSize);
				}
				if (arrSize > 0)
				{
					row = arr[arrSize - 1][0];
					arrSize = 0;
					flag = false;
				}
				flag = false;

			}
		}
		//flag = false;
	}

}

void board::ReductionRightToLeft(int maxRow)
{
	bool flag = false;
	bool flagrecu;
	int arr[4][2];
	int arrSize = 0;
	int col = 1;

	for (int col = Maxcol; col > 0; col--)
	{
		for (int row = (Maxrow - 1); row >= maxRow; row--)
		{
			if ((gamebord[row][col][0] == empty_space) && (flag == false))
			{
				flag = true;
			}
			else if ((flag == true) && (gamebord[row][col][0] == (char)gameSquer))
			{
				flagrecu = CheckIfReductionIsValide(row, col, row, col, arr, arrSize);
				if ((flagrecu == true) && (arrSize > 1))
					sortArr(arr, arrSize);
				while (flagrecu == true)
				{
					LoweringArr(arr, arrSize);
					flagrecu = IsLoweringValid(arr, arrSize);
				}
				if (arrSize > 0)
				{
					row = arr[arrSize - 1][0];
					arrSize = 0;
					flag = false;
				}
				flag = false;

			}
		}
		//flag = false;
	}

}

/*Check with the array of the shape after the bomb explodes and reduced
in one row whether it is possible to reduce the shape for another row */
bool board::IsLoweringValid(int(&arr)[4][2], int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		if ((gamebord[arr[i][0] + 1][arr[i][1]][0] != empty_space))
			if (gamebord[arr[i][0] + 1][arr[i][1]][2] != gamebord[arr[i][0]][arr[i][1]][2])
				return false;
		if (arr[i][0] + 1 >= Maxrow)
			return false;
	}
	return true;
}

/*Recursion that finds all the parts that belong to the shape,
keeps them in the array if at all it is possible to reduce the shape at least one row down */
bool board::CheckIfReductionIsValide(int row, int col, int initrow, int initcol, int(&arr)[4][2], int& arrSize)
{
	bool flag = true, down = false;
	if (((gamebord[row + 1][col][0] == (char)gameSquer) || ((row + 1) == Maxrow)) && (gamebord[row + 1][col][2] != gamebord[row][col][2]))
	{
		return false;
	}
	else
	{
		if ((gamebord[row + 1][col][2] == gamebord[row][col][2]) && (((row+1) != initrow)))
		{
			flag = CheckIfReductionIsValide((row + 1), col, row, col, arr, arrSize);
		}
		else if ((gamebord[row + 1][col][0] == empty_space) || (gamebord[row + 1][col][2] == gamebord[row][col][2]))
			down = true;

		if ((gamebord[row][col - 1][2] == gamebord[row][col][2]) && ((col-1) != initcol) && (down == true && flag == true))
		{
			flag = CheckIfReductionIsValide(row, (col - 1), row, col, arr, arrSize);
		}
		if ((gamebord[row][col + 1][2] == gamebord[row][col][2]) && ((col+1) != initcol) && (down == true && flag == true))
		{
			flag = CheckIfReductionIsValide(row, (col + 1), row, col, arr, arrSize);

		}
		if ((gamebord[row - 1][col][2] == gamebord[row][col][2]) && ((row-1) != initrow) && (down == true && flag == true))
		{
			flag = CheckIfReductionIsValide((row - 1), col, row, col, arr, arrSize);
		}

	}
	if (flag == true && down == true)
	{
		arr[arrSize][0] = row;
		arr[arrSize][1] = col;
		arrSize++;
		return true;
	}
}

/*A function that deletes empty rows after the bomb and updates the maximum row accordingly */
void board::DeleteEmptyRows(int& maxRow)//delete the empty rows after the bonb if there is
{
	int row;
	do {
		for (row = (maxRow + 1); row < Maxrow; row++)//Checking the rows is done from the end 
		{
			int col = 1;
			while (col <= Maxcol)
			{
				if (gamebord[row][col][0] == (char)gameSquer)
					break;
				col++;
			}

			if (col == (Maxcol + 1))
			{
				DeleteLineEmpty(row, maxRow);
				maxRow++;
			}
		}
	} while ((maxRow < Maxrow) && (row < Maxrow));
}

void board::DeleteLineEmpty(int position, int maxRow)
{
	// Moves all the upper lines one row down
	for (int row = position; row >= maxRow; row--)
	{
		for (int col = 1; col <= Maxcol; col++)
		{
			gamebord[row][col][0] = gamebord[row - 1][col][0];
			gamebord[row][col][1] = gamebord[row - 1][col][1];
			gamebord[row][col][2] = gamebord[row - 1][col][2];
		}
	}
}
/*A function that lowers the shape that can be lowered after the bomb a row */
void board::LoweringArr(int(&arr)[4][2], int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		gamebord[arr[i][0] + 1][arr[i][1]][0] = gamebord[arr[i][0]][arr[i][1]][0];
		gamebord[arr[i][0] + 1][arr[i][1]][1] = gamebord[arr[i][0]][arr[i][1]][1];
		gamebord[arr[i][0] + 1][arr[i][1]][2] = gamebord[arr[i][0]][arr[i][1]][2];

		gamebord[arr[i][0]][arr[i][1]][0] = empty_space;
		gamebord[arr[i][0]][arr[i][1]][1] = WHITE;
		gamebord[arr[i][0]][arr[i][1]][2] = 0;

		arr[i][0]++;
	}
}
/*Function that sorts the coordinates of a shape that can be lowerd
after the bomb so that the board update is correct */
void sortArr(int(&arr)[4][2], int arrSize)
{
	int i, j;
	int tempRow, tempCol;

	for (i = 0; i < arrSize; i++) {
		for (j = i + 1; j < arrSize; j++)
		{
			if (arr[j][0] >= arr[i][0]) {
				tempRow = arr[i][0];
				tempCol = arr[i][1];
				arr[i][0] = arr[j][0];
				arr[i][1] = arr[j][1];
				arr[j][0] = tempRow;
				arr[j][1] = tempCol;
			}
		}
	}
}


/*A function that checks with the board if the rotation of the shape is valid */
bool board::cheakRotation(int row, int col)
{
	if (col > offSetColPlayer2)
		return ((gamebord[row - offSetRow][col - offSetColPlayer2][0] != (char)gameSquer) && (gamebord[row - offSetRow][col - offSetColPlayer2][0] != (char)squer) && ((col - offSetColPlayer2) <= Maxcol) && ((col - offSetColPlayer2) > 0));
	else
		return ((gamebord[row - offSetRow][col - offSetColPlayer1][0] != (char)gameSquer) && (gamebord[row - offSetRow][col - offSetColPlayer1][0] != (char)squer) && ((col - offSetColPlayer1) <= Maxcol) && ((col - offSetColPlayer1) > 0));
}

bool board::FindNumOfGaps(int row, int col) const
{
	return ((gamebord[row - 1][col][0] != empty_space) && (gamebord[row + 1][col][0] != empty_space) && (gamebord[row][col - 1][0] != empty_space) && (gamebord[row][col + 1][0] != empty_space));
}

int board::HowManyFullRows()
{
	int count = 0;

	for (int row = Maxrow - 1; row > 0; row--)//Checking the rows is done from the end 
	{
		int col = 1;
		while (col <= Maxcol)
		{
			if (gamebord[row][col][0] == empty_space)
				break;
			col++;
		}
		if (col > Maxcol)
			count++;
	}
	return count;
}