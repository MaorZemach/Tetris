#ifndef BORD_H
#define BORD_H

#include <conio.h>
#include <iostream>
#include "point.h"



using std::cout;
using std::cin;
using std::endl;
void gotoxy(int, int);
void sortArr(int(&arr)[4][2], int arrSize);

class board
{
private:/*The board size will a row bigger and by 2 columns bigger,
		so that we can insert the boundaries of the board into the board itself for convenience. */
	enum{Maxrow=18, Maxcol=12,empty_space=' ', squer=254, offSetColPlayer2 = 19, offSetColPlayer1 = 2,
		offSetRow = 5, lowBorder='_', gameSquer = 178};
	char gamebord[Maxrow + 1][Maxcol + 2][3];//The board saves 3 parameters, the character of shape, color, and the number of the shape 

public:
	void ptintboard(int n);
	void initboared();
	bool checkBoard(int row, int col);
	bool checkBoardCol(int row, int col, int dir);
	void BoardUpdate(int row, int col, char color,int count);
	bool IsGameOver();
	void DeleteLine(int position);
	bool BoardUpdate_line(int& Score, char ch);
	bool cheakRotation(int row, int col);
	//void Explosion(int row, int col, int n);
	void Explosion(int row, int col);
	void UpdateAfterBomb();
	void DeleteEmptyRows(int& maxRow);
	void DeleteLineEmpty(int position,int maxRow);
	void ReductionLeftToRight(int maxRow);
	void ReductionRightToLeft(int maxRow);
	bool CheckIfReductionIsValide(int row, int col, int initrow, int initcol, int (&arr)[4][2], int &arrSize);
	void LoweringArr(int (&arr)[4][2], int arrSize);
	bool IsLoweringValid(int (&arr)[4][2], int arrSize);
	bool FindNumOfGaps(int row, int col) const;
	inline char GetChar(int row, int col) const
	{
		return gamebord[row][col][0];
	}
	int HowManyFullRows();
};

#endif