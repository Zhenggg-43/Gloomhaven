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
	std::cout << "��Jplay or exit" << std::endl;
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
	if (file.is_open())
	{
		int temp_i = 0;
		std::string temp_s = "";
		file >> character_file.character_amount;
		for (int i = 0; i < character_file.character_amount; i++)
		{
			file >> temp_s;
			character_file.name.push_back(temp_s);
			file >> temp_i;
			character_file.hp.push_back(temp_i);
			file >> temp_i;
			character_file.hands_amount.push_back(temp_i);
			file >> temp_i;
			character_file.deck_amount.push_back(temp_i);
			/*std::cout << character_file.name[0] << std::endl << character_file.hp[0] << " " << character_file.hands_amount[0] << std::endl << character_file.deck_amount[0] << std::endl;*/
			character_deck temp_deck;
			character_file.deck.push_back(temp_deck);
			for (int j=0;j< character_file.deck_amount[i];j++)
			{
				std::stringstream ss;
				std::getline(file, temp_s);
				ss << temp_s;
				ss >> character_file.deck[i].card_id;
				ss >> character_file.deck[i].move_value;
				ss >> temp_s;
				bool upordown = true;
				while (temp_s!="")
				{
					ss >> temp_i;
					if (temp_s=="move")
					{
						character_file.deck[i].up_effect.card_type.push_back(Action::Move);
					}
					else if (temp_s == "attack")
					{
						character_file.deck[i].up_effect.card_type.push_back(Action::Attack);
					}
					else if (temp_s == "heal")
					{
						character_file.deck[i].up_effect.card_type.push_back(Action::Heal);
					}
					else if (temp_s == "shield")
					{
						character_file.deck[i].up_effect.card_type.push_back(Action::Shield);
					}
				}
			}
		}
	}
	else
	{
		std::cout << "openfile_fail" << std::endl;
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