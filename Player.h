#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Gameobject.h"
#include <stdlib.h>
#include <time.h> 
#include "Color.h"

int randomizerPos();
int randomizerdir();
int randomizerColer();
int randomizerBomb();


class Player
{
protected:
	enum {numkeys = 10, player1 = 0, player2 = 1, tie = 2};
	int Score;
	char arrowkeys[numkeys];
	//char arrowkeys[numkeys];
	Color Allcolors[14] = {BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGREY,DARKGREY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW};
	Color color;
	gameobject shap;
	int nPos;
	bool bomb = false;
	int count = 0;//Counting the number of shape a player plays with, that is used in bomb tests 
	


public:
	/*We put the shap of the player in public
	so that we would have much simpler access to the shap of the player from different places. */
	void setArrowKeys(const char* keys);
	virtual void initShap(int num_p, gameobject allShaps[7],bool colorsSet,board gameboard);
	virtual char keyOfplayer(char buf[20], int num) = 0;
	void WhatToDo(char key,board gameboard,bool& drop);
	int checkScore(Player& p1, Player& p2);

	inline void initScore()
	{
		Score = 0;
	}

	inline int gerScore() const
	{
		return Score;
	}
	inline void updateScore(int num)
	{
		Score = Score + num;
	}
	inline Color getColor() const
	{
		return color;
	}
	
	inline gameobject getShap() const
	{
		return shap;
	}
	inline int getPos() const
	{
		return nPos;
	}
	inline void falling() 
	{
		shap.falling(nPos);
	}
	inline void deliteShap() 
	{
		shap.deliteShap();
	}
	inline void offSetStarting()
	{
		shap.offSetStarting();
	}
	inline bool Lowbordercheck(board gameboard)
	{
		return (this->shap.Lowbordercheck(gameboard));
	}
	inline bool IsItAbomb()
	{
		return bomb;
	}
	inline int GetX(int row, int col)
	{
		return (shap.Getx(row,col));
	}
	inline int GetY(int row, int col)
	{
		return (shap.Gety(row, col));
	}
	inline void DeleteCount()
	{
		count = 0;
	}
	
	inline int getCount() const
	{
		return count;
	}


};
#endif 