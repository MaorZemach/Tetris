#include "ComputerPlayer.h"

char ComputerPlayer::keyOfplayer(char buf[20], int num)
{
	if (cur_step < num_step)
	{
		cur_step++;
		return steps[cur_step - 1];
	}
	else
		return ' ';

}

void ComputerPlayer::initShap(int num_p, gameobject allShaps[7], bool colorsSet, board gameboard)
{
	this->Player::initShap(num_p, allShaps, colorsSet, gameboard);
	this->WherToGo(gameboard);
	this->Delete_curStep();
}

void ComputerPlayer::WherToGo(board player_board)
{
	if (bomb == false)
	{
		switch (nPos)
		{
		case 0://0
		{
			WherToGoCalculation(player_board, *this, NoRotations, this->num_step, this->steps);
			break;
		}
		case 1://1
		{
			WherToGoCalculation(player_board, *this, ShapeWithOnerotations, this->num_step, this->steps);
			break;
		}
		case 2://1
		{
			WherToGoCalculation(player_board, *this, ShapeWithOnerotations, this->num_step, this->steps);
			break;
		}
		case 3://1
		{
			WherToGoCalculation(player_board, *this, ShapeWithOnerotations, this->num_step, this->steps);
			break;
		}
		case 4://3
		{
			WherToGoCalculation(player_board, *this, ShapeWithThreerotations, this->num_step, this->steps);
			break;
		}
		case 5://3
		{
			WherToGoCalculation(player_board, *this, ShapeWithThreerotations, this->num_step, this->steps);
			break;
		}
		case 6://3
		{
			WherToGoCalculation(player_board, *this, ShapeWithThreerotations, this->num_step, this->steps);
			break;
		}
		}
	}
	else
		WherToGoCalculation(player_board, *this, NoRotations, this->num_step, this->steps);
}

void ComputerPlayer::WherToGoCalculation(board player_board, ComputerPlayer player, int nRotation, int& nKeys, char(&arry_keys)[20])
{
	int num_keys = 1;
	int tempX;
	int beging = 0;
	bool right = false;
	bool left = false;
	float MaxScore = 100;
	float tempScore;

	do
	{
		tempX = player.shap.GetCol(Left);
		while ((left == false) || (right == false))
		{
			if (left == false)
			{
				for (int numKeyToTheLeft = (tempX - 1); numKeyToTheLeft >= 0; numKeyToTheLeft--)
				{
					//this->initKeys(tempKeys,beging,numKeyToTheLeft,num_keys,LeftKey,ClockRotationKey);
					num_keys = numKeyToTheLeft + beging + 1;
					tempScore = demoGame(numKeyToTheLeft, player_board, player, LeftKey);
					//MaxCheck(tempKeys, arry_keys, num_keys, nKeys, tempScore, MaxScore);
					MaxCheck(arry_keys, numKeyToTheLeft, nKeys, tempScore, MaxScore, beging, num_keys, LeftKey);
					//check if the score is better than the old score and chang the parameters
					//accordenly
					num_keys = beging + 1;
				}
				left = true;
				tempX = player.shap.GetCol(Right);
				//Move the shape to the left for as long as possible
			}
			else if (right == false)
			{
				for (int numKeyToTheRight = (12 - tempX); numKeyToTheRight > 0; numKeyToTheRight--)//fix magic num
				{
					//this->initKeys(tempKeys, beging, numKeyToTheRight, num_keys, RightKey,ClockRotationKey);
					num_keys = numKeyToTheRight + beging + 1;
					tempScore = demoGame(numKeyToTheRight, player_board, player, RightKey);
					//MaxCheck(tempKeys, arry_keys, num_keys, nKeys, tempScore, MaxScore);
					MaxCheck(arry_keys, numKeyToTheRight, nKeys, tempScore, MaxScore, beging, num_keys, RightKey);
					//check if the score is better than the old score and chang the parameters
					//accordenly
					num_keys = beging + 1;
				}
				right = true;
			}
		}
		if (nRotation > 0)
		{
			beging++;
			right = false;
			left = false;
			player.WhatToDo(player.arrowkeys[ClockRotationKey], player_board, left);
		}
		nRotation--;
	} while (nRotation >= 0);
}


float ComputerPlayer::demoGame(int num_keys, board player_board, ComputerPlayer player, int key)
{
	//int i = 0;
	bool drop = false;
	int player_num;
	float score_arr[4];
	float score = 0;
	while (drop == false)
	{
		if (player.GetX(2, 2) > 19)
		{
			player_num = 1;
			if (key == RightKey)
				player.DemoinitXY(player_num, num_keys);
			else
				player.DemoinitXY(player_num, (-num_keys));
		}
		else
		{
			player_num = 0;
			if (key == RightKey)
				player.DemoinitXY(player_num, num_keys);
			else
				player.DemoinitXY(player_num, (-num_keys));
		}
		/*while (num_keys > 0)
		{
			player.DemoWhatToDo(player.arrowkeys[key], player_board, drop);
			num_keys--;
		}*/
		drop = player.shap.DemoDrop(player_board,nPos);
		//player.DemoWhatToDo(player.arrowkeys[DropKey], player_board, drop);
		/*player.DemoWhatToDo(keys[i], player_board, drop);
		i++;*/
	}
	//if (i == num_keys)
	//{
	if (player.IsItAbomb() == false)
	{
		player.getShap().BoardUpdate(player_board, (char)player.getColor(), player.getCount());
		//player_board.ptintboard((player_num + 1));
		score_arr[0] = FindNumOfGaps(player_board);
		score_arr[1] = Find_Max_Consecutive_Height_Dif(player_board);
		score_arr[2] = DeleteLIneCounter(player_board);
		score_arr[3] = calculateAverageColumns(player_board);
		score = (score_arr[0] * 8) + (score_arr[1] * 10) + (score_arr[2] * (-50)) + (score_arr[3] * 15);
	}
	else
	{
		player_board.Explosion(player.GetY(2, 2), player.GetX(2, 2));
		player_board.UpdateAfterBomb();
		score_arr[0] = FindNumOfGaps(player_board);
		score_arr[1] = Find_Max_Consecutive_Height_Dif(player_board);
		score_arr[2] = DeleteLIneCounter(player_board);
		score_arr[3] = calculateAverageColumns(player_board);
		score = (score_arr[0] * 8) + (score_arr[1] * 10) + (score_arr[2] * (-50)) + (score_arr[3] * 15);
	}
	return score;
}
//}
//else
	//return 0;



void ComputerPlayer::MaxCheck(char(&computer_keys)[20], int& num_keys, int& computer_numkeys, float& temp_score, float& Maxscore, int starting, int& maxNum, int key)
{
	if (Maxscore > temp_score)
	{
		for (int i = 0; i < num_keys; i++)
		{
			computer_keys[i + starting] = arrowkeys[key];
			if ((starting > 0) && (i < starting))
			{
				computer_keys[i] = arrowkeys[ClockRotationKey];
			}
		}
		computer_keys[maxNum - 1] = arrowkeys[DropKey];
		computer_numkeys = maxNum;
		Maxscore = temp_score;
		/*	CopyKeys(temp_keys, computer_keys, num_keys);
			computer_numkeys = num_keys;
			Maxscore = temp_score;*/
	}
}


void ComputerPlayer::CopyKeys(char(&temp_keys)[20], char(&computer_keys)[20], int num_keys)
{
	for (int i = 0; i < num_keys; i++)
	{
		computer_keys[i] = temp_keys[i];
	}
}

/*--------------------------------------------------------*/
//int ComputerPlayer::calculateHeight(const board& currBoard, int* minCol)//This function checks the heights of the colums and return the minimal height , plus update minCol to the index of the minimal column.
//{                                                                             //This function also calculate the average of all the columns and return it as pointer
//
//	int columnHeight = 0;
//	int Mincolumn = 0;
//	int MinHeight = -1;
//	for (int col = 0; col < MaximumCols; ++col)
//	{
//		columnHeight = calcColumnHeight(col, currBoard);
//
//
//		if (MinHeight == -1)//We checked the first column.
//		{
//			MinHeight = columnHeight;
//			Mincolumn = col;
//		}
//
//		else
//		{
//			if (columnHeight < MinHeight)
//			{
//				MinHeight = columnHeight;
//				Mincolumn = col;
//			}
//		}
//
//	}
//
//	*minCol = Mincolumn;
//
//
//}

float ComputerPlayer::FindNumOfGaps(const board& currBoard)// This fuction find how many gaps there are in the board. 
{
	int countGaps = 0;
	for (int row = 0; row < MaximumRows; ++row)
	{
		for (int col = 0; col <= MaximumCols; ++col)
		{
			if (currBoard.GetChar(row, col) == ' ')
			{
				if ((currBoard.GetChar((row - 1), col) != ' ') && (currBoard.GetChar((row + 1), cols) != ' ') && (currBoard.GetChar(row, (col - 1)) != ' ') && (currBoard.GetChar(row, (col + 1)) != ' '))
					countGaps++;
			}
		}
	}
	return countGaps;
}

int ComputerPlayer::calcColumnHeight(int currentcolumn, board currentBoard)
{
	int Height = 0;

	for (int row = 0; row < MaximumRows; ++row)
	{
		if (currentBoard.GetChar(row, currentcolumn) != ' ')// There is a shape.
		{
			Height++;
		}
		else if ((currentBoard.GetChar(row, currentcolumn) == ' ') && (Height != 0))// There is a gap in the colum so we need to calculate it too.
		{
			Height++;
		}
	}
	return Height;
}

float ComputerPlayer::Find_Max_Consecutive_Height_Dif(board currBoard)// This function calculate the difference between 2 consecutive columns and return the max diffrence in the board.
{
	int MaxConHeightDif = 0, columnHeight = 0, nextColumnH = 0, HeightDif = 0;
	int MaxHeightDif = 0;

	for (int col = 1; col < MaximumCols; ++col)
	{
		columnHeight = calcColumnHeight(col, currBoard);
		nextColumnH = calcColumnHeight(col + 1, currBoard);
		HeightDif = std::abs(columnHeight - nextColumnH);// Heightdif holds the differene between the height of the current columns to the height of the next column in absolute value.
		if (MaxHeightDif < HeightDif)
			MaxHeightDif = HeightDif;
	}

	return MaxHeightDif;
}

int ComputerPlayer::DeleteLIneCounter(board currBoard)//This function checks how many lines will be deleted with the chosen shape.
{
	int  CounterLines = 0;
	int countShapes = 0;// count the amount of shapes in the line 
	for (int row = 0; row < MaximumRows; row++)
	{
		for (int col = 1; col <= MaximumCols; col++)
		{
			if (currBoard.GetChar(row, col) != ' ')
			{
				countShapes++;
			}


		}
		if (countShapes == MaximumCols)// checks if the line is full 
			CounterLines++;
		countShapes = 0;
	}
	return CounterLines;
}

float ComputerPlayer::calculateAverageColumns(const board currBoard)
{
	float Average = 0;
	for (int col = 1; col <= MaximumCols; ++col)
	{
		Average = Average + calcColumnHeight(col, currBoard);

	}
	Average = Average / MaximumCols;
	return Average;
}






