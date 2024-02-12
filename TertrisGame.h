#ifndef _TETRISGAME_H
#define _TETRISGAME_H

#include "Player.h"
#include "board.h"
#include "Gameobject.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

int randomizerPos();
int randomizerdir();
int randomizerColer();


class TETRIS_GAME {
private:
	enum { ESC = 27 ,player1 = 0, player2 = 1, empty_space = ' ',gameSquer = 178};
	Player* players[2];
	board Gameboard[2];
	gameobject allShaps[7];

public:

	void init();
	char RunGame(bool pause, bool colorsSet);
	void Main_Menu(char key);
	void checkWinner(bool p1, bool p2);
	inline void initHumanPlayers(HumanPlayer* pl1, HumanPlayer* pl2)
	{
		players[0] = pl1;
		players[1] = pl2;
	}
	inline void initComputerPlayers(ComputerPlayer* pl1, ComputerPlayer* pl2)
	{
		players[0] = pl1;
		players[1] = pl2;
	}
	inline void initHumanAndComputerPlayers(HumanPlayer* pl1, ComputerPlayer* pl2)
	{
		players[0] = pl1;
		players[1] = pl2;
	}
};


#endif // _TETRISGAME_H