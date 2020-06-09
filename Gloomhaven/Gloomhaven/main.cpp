#include"gamamanager.h"
int main(int argc, char *argv[])
{
	srand(time(NULL));
	gamemanger game;
	//////////(cmd)與(vs)
	//game.temp_function(argv[1],argv[2],argv[3][0]-'0');
	//game.temp_function("D:\\作業\\期末專案\\Zhenggg-43\\Gloomhaven\\Gloomhaven\\Gloomhaven\\character1.txt", "D:\\作業\\期末專案\\Zhenggg-43\\Gloomhaven\\Gloomhaven\\Gloomhaven\\monster1.txt", 1);
	game.temp_function( "C:\\Users\\zzaa3\\OneDrive\\桌面\\Gloomhaven\\Gloomhaven\\Gloomhaven\\Gloomhaven\\character1.txt", "C:\\Users\\zzaa3\\OneDrive\\桌面\\Gloomhaven\\Gloomhaven\\Gloomhaven\\Gloomhaven\\monster1.txt" ,1);

	//////////
	game.loadgame();
	while (game.gameloop());
}