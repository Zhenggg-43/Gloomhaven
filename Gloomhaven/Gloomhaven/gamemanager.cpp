#include"gamamanager.h"
#include"gameload.h"
#include"whether_play.h"
#include"play_game.h"
#include"menu.h"
void menu()
{
	character_amount();
	characterANDskill();
	map_set();
}
void loadgame()
{
	load_file();
}
bool gameloop()
{

	if (!whether_play())
		return false;

	loadgame();

	menu();

	play_game();

	return true;
}