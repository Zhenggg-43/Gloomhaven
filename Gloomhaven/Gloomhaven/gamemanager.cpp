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
			std::cout << "����??��JPlay�٬OExit�n��??" << std::endl;
		}
		temp.clear();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void character_amount()
{
	std::cout << "�A��J�F����ƶq�A�u��!!" << std::endl;
}
void characterANDskill()
{
	std::cout << "�A��J�F�X�������ޯ�d�A�u��!!" << std::endl;
}
void map_set()
{
	std::cout << "�A��J�F�a�ϧA�u��!!" << std::endl;
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
	std::cout << "�L���}Ū(��)" << std::endl;
}
void loadgame()
{
	load_file();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void play_game()
{
	std::cout << "���C����~�o�Ӧn���F�a" << std::endl;
	std::cout << "��Ĺ�F��??�H�K��..." << std::endl;
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