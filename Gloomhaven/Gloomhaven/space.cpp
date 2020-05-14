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
	std::cout << "輸入play or exit" << std::endl;
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
	std::cout << "讀取角色檔案中~~" << std::endl;
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
		std::cout << "角色讀取結束" << std::endl;
	}
	else
	{
		std::cout << "openfile_fail" << std::endl;
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