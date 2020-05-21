#include"gamamanager.h"
int main()
{
	gamemanger game;
	game.loadgame();
	while (game.gameloop());
}