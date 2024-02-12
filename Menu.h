#ifndef _MENU_H
#define _MENU_H

#include <conio.h>
#include <iostream>
#include "TertrisGame.h"
using std::cout;
using std::cin;
using std::endl;

class Menu
{
private:
	enum { ESC = 27 };
public:
	void Main_Menu(char key, TETRIS_GAME& game, ComputerPlayer& computer1, ComputerPlayer& computer2,HumanPlayer& human1, HumanPlayer& human2);
	int Print_Menu(char key);
};


#endif // _MENU_H
