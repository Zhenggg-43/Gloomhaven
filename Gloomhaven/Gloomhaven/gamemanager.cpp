#include"gamamanager.h"
#include"loadgame.h"
#include"whether_play.h"
#include"play_game.h"
#include"menu.h"
bool gameloop()
{
	/////////////////////////
	if (!whether_play())
		return false;
	/////////////////////////
	loadgame();
	/////////////////////////
	menu();
	/////////////////////////
	play_game();
	/////////////////////////
	return true;
}