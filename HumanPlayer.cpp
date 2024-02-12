#include "HumanPlayer.h"

/*The function checks whether the character it received belongs to the player
Returns -1 if not */
int HumanPlayer::GetKeyIndex (char key) const 
{
	for (int i = 0; i < numkeys; i++)
	{
		if (key == arrowkeys[i])
			return i;
	}
	return -1;
}


/*A function that checks buffer whether there is a character that belongs
to the player.
the check is done from the end */
char HumanPlayer::keyOfplayer(char buf[20], int num) 
{
	if (num > 0)
	{
		for (int i = num - 1; i >= 0; i--)
		{
			if (this->GetKeyIndex(buf[i]) != -1)
				return buf[i];
		}
	}
	return (' ');
}