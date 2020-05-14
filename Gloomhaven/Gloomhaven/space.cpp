#include"gamamanager.h"
bool gamemanger::gameloop()
{

	if (!whether_play())
		return false;

	loadgame();

	menu();

	play_game();

	return true;
}


bool gamemanger::whether_play()
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


void gamemanger::loadgame()
{
	temp_function();
	load_file();
}
void gamemanger::temp_function()
{
	std::cout << "請輸入角色txt檔案" << std::endl;
	std::cin >> character_txt;
	std::cout << "請輸入怪物txt檔案" << std::endl;
	std::cin >> monster_txt;
}
void gamemanger::load_file()
{
	load_character();
	load_monster();
}
void gamemanger::load_character()
{
	std::cout << "讀取角色檔案!!~~" << std::endl;
	std::fstream file;
	file.open(character_txt,std::ios::in);
	if (file.is_open)
	{
		character_file;
	}
	else
	{
		std::cout << "openfile" << std::endl;
	}
}
void gamemanger::load_monster()
{
	std::cout << "讀取怪物檔案" << std::endl;
}


void gamemanger::menu()
{
	character_amount();
	characterANDskill();
	map_set();
}
void gamemanger::character_amount()
{
	std::cout << "你輸入了角色數量你真棒!!" << std::endl;
}
void gamemanger::characterANDskill()
{//實作時丟入角色檔案class回傳角色class
	std::cout << "你輸入了出場角色跟技能卡你真棒!!" << std::endl;
}
void gamemanger::map_set()
{
	std::cout << "你輸入了地圖你真棒!!" << std::endl;
}


void gamemanger::play_game()
{
	std::cout << "玩遊戲中~這太好玩了吧" << std::endl;
	std::cout << "我贏了嗎??隨便啦..." << std::endl;
}