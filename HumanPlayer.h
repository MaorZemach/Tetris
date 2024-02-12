#ifndef _HUMANPLAYER_H
#define _HUMANPLAYER_H
#include "Player.h"

class HumanPlayer : public Player
{
public:
	/*We put the shap of the player in public
	so that we would have much simpler access to the shap of the player from different places. */
	int GetKeyIndex(char key) const;
	char keyOfplayer(char buf[20], int num) override;

};
#endif 