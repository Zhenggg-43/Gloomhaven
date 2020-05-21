#include"gamamanager.h"
bool gamemanger::gameloop()
{

	if (!whether_play())
		return false;


	menu();

	play_game();

	return true;
}


bool gamemanger::whether_play()
{
	std::string temp;
	std::cout << "輸入play 或是 exit" << std::endl;
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
	set_debugmode();
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
						file >> card_skill.attack.attpower;
						card_temp.skill.push_back(card_skill);
					}
					else if (s_temp == "heal")
					{
						card_skill.type = Action::Heal;
						file >> card_skill.skillpower;
						card_temp.skill.push_back(card_skill);
					}
					else if (s_temp == "shield")
					{
						card_skill.type = Action::Shield;
						file >> card_skill.skillpower;
						card_temp.skill.push_back(card_skill);
					}
					else if (s_temp == "range")
					{
						card_temp.skill.back().attack.ifrange = 1;
						file >> card_temp.skill.back().attack.range;
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
			monster_file.All_deck.push_back(vec_card);
			vec_card.clear();
			//////////////////////////////////////////////////
		}
	}
	else
	{
		std::cout << "openfile_fail" << std::endl;
	}

	//for (int i = 0;i < monster_file.monster_amount;i++)
	//{
	//	std::cout << monster_file.name[i] << ' ' << monster_file.normal[i].hp << monster_file.normal[i].power << monster_file.normal[i].range << monster_file.elite[i].hp << monster_file.elite[i].power << monster_file.elite[i].range << std::endl;
	//	for (int j = 0;j < 6;j++)
	//	{
	//		std::cout << monster_file.All_deck[i][j].card_index << ' ' << monster_file.All_deck[i][j].agility << ' ' << monster_file.All_deck[i][j].suffle_sign<<std::endl;
	//		for (auto k : monster_file.All_deck[i][j].skill)
	//		{
	//			std::cout <<"move: "<< k.type << ' ' << k.power <<' '<< k.range <<' '<< k.movement <<' '<< k.range<<std::endl;
	//		}
	//	}
	//	std::cout << "///////////////////////////////////\n";
	//}
}
void gamemanger::set_debugmode() 
{
	std::cout << "是否要要啟用Debug Mode (0/1)\n";
	std::string input;
	while (std::cin >> input)
	{
		if (input=="1")
		{
			Flag_DebugMode = 1;
			break;
		}
		else if (input == "0")
		{
			Flag_DebugMode = 0;
			break;
		}
		else
		{
			std::cout << "輸入錯誤!!!\n";
		}
	}
}
void gamemanger::load_map()
{
	std::cout << "請選擇地圖\n";
	std::string map_txt;
	std::cin >> map_txt;
	std::fstream file;
	file.open(map_txt, std::ios::in);
	if (file.is_open())
	{
		int xb_temp, yb_temp;
		//設定XY邊界
		file>> yb_temp >> xb_temp;
		PlayingData_map.Y_border = yb_temp;
		PlayingData_map.X_border = xb_temp;
		//設定地圖
		PlayingData_map.body = new std::string[yb_temp];
		for (int i = 0;i < yb_temp;i++)
		{
			file >> PlayingData_map.body[i];
		}
		//初始化視野
		PlayingData_map.sight = new bool*[yb_temp];
		for (int i = 0;i < yb_temp;i++)
		{
			PlayingData_map.sight[i] = new bool[xb_temp];
		}
		for (int i = 0;i < yb_temp;i++)
		{
			for (int j = 0;j < xb_temp;j++)
			{
				PlayingData_map.sight[i][j] = 0;
			}
		}
		//設定可選起始位置
		for (int i = 0;i < 4;i++)
		{
			file >> PlayingData_map.position_start[i][1] >> PlayingData_map.position_start[i][0];
		}
		//設定怪物資料
		int monster_amount_temp;
		char icon_temp = 'a';
		file >> monster_amount_temp;
		for (int i = 0;i < monster_amount_temp;i++)
		{
			std::string name_temp="";
			monster temp_monster;
			S_coordinate temp_coor;
			int xtemp = 0, ytemp = 0,montype;

			file >> name_temp >> xtemp >> ytemp;
			temp_coor.x = xtemp, temp_coor.y = ytemp;
			//type
			for (int x = 0;x < 3;x++)
			{
				int null;
				if (x == playingData_hero.hero_amount - 2)
				{
					file >> montype;
				}
				else
				{
					file >> null;
				}
			}

			if (montype == 1)///////normal
			{
				PlayingData_monster.monster_amount++;

				temp_monster.icon = icon_temp;//icon
				for (int pos=0;pos<monster_file.monster_amount;pos++)
				{
					if (monster_file.name[pos] == name_temp)
					{
						temp_monster.ifactive = 0;
						temp_monster.name = monster_file.name[pos];//name
						temp_monster.hp_max = monster_file.normal[pos].hp;//basic data
						temp_monster.hp = temp_monster.hp_max;
						temp_monster.power = monster_file.normal[pos].power;
						temp_monster.range = monster_file.normal[pos].range;
						temp_monster.cards = monster_file.All_deck[pos];//deck
						break;
					}
				}
				PlayingData_monster.monster_status.push_back(temp_monster);//怪物資料
				PlayingData_map.monster_coordinate.push_back(temp_coor);//怪物座標
			}
			else if (montype == 2)///////elite
			{
				PlayingData_monster.monster_amount++;

				temp_monster.icon = icon_temp;//icon
				for (int pos = 0;pos < monster_file.monster_amount;pos++)
				{
					if (monster_file.name[pos] == name_temp)
					{
						temp_monster.ifactive = 0;
						temp_monster.name = monster_file.name[pos];//name
						temp_monster.hp_max = monster_file.elite[pos].hp;//basic data
						temp_monster.hp = temp_monster.hp_max;
						temp_monster.power = monster_file.elite[pos].power;
						temp_monster.range = monster_file.elite[pos].range;
						temp_monster.cards = monster_file.All_deck[pos];//deck
						break;
					}
				}
				PlayingData_monster.monster_status.push_back(temp_monster);//怪物資料
				PlayingData_map.monster_coordinate.push_back(temp_coor);//怪物座標
			}

			icon_temp++;
		}
	}
	else
	{
		std::cout << "openfile_fail" << std::endl;
	}
	PlayingData_monster.monster_amount = PlayingData_monster.monster_status.size();

	//std::cout <<std::endl<< PlayingData_monster.monster_amount<<std::endl;
	PlayingData_monster.printAllmonster();
	std::cout << "你輸入了地圖你真棒!!" << std::endl;
}

void gamemanger::menu()
{
	character_amount();
	characterANDskill();
	load_map();
}
void gamemanger::character_amount()
{
	std::cout << "請輸入出場角色數量:" << std::endl;
	while (std::cin >> playingData_hero.hero_amount)
	{
		if (playingData_hero.hero_amount >= 2 && playingData_hero.hero_amount <= 4)
		{
			break;
		}
		else
		{
			std::cout << "輸入錯誤請輸入2~4" << std::endl;
		}
	}
	playingData_hero.hero_status.clear();
	playingData_hero.hero_status.resize(playingData_hero.hero_amount);
	for (int i=0;i< playingData_hero.hero_amount;i++)
	{
		playingData_hero.hero_status[i].icon = 'A' + i;
	}
}
void gamemanger::characterANDskill()
{
	std::cout << "輸入角色名稱與卡片:" << std::endl;
	std::stringstream ss;
	std::string temp_s="";
	int temp_i=0;
	std::vector<int> temp_i_vector;
	ss.clear();
	temp_i_vector.clear();
	std::cin.ignore();
	for (int i=0;i< playingData_hero.hero_amount;i++)
	{
		while (std::getline(std::cin, temp_s))
		{
			ss << temp_s;
			ss >> temp_s;
			while (ss>>temp_i)
			{
				temp_i_vector.push_back(temp_i);
			}
			bool have_char=false;
			bool deck_amount_crrect = false;
			bool deck_id_crrect = true;
			for (int j=0;j< character_file.character_amount;j++)
			{
				if (temp_s== character_file.name[j])
				{
					have_char = true;
					if (character_file.hands_amount[j] == temp_i_vector.size())
					{
						deck_amount_crrect = true;
						for (int k=0;k< temp_i_vector.size();k++)
						{
							if (temp_i_vector[k]<0|| temp_i_vector[k]>=character_file.deck_amount[j])
							{
								deck_id_crrect = false;
								break;
							}
						}
						if (deck_id_crrect)
						{
							playingData_hero.hero_status[i].hp = character_file.hp[j];
							playingData_hero.hero_status[i].name = temp_s;
							playingData_hero.hero_status[i].hand = temp_i_vector;
						}
						else 
						{
							std::cout << "你輸入了此角色沒有的卡牌，請重新輸入!" << std::endl;
						}
					}
					temp_i_vector.clear();
					if (!deck_amount_crrect)
					{
						std::cout << "手牌數量不符合請重新輸入!" << std::endl;
					}
					break;
				}
			}
			temp_i_vector.clear();
			ss.clear();
			if (!have_char)
			{
				std::cout << "角色名稱不再資料庫中~~請重新輸入!" << std::endl;
			}
			else if (deck_amount_crrect&& deck_id_crrect)
			{
				break;
			}
		}
	}
	//////////test_input
	for (int i=0;i< playingData_hero.hero_amount;i++)
	{
		std::cout << playingData_hero.hero_status[i].name << "  "<< playingData_hero.hero_status[i].icon<<" "<< playingData_hero.hero_status[i].hp<<" ";
		for (int j=0;j< playingData_hero.hero_status[i].hand.size();j++)
		{
			std::cout << playingData_hero.hero_status[i].hand[j] << " ";
		}
		std::cout << std::endl;
	}
	//////////
}


void gamemanger::set_startpos() 
{
	std::string iconstr="";
	for (auto i : PlayingData_monster.monster_status)
	{
		iconstr.push_back(i.icon);
	}
	std::cout << iconstr << std::endl;
	PlayingData_map.Print_Allmap();
	PlayingData_map.Set_Monsterpos(iconstr);
	PlayingData_map.Set_Characterpos(playingData_hero.hero_amount);
	PlayingData_map.Print_Sightmap();
}
void gamemanger::play_game()
{
	std::cout << "玩遊戲中~這太好玩了吧" << std::endl;
	set_startpos();
	PlayingData_map.Print_Allmap();
	std::cout << "我贏了嗎??隨便啦..." << std::endl;

	clearPlayingdata();
}
void gamemanger::clearPlayingdata()
{
	PlayingData_monster.monster_status.clear();
	PlayingData_map.character_coordinate.clear();
	PlayingData_map.monster_coordinate.clear();
	delete[] PlayingData_map.body;
	delete[] PlayingData_map.sight;
}