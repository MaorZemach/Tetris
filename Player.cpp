#include <iostream>
#include "Player.h"
#include <random>


//
///*The function checks whether the character it received belongs to the player
//Returns -1 if not */
//int Player::GetKeyIndex(char key)
//{
//	for (int i = 0; i < numkeys; i++)
//	{
//		if (key == arrowkeys[i])
//			return i;
//	}
//	return -1;
//}

void Player::setArrowKeys(const char* keys)
{
	arrowkeys[0] = keys[0];
	arrowkeys[1] = keys[1];
	arrowkeys[2] = keys[2];
	arrowkeys[3] = keys[3];
	arrowkeys[4] = keys[4];
	arrowkeys[5] = keys[5];
	arrowkeys[6] = keys[6];
	arrowkeys[7] = keys[7];
	arrowkeys[8] = keys[8];
	arrowkeys[9] = keys[9];

}

/*A function that Initializing the shape of the player*/
void Player::initShap(int num_p,gameobject allShaps[7], bool colorsSet, board gameboard)
{
	int isItAbomb = randomizerBomb();
	this->nPos = randomizerPos();
	int dir = randomizerdir();
	count++;
	if (isItAbomb != 0)
	{
		if (colorsSet == true)
		{
			int numColor = randomizerColer();
			color = Allcolors[numColor];
		}
		else
			color = WHITE;
		shap.initStarting(allShaps[this->nPos], dir);
		bomb = false;
	}
	else
	{
		color = WHITE;
		shap.TheBomb();
		nPos = 3;
		bomb = true;

	}
	shap.initXY(num_p);
	
}

/*A function that checks buffer whether there is a character that belongs
to the player.
the check is done from the end */
//char Player:: keyOfplayer(char buf[20],int num)
//{
//	if (num > 0)
//	{
//		for (int i = num - 1; i >= 0; i--)
//		{
//			if (this->GetKeyIndex(buf[i]) != -1)
//				return buf[i];
//		}
//	}
//	return (' ');
//}

/*The function gets the player's board and the character of the action
that the player wants to do.
And depending on the character it will choose the appropriate action. */
void Player::WhatToDo(char key,board gameboard,bool& drop)
{
	if (key == 'a' || key == 'A' || key == 'j' || key == 'J')//move to the left
	{
		this->shap.move(key, gameboard);
	}
	else if (key == 'd' || key == 'D' || key == 'l' || key == 'L')//move to the right
	{
		this->shap.move(key, gameboard);
	}
	else if (key == 'S' || key == 's' || key == 'K' || key == 'k')//ROTATE clockwise
	{
		//If the shape is a square we will not allow rotation
		if(nPos != 0)
			this->shap.rotation(0, gameboard);
	}
	else if (key == 'w' || key == 'W' || key == 'i' || key == 'I')//ROTATE counterclockwise
	{
		//If the shape is a square we will not allow rotation
		if(nPos != 0)
			this->shap.rotation(1, gameboard);
	}
	else if (key == 'x' || key == 'X' || key == 'm' || key == 'M')//drop
	{
		drop = this->shap.Drop(gameboard, nPos);
	}
}

/*A function that checks which player has a higher score */
int Player::checkScore(Player& p1, Player& p2)
{
	if (p1.Score > p2.Score)
		return player1;
	if (p1.Score < p2.Score)
		return player2;
	else
		return tie;
}

int randomizerPos()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0.0, 7.0);

	return (int)dist(mt);
}

int randomizerdir()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0.0, 4.0);

	return (int)dist(mt);
}

int randomizerColer()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0.0, 14.0);

	return (int)dist(mt);
}

int randomizerBomb()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0.0, 10.0);

	return (int)dist(mt);
}
