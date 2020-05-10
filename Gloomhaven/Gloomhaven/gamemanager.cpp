#include"gamamanager.h"
#include"loadgame.h"
#include"whether_play.h"
#include"play_game.h"
bool gameloop()
{
	if (!whether_play())
		return false;

	loadgame();

	play_game();

	return true;
}