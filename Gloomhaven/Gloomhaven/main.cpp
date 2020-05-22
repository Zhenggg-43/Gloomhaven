#include"gamamanager.h"
int main()
{
	srand(time(NULL));
	gamemanger game;
	game.loadgame();
	while (game.gameloop());
}