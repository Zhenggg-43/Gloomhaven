#include"gamamanager.h"
int main(int argc, char *argv[])
{
	srand(time(NULL));
	gamemanger game;
	//////////(cmd)�P(vs)
	//game.temp_function(argv[1],argv[2],argv[3][0]-'0');
	game.temp_function("D:\\�@�~\\�����M��\\Zhenggg-43\\Gloomhaven\\Gloomhaven\\Gloomhaven\\character3.txt", "D:\\�@�~\\�����M��\\Zhenggg-43\\Gloomhaven\\Gloomhaven\\Gloomhaven\\monster3.txt", 1);
	//////////
	game.loadgame();
	while (game.gameloop());
}