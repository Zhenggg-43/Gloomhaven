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
			std::cout << "����??��JPlay�٬OExit�n��??" << std::endl;
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
	std::cout << "�п�J����txt�ɮ�" << std::endl;
	std::cin >> character_txt;
	std::cout << "�п�J�Ǫ�txt�ɮ�" << std::endl;
	std::cin >> monster_txt;
}
void gamemanger::load_file()
{
	load_character();
	load_monster();
}
void gamemanger::load_character()
{
	std::cout << "Ū�������ɮ�!!~~" << std::endl;
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
	std::cout << "Ū���Ǫ��ɮ�" << std::endl;
}


void gamemanger::menu()
{
	character_amount();
	characterANDskill();
	map_set();
}
void gamemanger::character_amount()
{
	std::cout << "�A��J�F����ƶq�A�u��!!" << std::endl;
}
void gamemanger::characterANDskill()
{//��@�ɥ�J�����ɮ�class�^�Ǩ���class
	std::cout << "�A��J�F�X�������ޯ�d�A�u��!!" << std::endl;
}
void gamemanger::map_set()
{
	std::cout << "�A��J�F�a�ϧA�u��!!" << std::endl;
}


void gamemanger::play_game()
{
	std::cout << "���C����~�o�Ӧn���F�a" << std::endl;
	std::cout << "��Ĺ�F��??�H�K��..." << std::endl;
}