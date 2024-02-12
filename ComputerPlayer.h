#ifndef _COMPUTERPLAYER_H
#define _COMPUTERPLAYER_H
#include "Player.h"
#include <cmath>


class ComputerPlayer : public Player
{
private:
	enum {
		Right = 0, Left = 1, RightKey = 1, LeftKey = 0, ClockRotationKey = 2, DropKey = 4,
		ShapeWithOnerotations = 1,ShapeWithTworotations = 2, ShapeWithThreerotations = 3,
		NoRotations = 0, MaximumRows = 18,
		MaximumCols = 12
	};
	int level;
	char steps[20];
	int num_step = 0;
	int cur_step = 0;



public:
	char keyOfplayer(char buf[20], int num) override;
	void initShap(int num_p, gameobject allShaps[7], bool colorsSet,board gameboard) override;
	void WherToGo(board player_board);
	void WherToGoCalculation(board player_board,const ComputerPlayer player, int nRotation, int& nKeys, char(&arry_keys)[20]);
	float demoGame(int num_keys, board player_board, ComputerPlayer player,int key);
	void MaxCheck(char(&computer_keys)[20], int& num_keys, int& computer_numkeys, float& temp_score, float& Maxscore, int starting, int& maxNum, int key);
	void CopyKeys(char(&temp_keys)[20], char(&computer_keys)[20], int num_keys);
	int calcColumnHeight(int currentcolumn, board currentBoard);
	//int calculateHeight(const board& currBoard, int* minCol);
	float calculateAverageColumns(const board currBoard);
	float FindNumOfGaps(const board& currBoard);
	float Find_Max_Consecutive_Height_Dif(board currBoard);
	int DeleteLIneCounter(board currBoard);

	inline void Delete_numSteps()
	{
		num_step = 0;
	}
	inline void Delete_curStep()
	{
		cur_step = 0;
	}
	inline void DemoinitXY(int p, int offSet)
	{
		this->shap.DemoinitXY(p, offSet);
	}


};
#endif 