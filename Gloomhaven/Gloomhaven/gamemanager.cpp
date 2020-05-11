#include<string>
#include<iostream>
#include"gamamanager.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
bool whether_play()
{
	std::string temp;
	while (1)
	{
		std::cin >> temp;
		if (temp == "play")
			return true;
		else if (temp == "exit")
			return false;
		else if (temp == "")
			return false;
		else
		{
			std::cout << "智障??輸入Play還是Exit好嗎??" << std::endl;
		}
		temp.clear();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void character_amount()
{
	std::cout << "你輸入了角色數量你真棒!!" << std::endl;
}
void characterANDskill()
{
	std::cout << "你輸入了出場角色跟技能卡你真棒!!" << std::endl;
}
void map_set()
{
	std::cout << "你輸入了地圖你真棒!!" << std::endl;
}
void menu()
{
	character_amount();
	characterANDskill();
	map_set();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void load_file()
{
	std::cout << "無情開讀(檔)" << std::endl;
}
void loadgame()
{
	load_file();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void play_game()
{
	std::cout << "玩遊戲中~這太好玩了吧" << std::endl;
	std::cout << "我贏了嗎??隨便啦..." << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool gameloop()
{

	if (!whether_play())
		return false;

	loadgame();

	menu();

	play_game();

	return true;
}