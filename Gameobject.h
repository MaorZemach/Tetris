#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "point.h"
#include "board.h"
#include <conio.h>
#include <iostream>

const unsigned char Square = 178;
const int rows = 5;
const int cols = 5;
using std::cout;
using std::cin;
using std::endl;
void gotoxy(int, int);


class gameobject
{
private:
	enum {left = 1,right = 2,offSetColPlayer2 = 19, offSetColPlayer1 = 2, offSetRow = 5,empty_space=' '};
	/*We make a 5-by-5 two-dimensional array to make the pivot point clear,
	and the shape rotation simpler*/
	point object[rows][cols];
	

public:
	void initXY(int& p);
	void creatI();
	void creatJ();
	void creatL();
	void creatO();
	void creatS();
	void creatT();
	void creatZ();
	void printObject();
	void initStarting(const gameobject g, int& d);//Creates the initial shape
	void rotation(int dir, board& gamebord);
	void move(char& ch, board& gameBord);
	int columnCheck(point arr[5][5], int dir);
	//void falling(bord player_bord);
	void falling(int& nPos);
	bool Lowbordercheck(board& player_bord);
	void deliteShap();
	void BoardUpdate(board& Bord,char color, int count);
	int isOffSetNeeded();
	void offSetStarting();
	bool Drop(board& player_bord, int& nPos);
	void TheBomb();
	bool DemoDrop(board& player_bord, int& nPos);
	void DemoFalling(int& nPos);
	void DemoinitXY(int p,int offSet);
	inline int Getx(int row, int col)
	{
		return (object[row][col].getX());
	}
	inline int Gety(int row, int col)
	{
		return (object[row][col].getY());
	}
	inline int GetCol(int dir)
	{
		int col;
		col = this->columnCheck(object, dir);
		col = object[0][col].getX();
		if (col > offSetColPlayer2)
			return (col - offSetColPlayer2);
		else
			return (col - offSetColPlayer1);
	}

};

#endif