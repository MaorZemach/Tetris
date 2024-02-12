#include "Menu.h"
#include "TertrisGame.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"


void Menu::Main_Menu(char key, TETRIS_GAME& game, ComputerPlayer& computer1, ComputerPlayer& computer2, HumanPlayer& human1, HumanPlayer& human2)
{
	setTextColor(Color::WHITE);
	bool exit = false;
	bool colorsSet = false;
	char temp;
	int casNum;
	gotoxy(0,0);
	while (exit != true)
	{
		setTextColor(Color::WHITE);
		casNum =this->Print_Menu(key);
		//if (key == ESC)
		//{
		//	system("cls");
		//	cout << "The game is paused" << endl;
		//	cout << "menu:" << endl << "Please choose one of the following options:" << endl;
		//	cout << "(1) Start a new game - Human vs Human" << endl;
		//	cout << "(2) Start a new game - Human vs Computer" << endl;
		//	cout << "(3) Start a new game - Computer vs Computer" << endl;
		//	cout << "(4) Continue a paused game" << endl;
		//	cout << "(8) Present instructions and keys" << endl;
		//	cout << "(9) EXIT" << endl;
		//	cout << "Answer: ";
		//}
		//else//key!=27(ESC)
		//{
		//	cout << "Welcome to the Tetris game " << endl;
		//	cout << "menu:" << endl << "Please choose one of the following options:" << endl;
		//	cout << "(1) Start a new game - Human vs Human" << endl;
		//	cout << "(2) Start a new game - Human vs Computer" << endl;
		//	cout << "(3) Start a new game - Computer vs Computer" << endl;
		//	cout << "(8) Present instructions and keys" << endl;
		//	cout << "(9) EXIT" << endl;
		//	cout << "Answer: ";
		//}

		//cin >> casNum;
		//cout << "\n";

		switch (casNum)
		{
		case 1://new game Human vs Human
		{
			cout << "Do you want your game with colors?: Y/N: ";
			cin >> temp;
			if (temp == 'y' || temp == 'Y')
				colorsSet = true;
			else
				colorsSet = false;
			system("cls");
			_flushall();
			
			game.initHumanPlayers(&human1, &human2);
			game.init();
			human1.deliteShap();
			human2.deliteShap();
			human1.DeleteCount();
			human2.DeleteCount();
			key = game.RunGame(false, colorsSet);

			break;
		}
		case 2://new game Human vs Computer
		{
			cout << "Do you want your game with colors?: Y/N: ";
			cin >> temp;
			if (temp == 'y' || temp == 'Y')
				colorsSet = true;
			else
				colorsSet = false;
			system("cls");
			_flushall();
			game.initHumanAndComputerPlayers(&human1, &computer2);
			game.init();
			human1.deliteShap();
			computer2.deliteShap();
			human1.DeleteCount();
			computer2.DeleteCount();
			computer2.Delete_curStep();
			computer2.Delete_numSteps();
			key = game.RunGame(false, colorsSet);

			break;
		}
		case 3://new game Computer vs Computer
		{
			cout << "Do you want your game with colors?: Y/N: ";
			cin >> temp;
			if (temp == 'y' || temp == 'Y')
				colorsSet = true;
			else
				colorsSet = false;
			system("cls");
			_flushall();
			game.initComputerPlayers(&computer1, &computer2);
			game.init();
			computer1.deliteShap();
			computer2.deliteShap();
			computer1.DeleteCount();
			computer2.DeleteCount();
			computer1.Delete_curStep();
			computer1.Delete_numSteps();
			computer2.Delete_curStep();
			computer2.Delete_numSteps();
			key = game.RunGame(false, colorsSet);

			break;
		}
		case 4://Continue game
		{
			system("cls");
			_flushall();
			key = game.RunGame(true, colorsSet);

			break;
		}
		case 8://Displays keys of all players
		{
			system("cls");
			cout << "LEFT: Player1 - press a or A  , Player2 - press j or J " << endl;
			cout << "RIGHT:Player1 - press d or D  , Player2 - press l (small L) or L" << endl;
			cout << "ROTATE clockwise: Player1 - press s or S , Player2 - press k or K " << endl;
			cout << "ROTATE counterclockwise: Player1 - press w or W" << endl;
			cout << "Player2 - press i or I(uppercase i)" << endl;
			cout << "DROP: Player1 -  press x or X , Player2 - press m or M " << endl;
			cout << "Press any key to continue ";
			cin >> temp;
			system("cls");
			break;
		}
		case 9:
		{
			system("cls");
			_flushall();
			return;
			exit = true;
			break;
		}
		}
		system("cls");
	}
	return;
}

int Menu::Print_Menu(char key)
{
	int casNum;
	setTextColor(Color::WHITE);

	if (key == ESC)
	{
		system("cls");
		cout << "The game is paused" << endl;
		cout << "menu:" << endl << "Please choose one of the following options:" << endl;
		cout << "(1) Start a new game - Human vs Human" << endl;
		cout << "(2) Start a new game - Human vs Computer" << endl;
		cout << "(3) Start a new game - Computer vs Computer" << endl;
		cout << "(4) Continue a paused game" << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl;
		cout << "Answer: ";
	}
	else//key!=27(ESC)
	{
		cout << "Welcome to the Tetris game " << endl;
		cout << "menu:" << endl << "Please choose one of the following options:" << endl;
		cout << "(1) Start a new game - Human vs Human" << endl;
		cout << "(2) Start a new game - Human vs Computer" << endl;
		cout << "(3) Start a new game - Computer vs Computer" << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl;
		cout << "Answer: ";
	}

	cin >> casNum;
	cout << "\n";

	return casNum;
}