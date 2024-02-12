#include <iostream>
#include <conio.h>
#include <windows.h>
#include  <random>

#include "TertrisGame.h"
#include"board.h"
#include"point.h"
//#include"Player.h"
#include "Menu.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

using std::cout;
using std::cin;
using std::endl;
void creatObject(gameobject g[]);
char bufferKeys(char buf[20], int& sizeBuf);
void clearKeyboardBuffer();
void deliteBuf(char buf[20], int& num);


/*A function that initializes the game */
void TETRIS_GAME::init()
{
	players[0]->initScore();
	players[1]->initScore();
	players[0]->setArrowKeys("adswxADSWX");
	players[1]->setArrowKeys("jlkimJLKIM");
	Gameboard[0].initboared();
	Gameboard[1].initboared();
	creatObject(allShaps);

}

void creatObject(gameobject g[])//A function that sends according to the index in the array to produce the correct shape. 
{
	for (int i = 0; i < 7; i++)
	{
		/*switch (i)
		{
		case 0:
			g[i].creatI();
			break;
		case 1:
			g[i].creatJ();
			break;
		case 2:
			g[i].creatL();
			break;
		case 3:
			g[i].creatO();
			break;
		case 4:
			g[i].creatS();
			break;
		case 5:
			g[i].creatT();
			break;
		case 6:
			g[i].creatZ();
			break;
		}*/


		switch (i)
		{
		case 0:
			g[i].creatO();
			break;
		case 1:
			g[i].creatI();
			break;
		case 2:
			g[i].creatS();
			break;
		case 3:
			g[i].creatZ();
			break;
		case 4:
			g[i].creatJ();
			break;
		case 5:
			g[i].creatL();
			break;
		case 6:
			g[i].creatT();
			break;
		}
	}
}

/*The main game function,
the function gets a boolean value that shows whether we returned to the function,
after pausing a game or a new game. */
char TETRIS_GAME::RunGame(bool pause, bool colorsSet)
{
	char buf[20];
	int sizeBuf = 1;
	bool p1lost = false, p2lost = false;
	int score = 0;
	bool dropP1 = false, dropP2 = false;//Flag to check if a drop has been made 
	Gameboard[0].ptintboard(1);
	Gameboard[1].ptintboard(2);

	if (pause == false)
	{
		players[0]->initShap(0, allShaps, colorsSet, Gameboard[0]);
		players[1]->initShap(1, allShaps, colorsSet, Gameboard[1]);
		/*Check if the first shaps fall from the same height */
		int temprow1 = players[0]->getShap().isOffSetNeeded(), temprow2 = players[1]->getShap().isOffSetNeeded();
		if (temprow1 > temprow2)
			players[1]->offSetStarting();
		else if (temprow1 < temprow2)
			players[0]->offSetStarting();
	}
	char c = ' ';
	while (!_kbhit() || ((c = _getch()) != ESC))//The loop continues to run until the player press esc 
	{
		buf[0] = c;
		clearKeyboardBuffer();
		if (bufferKeys(buf, sizeBuf) == ESC)
			return (ESC);

		if ((c = players[0]->keyOfplayer(buf, sizeBuf)) != ' ')//Check if we got a character from the first player 
		{
			setTextColor(players[0]->getColor());
			players[0]->WhatToDo(c, Gameboard[0], dropP1);
			c = ' ';
		}

		if ((c = players[1]->keyOfplayer(buf, sizeBuf)) != ' ')////Check if we got a character from the second player
		{
			setTextColor(players[1]->getColor());
			players[1]->WhatToDo(c, Gameboard[1], dropP2);
			c = ' ';
		}



		_flushall();
		/*Check if the shape should stop in the next movement down
		We will check if a drop has been made to avoid unnecessary entry into the function Lowbordercheck */
		if ((dropP1 == false) && (players[0]->Lowbordercheck(Gameboard[0])))
		{
			setTextColor(players[0]->getColor());
			players[0]->falling();

		}
		else//If the shape stops we want to create the following shape and update the board.
		{
			//int nPos1 = rand() % 7;
			//int dir1 = rand() % 4;
			//players[0].nPos = randomizerPos();
			//int dir1 = randomizerdir();
			if (players[0]->IsItAbomb())
			{
				//Gameboard[0].Explosion(players[0]->GetY(2, 2), players[0]->GetX(2, 2),1);
				Gameboard[0].Explosion(players[0]->GetY(2, 2), players[0]->GetX(2, 2));
				Sleep(20);
				Gameboard[0].ptintboard(1);
				Gameboard[0].UpdateAfterBomb();
				Gameboard[0].ptintboard(1);
			}
			else
			{
				players[0]->getShap().BoardUpdate(Gameboard[0], (char)players[0]->getColor(),players[0]->getCount());
				//Gameboard[0].BoardUpdate_line(score, gameSquer);
			}//Update the board 
			if (Gameboard[0].BoardUpdate_line(score,empty_space))//Check whether a row should be deleted, and if a row is deleted we will reprint the board. 
			{
				setTextColor(Color::WHITE);
				Gameboard[0].ptintboard(1);
				players[0]->updateScore(score);
				score = 0;
			}
			p1lost = Gameboard[0].IsGameOver();
			Sleep(70);
			players[0]->deliteShap();//Reset the shape 
			//players[0].shap.initStarting(allShaps[players[0].nPos], dir1);//Create a shape from the shapes array 
			players[0]->initShap(0, allShaps, colorsSet,Gameboard[0]);
			//players[0].shap.initXY(player1);//Reset coordinates of the shape 
			dropP1 = false;
		}
		/*Same process as for the first player also for the second player  */
		if ((dropP2 == false) && (players[1]->Lowbordercheck(Gameboard[1])))
		{
			setTextColor(players[1]->getColor());
			players[1]->falling();

		}
		else
		{
			/*int nPos2 = rand() % 7;
			int dir2 = rand() % 4;*/
			/*players[1].nPos = randomizerPos();
			int dir2 = randomizerdir();*/
			if (players[1]->IsItAbomb())
			{
				//Gameboard[1].Explosion(players[1]->GetY(2, 2), players[1]->GetX(2, 2),2);
				Gameboard[1].Explosion(players[1]->GetY(2, 2), players[1]->GetX(2, 2));
				Sleep(20);
				Gameboard[1].ptintboard(2);
				Gameboard[1].UpdateAfterBomb();
				Gameboard[1].ptintboard(2);
			}
			else
			{
				players[1]->getShap().BoardUpdate(Gameboard[1], (char)players[1]->getColor(),players[1]->getCount());
				//Gameboard[1].BoardUpdate_line(score, gameSquer);
			}
			if (Gameboard[1].BoardUpdate_line(score,empty_space))
			{
				setTextColor(Color::WHITE);
				Gameboard[1].ptintboard(2);
				players[1]->updateScore(score);
				score = 0;
			}
			p2lost = Gameboard[1].IsGameOver();
			Sleep(70);
			players[1]->deliteShap();
			players[1]->initShap(1, allShaps, colorsSet, Gameboard[1]);
			//players[1].shap.initStarting(allShaps[players[1].nPos], dir2);
			//players[1].shap.initXY(player2);
			dropP2 = false;
		}
		if (p1lost != false || p2lost != false)//Check if we reached the end of the game and if so who won 
		{
			this->checkWinner(p1lost, p2lost);
			return (' ');
		}
		deliteBuf(buf, sizeBuf);
		Sleep(700);
	}
	return (ESC);

}


/*Menu function, we will loop the menu until the player wants to exit the game.
The function gets a character indicating what type of menu should be displayed.
If we want to start a new game, we will reset the data we have in the game
and go to the main game loop with the false boolean value.
If we want to continue the stopped game we will return to the main game loop with the true value,
so that the loop will know that we have returned from a paused game and will not overwrite the data
we have. Each time we return from the game loop by returning to the menu function (return) and not by re-calling
the function, to avoid recursion.*/
void TETRIS_GAME::Main_Menu(char key)
{// key is to know if the player press ESC or not so we will know to show him the correct menu
	Menu menu;
	ComputerPlayer p1, p2;
	HumanPlayer p1_, p2_;
	menu.Main_Menu(key, *this,p1,p2,p1_,p2_);
	
	return;
}

char bufferKeys(char buf[20], int& sizeBuf)//Key input to the buffer
{
	int i = 1;
	while (_kbhit() && i < 20)
	{
		buf[i] = _getch();
		if (buf[i] == 27)
		{
			sizeBuf = i;
			return buf[i];
		}
		i++;
		Sleep(100);
	}
	sizeBuf = i;
	return *buf;

}

void clearKeyboardBuffer()
{
	char junk;
	while (_kbhit())
	{
		junk = _getch();
	}
}

void deliteBuf(char buf[20], int& num)//Reset buffer
{
	int i = num;
	while (i > 1)
	{
		buf[i] = ' ';
		i--;
	}
	num = i;
}

/*A function that checks who won the game */
void TETRIS_GAME::checkWinner(bool p1, bool p2)
{
	setTextColor(Color::WHITE);
	char c;
	int num = ((Player*)players)->checkScore(*players[0], *players[1]);
	system("cls");
	_flushall();
	gotoxy(0, 0);
	if (p1 == true && p2 == true)//If both players lost we will check by the score who won 
	{
		if (num == 2)
		{
			cout << "it's a tie!!!" << endl;
			cout << "Score of player 1: " << this->players[0]->gerScore() << endl;
			cout << "Score of player 2: " << this->players[1]->gerScore() << endl;
			cout << "Press any key to continue ";
			cin >> c;
		}
		else if (num == 0)
		{
			cout << "player 1 is the winner" << endl;
			cout << "Score of player 1: " << this->players[0]->gerScore() << endl;
			cout << "Score of player 2: " << this->players[1]->gerScore() << endl;
			cout << "Press any key to continue ";
			cin >> c;
		}
		else
		{
			cout << "player 2 is the winner" << endl;
			cout << "Score of player 1: " << this->players[0]->gerScore() << endl;
			cout << "Score of player 2: " << this->players[1]->gerScore() << endl;
			cout << "Press any key to continue ";
			cin >> c;
		}
		return;
	}
	else if (p1 == true)//If the first player lost 
	{
		cout << "player 2 is the winner" << endl;
		cout << "Score of player 1: " << this->players[0]->gerScore() << endl;
		cout << "Score of player 2: " << this->players[1]->gerScore() << endl;
		cout << "Press any key to continue ";
		cin >> c;
		return;
	}
	else//If the second player lost 
	{
		cout << "player 1 is the winner" << endl;
		cout << "Score of player 1: " << this->players[0]->gerScore() << endl;
		cout << "Score of player 2: " << this->players[1]->gerScore() << endl;
		cout << "Press any key to continue ";
		cin >> c;
		return;
	}
}
