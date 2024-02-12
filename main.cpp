#include "TertrisGame.h"
#include "Menu.h"




void set_cursor(bool visible);

int main()
{
	set_cursor(false);//hides cursor
	TETRIS_GAME game;
	game.Main_Menu(' ');
	gotoxy(0, 0);
	cout << "Thank you for playing!!!";
	gotoxy(20, 20);
}

void set_cursor(bool visible) {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}





