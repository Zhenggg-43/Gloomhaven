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
	std::cout << "讀取角色檔案中~~" << std::endl;
	load_character();
	std::cout << "角色讀取結束" << std::endl;

	std::cout << "讀取怪物檔案中~~" << std::endl;
	load_monster();
	std::cout << "怪物讀取結束" << std::endl;
}
void gamemanger::load_character()
{
	
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
		
	}
	else
	{
		std::cout << "openfile_fail" << std::endl;
	}
}
void gamemanger::load_monster()
{
	std::fstream file;
	file.open(monster_txt, std::ios::in);
	if (file.is_open())
	{
		file >> monster_file.monster_amount;
		std::string s_temp;
		monster_card card_temp,zero_card;
		monster_cardskill card_skill,zero_skill;
		std::vector<monster_card> vec_card;
		S_monster mon_temp;

		int inputtime = monster_file.monster_amount;
		for (int i = 0;i < inputtime;i++)
		{
			///////////////////////////////////////////// basic data
			file >> s_temp>>mon_temp.hp>>mon_temp.power>>mon_temp.range;
			monster_file.name.push_back(s_temp);
			monster_file.normal.push_back(mon_temp);
			file >> mon_temp.hp >> mon_temp.power >> mon_temp.range;
			monster_file.elite.push_back(mon_temp);
			///////////////////////////////////////////////card data
			for (int j = 0;j < 6;j++)
			{
				card_temp = zero_card;
				file >> s_temp >> card_temp.card_index >> card_temp.agility;
				while (file >> s_temp)
				{
					card_skill = zero_skill;
					if (s_temp == "move")
					{
						card_skill.type= Action::Move;
						file >> card_skill.movement;
						card_temp.skill.push_back(card_skill);
					}
					else if (s_temp == "attack")
					{
						card_skill.type = Action::Attack;
						file >> card_skill.power;
						card_temp.skill.push_back(card_skill);
					}
					else if (s_temp == "heal")
					{
						card_skill.type = Action::Heal;
						file >> card_skill.power;
						card_temp.skill.push_back(card_skill);
					}
					else if (s_temp == "shield")
					{
						card_skill.type = Action::Shield;
						file >> card_skill.power;
						card_temp.skill.push_back(card_skill);
					}
					else if (s_temp == "range")
					{
						
					}
					else if (s_temp == "r")
					{
						card_temp.suffle_sign = true;
						break;
					}
					else if (s_temp == "d")
					{
						card_temp.suffle_sign = false;
						break;
					}
				}
				vec_card.push_back(card_temp);
			}
			monster_file.deck.push_back(vec_card);
			vec_card.clear();
			//////////////////////////////////////////////////
		}
	}
	else
	{
		std::cout << "openfile_fail" << std::endl;
	}

	for (int i = 0;i < monster_file.monster_amount;i++)
	{
		std::cout << monster_file.name[i] << ' ' << monster_file.normal[i].hp << monster_file.normal[i].power << monster_file.normal[i].range << monster_file.elite[i].hp << monster_file.elite[i].power << monster_file.elite[i].range << std::endl;
		for (int j = 0;j < 6;j++)
		{
			std::cout << monster_file.deck[i][j].card_index << ' ' << monster_file.deck[i][j].agility << ' ' << monster_file.deck[i][j].suffle_sign<<std::endl;
			for (auto k : monster_file.deck[i][j].skill)
			{
				std::cout <<"move: "<< k.type << ' ' << k.power <<' '<< k.range <<' '<< k.movement <<' '<< k.range<<std::endl;
			}
		}
		std::cout << "///////////////////////////////////\n";
	}
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