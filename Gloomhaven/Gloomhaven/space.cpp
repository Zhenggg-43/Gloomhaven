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
	std::cout << "Ū�������ɮפ�~~" << std::endl;
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
			//std::cout << character_file.name[i] << std::endl << character_file.hp[i] << " " << character_file.hands_amount[i] << std::endl << character_file.deck_amount[i] << std::endl;
			std::vector<character_card> temp_deck;
			character_file.deck.push_back(temp_deck);
			character_file.deck[i].resize(character_file.deck_amount[i]);
			file.ignore();
			for (int j=0;j< character_file.deck_amount[i];j++)
			{
				std::stringstream ss;
				ss.clear();
				temp_s.clear();
				std::getline(file, temp_s);
				ss << temp_s;
				ss >> character_file.deck[i][j].card_index;
				ss >> character_file.deck[i][j].agility;
				//std::cout << character_file.deck[i][j].card_index << " "<<character_file.deck[i][j].agility << " ";
				ss >> temp_s;
				for (int k=0;temp_s!="-";k++,ss>>temp_s)
				{
					ss >> temp_i;
					if (temp_s=="move")
					{
						character_file.deck[i][j].up_effect.card_type.push_back(Action::Move);
						character_file.deck[i][j].up_effect.card_power.push_back(temp_i);
					}
					else if (temp_s == "attack")
					{
						character_file.deck[i][j].up_effect.card_type.push_back(Action::Attack);
						character_file.deck[i][j].up_effect.card_power.push_back(temp_i);
					}
					else if (temp_s == "heal")
					{
						character_file.deck[i][j].up_effect.card_type.push_back(Action::Heal);
						character_file.deck[i][j].up_effect.card_power.push_back(temp_i);
					}
					else if (temp_s == "shield")
					{
						character_file.deck[i][j].up_effect.card_type.push_back(Action::Shield);
						character_file.deck[i][j].up_effect.card_power.push_back(temp_i);
					}
					else if (temp_s == "range")
					{
						character_file.deck[i][j].up_effect.card_type.push_back(Action::Range);
						character_file.deck[i][j].up_effect.card_power.push_back(temp_i);
					}
					//std::cout << character_file.deck[i][j].up_effect.card_type[k] << " " << character_file.deck[i][j].up_effect.card_power[k]<<" ";
				}
				for (int k=0; ss >> temp_s;k++)
				{
					ss >> temp_i;
					if (temp_s == "move")
					{
						character_file.deck[i][j].down_effect.card_type.push_back(Action::Move);
						character_file.deck[i][j].down_effect.card_power.push_back(temp_i);
					}
					else if (temp_s == "attack")
					{
						character_file.deck[i][j].down_effect.card_type.push_back(Action::Attack);
						character_file.deck[i][j].down_effect.card_power.push_back(temp_i);
					}
					else if (temp_s == "heal")
					{
						character_file.deck[i][j].down_effect.card_type.push_back(Action::Heal);
						character_file.deck[i][j].down_effect.card_power.push_back(temp_i);
					}
					else if (temp_s == "shield")
					{
						character_file.deck[i][j].down_effect.card_type.push_back(Action::Shield);
						character_file.deck[i][j].down_effect.card_power.push_back(temp_i);
					}
					else if (temp_s == "range")
					{
						character_file.deck[i][j].down_effect.card_type.push_back(Action::Range);
						character_file.deck[i][j].down_effect.card_power.push_back(temp_i);
					}
					//std::cout<< character_file.deck[i][j].down_effect.card_type[k] << " " << character_file.deck[i][j].down_effect.card_power[k]<<" ";
				}
				//std::cout << std::endl;
			}
		}
		std::cout << "����Ū������" << std::endl;
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