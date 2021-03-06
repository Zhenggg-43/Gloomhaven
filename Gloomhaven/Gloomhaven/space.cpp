#include"gamamanager.h"
#define Map PlayingData_map
#define Monster PlayingData_monster
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
			std::cout << "輸入錯誤請輸入play 或是 exit" << std::endl;
		}
		temp.clear();
	}
}


void gamemanger::loadgame()
{
	/*temp_function();*/
	set_debugmode();
	load_file();
}
void gamemanger::temp_function(std::string character_txtname, std::string monster_txtname,int mod)
{
	/*std::cout << "請輸入角色txt檔案" << std::endl;
	std::cin >> character_txt;
	std::cout << "請輸入怪物txt檔案" << std::endl;
	std::cin >> monster_txt;*/
	//std::cout << character_txtname << "  " << monster_txtname << " " <<mod << std::endl;
	character_txt = character_txtname;
	monster_txt = monster_txtname;
	Flag_DebugMode = mod;
}
void gamemanger::load_file()
{
	load_character();
	std::cout << "角色讀取結束" << std::endl;

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
}
void gamemanger::set_debugmode() 
{
	/*std::cout << "是否要要啟用Debug Mode (0/1)\n";
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
	}*/
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
		int index = 0;
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
						temp_monster.ifdead = 0;
						temp_monster.name = monster_file.name[pos];//name
						temp_monster.hp_max = monster_file.normal[pos].hp;//basic data
						temp_monster.hp = temp_monster.hp_max;
						temp_monster.power = monster_file.normal[pos].power;
						temp_monster.range = monster_file.normal[pos].range;
						temp_monster.cards = monster_file.All_deck[pos];//deck
						temp_monster.index = index;//設定index
						index++;
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
						temp_monster.ifdead = 0;
						temp_monster.name = monster_file.name[pos];//name
						temp_monster.hp_max = monster_file.elite[pos].hp;//basic data
						temp_monster.hp = temp_monster.hp_max;
						temp_monster.power = monster_file.elite[pos].power;
						temp_monster.range = monster_file.elite[pos].range;
						temp_monster.cards = monster_file.All_deck[pos];//deck
						temp_monster.index = index;//設定index
						index++;
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
	//PlayingData_monster.printAllmonster();
	//std::cout << "你輸入了地圖你真棒!!" << std::endl;

	for (int index_ = 0; index_ < Monster.monster_amount; index_++)
	{
		for (int j = 0; j < Monster.monster_status[index_].cards.size(); j++)
		{
			Monster.monster_status[index_].hand.push_back(j);//設定起始手排cardVec
		}
	}
}
void gamemanger::set_door_amount()
{
	for (int i=0;i<PlayingData_map.Y_border;i++)
	{
		for (int j=0;j<PlayingData_map.X_border;j++)
		{
			if (PlayingData_map.body[i][j] == '3')
			{
				PlayingData_map.door_amount++;
				S_coordinate tmp;
				tmp.x = j, tmp.y = i;
				Map.door_coordinate.push_back(tmp);
			}
		}
	}
}


void gamemanger::menu()
{
	character_amount();
	characterANDskill();
	load_map();
	set_door_amount();
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
	/*for (int i=0;i< playingData_hero.hero_amount;i++)
	{
		std::cout << playingData_hero.hero_status[i].name << "  "<< playingData_hero.hero_status[i].icon<<" "<< playingData_hero.hero_status[i].hp<<" ";
		for (int j=0;j< playingData_hero.hero_status[i].hand.size();j++)
		{
			std::cout << playingData_hero.hero_status[i].hand[j] << " ";
		}
		std::cout << std::endl;
	}*/
	//////////
}

///////////////////////////////play game
void gamemanger::play_game()
{
	//std::cout << "玩遊戲中~這太好玩了吧" << std::endl;
	//設定起始位置
	set_startpos();
	set_monster_active();
	//////////////////
	Map.visible(0, 0);
	Map.Print_Allmap();
	std::cin.ignore();
	while (gameover())
	{
		print_round();
		hero_turn();
		monster_turn();
		set_order();
		print_drawing();
		round_action();
		open_door();
	}
	if (playingData_hero.hero_amount==0)
	{
		std::cout << "monster win~" << std::endl;
	}
	else
	{
		std::cout << "character win~" << std::endl;
	}

	clearPlayingdata();
}
void gamemanger::print_round()
{
	std::cout << "round " << round.round_temp++ << ":" << std::endl;
}
void gamemanger::hero_turn()
{
	//////////
	for (int i = 0; i < playingData_hero.hero_amount; i++)
	{
		if (playingData_hero.hero_status[i].deadwood.size()<2&& playingData_hero.hero_status[i].hand.size()<2)
		{
			remove_dead_hero(playingData_hero.hero_status[i].icon);
			i--;
		}
	}
	//////////
	std::stringstream ss;
	std::string temp_s="";
	int temp_i = 0;
	//////////(每輪重製round的行動順序的資料)
	round.canmove_icon.clear();
	round.agility.clear();
	round.action_creature_icon.clear();
	//////////
	for (int i = 0; i < playingData_hero.hero_amount; i++)
	{
		round.canmove_icon.push_back(playingData_hero.hero_status[i].icon);
	}
	if (round.canmove_icon.size()!=0)
	{
		std::cout << "請輸入角色與卡牌" << std::endl;//回合提示
	}
	//(看CANMOVEICON有沒有問題)
	/*for (int i=0;i<round.canmove_icon.size();i++)
	{
		std::cout << round.canmove_icon[i] << " ";
	}
	std::cout << std::endl;*/
	//
	while (round.canmove_icon.size() != 0&&std::getline(std::cin,temp_s))
	{
		
		bool exist = false;
		ss.str("");
		ss.clear();
		ss << temp_s;
		ss >> temp_s;
		if (temp_s.size()>1)
		{
			std::cout << "輸入角色名稱錯誤請重新輸入!" << std::endl;
		}
		else
		{
			for (int i = 0; i < playingData_hero.hero_amount; i++)
			{
				if (playingData_hero.hero_status[i].icon == temp_s[0])
				{
					exist = true;
					ss >> temp_s;
					if (temp_s == "check")//查看手牌
					{
						std::sort(playingData_hero.hero_status[i].hand.begin(), playingData_hero.hero_status[i].hand.end());
						std::sort(playingData_hero.hero_status[i].deadwood.begin(), playingData_hero.hero_status[i].deadwood.end());
						std::cout << "hand: ";
						for (int j = 0; j < playingData_hero.hero_status[i].hand.size(); j++)
						{
							std::cout << playingData_hero.hero_status[i].hand[j];
							if (!(j == playingData_hero.hero_status[i].hand.size() - 1))
							{
								std::cout << ", ";
							}
						}
						std::cout << "; discard: ";
						for (int j = 0; j < playingData_hero.hero_status[i].deadwood.size(); j++)
						{
							std::cout << playingData_hero.hero_status[i].deadwood[j];
							if (!(j == playingData_hero.hero_status[i].deadwood.size() - 1))
							{
								std::cout << ", ";
							}
						}
						std::cout << std::endl;
					}
					else if (temp_s == "-1")//選擇長休
					{
						if (playingData_hero.hero_status[i].deadwood.size()<2)
						{
							std::cout << "棄牌堆少於2此角色不能長休請重新輸入" << std::endl;
						}
						else
						{
							bool moved = true;
							for (int j=0;j<round.canmove_icon.size();j++)
							{
								if (round.canmove_icon[j]== playingData_hero.hero_status[i].icon)
								{
									moved = false;
									playingData_hero.hero_status[i].action_card[0] = -1;
									playingData_hero.hero_status[i].action_card[1] = 0;
									round.canmove_icon.erase(round.canmove_icon.begin() + j);
									round.action_creature_icon.push_back(playingData_hero.hero_status[i].icon);
									round.agility.push_back(99);
								}
							}
							if (moved)
							{
								std::cout << "此角色已經移動過了請輸入別的角色!" << std::endl;
							}
						}
					}
					else//選擇行動的兩張手牌
					{
						bool moved1 = true;
						for (int j = 0; j < round.canmove_icon.size(); j++)
						{
							if (round.canmove_icon[j] == playingData_hero.hero_status[i].icon)
							{
								moved1 = false;
							}
						}
						if (moved1)
						{
							std::cout << "此角色已經移動過了請輸入別的角色!" << std::endl;

						}
						else
						{
							bool havecard1 = false, havecard2 = false;;
							int temp_i = 0;
							std::stringstream temp;
							temp << temp_s;
							temp >> temp_i;
							for (int j = 0; j < playingData_hero.hero_status[i].hand.size(); j++)
							{
								if (playingData_hero.hero_status[i].hand[j] == temp_i)
								{
									havecard1 = true;
									playingData_hero.hero_status[i].action_card[0] = temp_i;
								}
							}
							ss >> temp_i;
							for (int j = 0; j < playingData_hero.hero_status[i].hand.size(); j++)
							{
								if (playingData_hero.hero_status[i].hand[j] == temp_i)
								{
									havecard2 = true;
									playingData_hero.hero_status[i].action_card[1] = temp_i;
								}
							}
							if (!havecard1 || !havecard2)
							{
								std::cout << "此角色沒有你輸入的卡牌" << std::endl;
							}
							else
							{
								if (playingData_hero.hero_status[i].action_card[0] != playingData_hero.hero_status[i].action_card[1])
								{
									bool moved = true;
									for (int j = 0; j < round.canmove_icon.size(); j++)
									{
										if (round.canmove_icon[j] == playingData_hero.hero_status[i].icon)
										{
											moved = false;
											round.canmove_icon.erase(round.canmove_icon.begin() + j);
											round.action_creature_icon.push_back(playingData_hero.hero_status[i].icon);
											for (int k = 0; k < character_file.character_amount; k++)
											{
												if (playingData_hero.hero_status[i].name == character_file.name[k])
												{
													for (int l = 0; l < character_file.deck_amount[k]; l++)
													{
														if (playingData_hero.hero_status[i].action_card[0] == character_file.deck[k][l].card_index)
														{
															round.agility.push_back(character_file.deck[k][l].agility);
															break;
														}
													}
													break;
												}
											}
											break;
										}
									}
									if (moved)
									{
										std::cout << "此角色已經移動過了請輸入別的角色!" << std::endl;
									}
								}
								else
								{
									std::cout << "你輸入了重複卡牌請重新輸入" << std::endl;
								}
							}
						}
					}
				}
			}
			if (!exist)
			{
				std::cout << "此角色不存在請重新輸入!" << std::endl;
			}

			if (round.canmove_icon.size()==0)
			{
				break;
			}
		}
	}
	//(看icon與敏捷值有沒有問題)
	//for (int i=0;i<round.action_creature_icon.size();i++)
	//{
	//	std::cout << round.action_icon[i] << " " << round.agility[i] << std::endl;
	//}
	//
}
void gamemanger::monster_turn()
{
	if (Flag_DebugMode)
	{
		for (int i = 0;i < active_monster.size();i++)
		{
			char acting_icon = active_monster[i];
			Monster[acting_icon].drew_card = Monster[acting_icon].hand[0];
			round.agility.push_back(Monster[acting_icon].cards[Monster[acting_icon].hand[0]].agility);//第一張手牌的敏捷值
			round.action_creature_icon.push_back(acting_icon);
		}
	}
	else
	{
		std::string str_mon;
		for (int i = 0;i < active_monster.size();i++)
		{
			str_mon.push_back(active_monster[i]);
		}
		for (int i = 0;i < str_mon.length();i++)
		{
			char acting_icon = str_mon[i];
			int hand_index = rand() % Monster[acting_icon].hand.size();//現有手牌index  

			round.action_creature_icon.push_back(acting_icon);//當下pos
			Monster[acting_icon].drew_card = Monster[acting_icon].hand[hand_index];
			round.agility.push_back(Monster[acting_icon].cards[Monster[acting_icon].hand[hand_index]].agility);//隨機手牌的敏捷值
			for (int j = i + 1;j < str_mon.length();j++)
			{
				if (Monster[acting_icon].name == Monster[str_mon[j]].name)//同種怪物給予相同卡牌
				{
					round.action_creature_icon.push_back(str_mon[j]);
					Monster[str_mon[j]].drew_card = Monster[str_mon[j]].hand[hand_index];
					round.agility.push_back(Monster[str_mon[j]].cards[Monster[str_mon[j]].hand[hand_index]].agility);
					str_mon.erase(j,j);
					j--;
				}
			}
			
		}
	}
}



void gamemanger::set_order()//依照敏捷設定順序
{
	//
	/*for (int i = 0; i < round.action_creature_icon.size(); i++)
	{
		std::cout << round.action_creature_icon[i] << " " << round.agility[i] << std::endl;;
	}*/
	//
	std::vector<char> temp_c_1;
	std::vector<std::vector<char>> temp_c_2;
	temp_c_1.clear();
	temp_c_2.clear();
	for (int i = 0; i < round.action_creature_icon.size(); i++)
	{
		temp_c_1.push_back(round.agility[i]);
		temp_c_1.push_back(round.action_creature_icon[i]);
		temp_c_2.push_back(temp_c_1);
		temp_c_1.clear();
	}
	std::sort(temp_c_2.begin(), temp_c_2.end());
	for (int i=0; i < (int(round.action_creature_icon.size())-1); i++)
	{
		for (int j = 0; j < round.action_creature_icon.size()-i-1; j++)
		{
			if (temp_c_2[j][0]==temp_c_2[j+1][0])
			{
				if ((temp_c_2[j][1]<='z'&& temp_c_2[j][1] >= 'a')&& (temp_c_2[j+1][1] <= 'Z' && temp_c_2[j+1][1] >= 'A'))
				{
					char temp_c=' ';
					temp_c = temp_c_2[j][1];
					temp_c_2[j][1] = temp_c_2[j + 1][1];
					temp_c_2[j + 1][1] = temp_c;
				}
				else if ((temp_c_2[j][1] <= 'Z' && temp_c_2[j][1] >= 'A') && (temp_c_2[j + 1][1] <= 'Z' && temp_c_2[j + 1][1] >= 'A'))
				{
					int temp_i_1 = 0,temp_i_2=0;
					for (int k=0;k<playingData_hero.hero_amount;k++)
					{
						if (temp_c_2[j][1]==playingData_hero.hero_status[k].icon)
						{
							for (int l = 0; l < character_file.character_amount; l++)
							{
								if (playingData_hero.hero_status[k].name == character_file.name[l])
								{
									for (int m = 0; m < character_file.deck_amount[l]; m++)
									{
										if (playingData_hero.hero_status[k].action_card[1] == character_file.deck[l][m].card_index)
										{
											temp_i_1 = character_file.deck[l][m].agility;
											break;
										}
									}
									break;
								}
							}
							break;
						}
					}
					for (int k = 0; k < playingData_hero.hero_amount; k++)
					{
						if (temp_c_2[j+1][1] == playingData_hero.hero_status[k].icon)
						{
							for (int l = 0; l < character_file.character_amount; l++)
							{
								if (playingData_hero.hero_status[k].name == character_file.name[l])
								{
									for (int m = 0; m < character_file.deck_amount[l]; m++)
									{
										if (playingData_hero.hero_status[k].action_card[1] == character_file.deck[l][m].card_index)
										{
											temp_i_2 = character_file.deck[l][m].agility;
											break;
										}
									}
									break;
								}
							}
							break;
						}
					}
					if (temp_i_1>temp_i_2)
					{
						char temp_c = ' ';
						temp_c = temp_c_2[j][1];
						temp_c_2[j][1] = temp_c_2[j + 1][1];
						temp_c_2[j + 1][1] = temp_c;
					}
					else if (temp_i_1 == temp_i_2)
					{
						if (temp_c_2[j][1]> temp_c_2[j+1][1])
						{
							char temp_c = ' ';
							temp_c = temp_c_2[j][1];
							temp_c_2[j][1] = temp_c_2[j + 1][1];
							temp_c_2[j + 1][1] = temp_c;
						}
					}
				}
				else if ((temp_c_2[j][1] <= 'z' && temp_c_2[j][1] >= 'a') && (temp_c_2[j + 1][1] <= 'z' && temp_c_2[j + 1][1] >= 'a'))
				{
					std::string temp_s_1, temp_s_2;
					for (int l = 0; l < PlayingData_monster.monster_status.size(); l++)
					{
						if (temp_c_2[j][1] == PlayingData_monster.monster_status[l].icon)
						{
							temp_s_1 = PlayingData_monster.monster_status[l].name;
						}
					}
					for (int l = 0; l < PlayingData_monster.monster_status.size(); l++)
					{
						if (temp_c_2[j + 1][1] == PlayingData_monster.monster_status[l].icon)
						{
							temp_s_2 = PlayingData_monster.monster_status[l].name;
						}
					}
					if (temp_s_1 == temp_s_2)
					{
						if (temp_c_2[j][1] > temp_c_2[j + 1][1])
						{
							char temp_c = ' ';
							temp_c = temp_c_2[j][1];
							temp_c_2[j][1] = temp_c_2[j + 1][1];
							temp_c_2[j + 1][1] = temp_c;
						}
					}
					else
					{
						bool temp_b = true;
						for (int l = 0; l < temp_s_1.size() && l < temp_s_2.size(); l++)
						{
							if (temp_s_1[l] > temp_s_2[l])
							{
								temp_b = false;
								char temp_c = ' ';
								temp_c = temp_c_2[j][1];
								temp_c_2[j][1] = temp_c_2[j + 1][1];
								temp_c_2[j + 1][1] = temp_c;
								break;
							}
							else if (temp_s_1[l] < temp_s_2[l])
							{
								temp_b = false;
								break;
							}
						}
						if (temp_b && temp_s_1.size() > temp_s_2.size())
						{
							char temp_c = ' ';
							temp_c = temp_c_2[j][1];
							temp_c_2[j][1] = temp_c_2[j + 1][1];
							temp_c_2[j + 1][1] = temp_c;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < round.action_creature_icon.size(); i++)
	{
		round.agility[i] = temp_c_2[i][0];
		round.action_creature_icon[i] = temp_c_2[i][1];
	}
	//(輸出排序完的ICON與敏捷值)
	/*for (int i = 0; i < round.action_creature_icon.size(); i++)
	{
		std::cout << round.action_creature_icon[i] << " " << round.agility[i] << std::endl;
	}*/
}
void gamemanger::print_drawing()//輸出行動順序
{
	std::vector<std::string>tmp_name;

	for (int i = 0; i < round.action_creature_icon.size(); i++)
	{
		if (round.action_creature_icon[i]<='Z'&& round.action_creature_icon[i]>='A')//玩家
		{
			std::cout << round.action_creature_icon[i] << " ";
			if (round.agility[i]<10)
			{
				std::cout << "0";
			}
			std::cout << round.agility[i]<<" ";
			for (int j=0;j<playingData_hero.hero_amount;j++)
			{
				if (round.action_creature_icon[i]==playingData_hero.hero_status[j].icon)
				{
					std::cout << playingData_hero.hero_status[j].action_card[0];
					if (playingData_hero.hero_status[j].action_card[0]!=-1)
					{
						std::cout <<" "<< playingData_hero.hero_status[j].action_card[1];
					}
					std::cout << std::endl;
					break;
				}
			}
		}
		else if (round.action_creature_icon[i] <= 'z' && round.action_creature_icon[i] >= 'a')//怪獸
		{
			if (tmp_name.empty())
			{
				tmp_name.push_back(Monster[round.action_creature_icon[i]].name);
				Monster.printmonstercard(round.action_creature_icon[i], Monster[round.action_creature_icon[i]].drew_card);
			}
			else 
			{
				bool Flag_print=1;
				for (auto for_I : tmp_name)
				{
					if (for_I == Monster[round.action_creature_icon[i]].name)
						Flag_print = 0;
				}
				if (Flag_print)
				{
					Monster.printmonstercard(round.action_creature_icon[i], Monster[round.action_creature_icon[i]].drew_card);
					tmp_name.push_back(Monster[round.action_creature_icon[i]].name);
				}
			}
			
		}
		
	}
}



void gamemanger::round_action()
{
	for (int i = 0; i < round.action_creature_icon.size(); i++)
	{
		if (round.action_creature_icon[i] <= 'Z' && round.action_creature_icon[i] >= 'A')//玩家
		{
			hero_action(round.action_creature_icon[i]);
		}
		else if (round.action_creature_icon[i] <= 'z' && round.action_creature_icon[i] >= 'a')//怪獸
		{
			monster_action(round.action_creature_icon[i]);
		}
	}
	deal_nextround();
}
std::string print_card(int input)
{
	if (input ==Action::Move)
		return "Move ";
	else if (input == Action::Attack)
		return "Attack ";
	else if (input==Action::Heal)
		return  "Heal ";
	else if (input == Action::Shield)
		return  "Shield ";
	else if (input == Action::Range)
		return  "Range ";
}
void gamemanger::hero_action(char &hero)//玩家行動
{
	for (int i=0;i<playingData_hero.hero_amount;i++)
	{
		if (playingData_hero.hero_status[i].icon==hero)//找要行動角色
		{
			if (playingData_hero.hero_status[i].action_card[0]==-1)
			{
				std::cout << hero << "'s turn: card " << playingData_hero.hero_status[i].action_card[0] << std::endl;
				int b; bool a; hero_action__deal(3, 2, b, a, hero);
				std::cout << hero << "'s discard :";
				for (int j = 0; j < playingData_hero.hero_status[i].deadwood.size(); j++)
				{
					std::cout << " " << playingData_hero.hero_status[i].deadwood[j];
				}
				std::cout << std::endl << "請輸入你要丟棄的卡牌 :";
				int temp_i=0;
				bool have_card = false;
				while (std::cin >> temp_i)
				{
					for (int j=0;j<playingData_hero.hero_status[i].deadwood.size();j++)//找棄牌堆要移除的牌
					{
						if (temp_i== playingData_hero.hero_status[i].deadwood[j])
						{
							playingData_hero.hero_status[i].deadwood.erase(playingData_hero.hero_status[i].deadwood.begin()+j);

							for (int l = 0; l < playingData_hero.hero_status[i].deadwood.size(); l++)
							{
								playingData_hero.hero_status[i].hand.push_back(playingData_hero.hero_status[i].deadwood[l]);
							}
							playingData_hero.hero_status[i].deadwood.clear();

							have_card = true;
							break;
						}
					}
					if (have_card)
					{
						std::cout << "remove card: " << temp_i << std::endl;
						break;
					}
					else
					{
						std::cout << "你輸入了棄牌堆沒有的牌請重新輸入" << std::endl;
					}
				}
				std::cin.ignore();
			}
			else
			{
				std::cout << hero << "'s turn: card " << playingData_hero.hero_status[i].action_card[0] << " " << playingData_hero.hero_status[i].action_card[1] << std::endl;
				//(輸出當前選擇卡片的上下效果)
				std::cout << "card " << playingData_hero.hero_status[i].action_card[0] << " :";
				for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].up_effect.card_type.size(); j++)
				{
					std::cout << " " << print_card(character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].up_effect.card_type[j]) << " " << character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].up_effect.card_power[j];
				}
				std::cout << " <-> ";
				for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].down_effect.card_type.size(); j++)
				{
					std::cout << " " << print_card(character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].down_effect.card_type[j]) << " " << character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].down_effect.card_power[j];
				}
				std::cout << std::endl << "card " << playingData_hero.hero_status[i].action_card[1] << " :";
				for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].up_effect.card_type.size(); j++)
				{
					std::cout << " " << print_card(character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].up_effect.card_type[j]) << " " << character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].up_effect.card_power[j];
				}
				std::cout << " <-> ";
				for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].down_effect.card_type.size(); j++)
				{
					std::cout << " " << print_card(character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].down_effect.card_type[j]) << " " << character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].down_effect.card_power[j];
				}
				std::cout<<std::endl;
				//
				std::string temp_s;
				bool attack = false;
				int attack_power = 0;
				while (std::getline(std::cin, temp_s))
				{
					if (temp_s == "check")
					{
						print_check();
						continue;
					}
					if (temp_s.size() == 2)
					{
						if ((temp_s[0] - '0' == playingData_hero.hero_status[i].action_card[0] || temp_s[0] - '0' == playingData_hero.hero_status[i].action_card[1]) && (temp_s[1] == 'u' || temp_s[1] == 'd'))
						{
							if (temp_s[0] - '0' == playingData_hero.hero_status[i].action_card[0])//第一張行動卡
							{
								if (temp_s[1] == 'u')//上面
								{
									for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].up_effect.card_type.size(); j++)
									{
										if (character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].up_effect.card_type[j] != Action::Range && attack)
										{
											hero_action__deal(Action::Range, 1, attack_power, attack, hero);
										}

										hero_action__deal(character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].up_effect.card_type[j], character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].up_effect.card_power[j], attack_power, attack, hero);
									}
									//
									if (attack)
									{
										hero_action__deal(Action::Range, 1, attack_power, attack, hero);
									}

									for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].down_effect.card_type.size(); j++)
									{
										if (character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].down_effect.card_type[j] != Action::Range && attack)
										{
											hero_action__deal(Action::Range, 1, attack_power, attack, hero);
										}

										hero_action__deal(character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].down_effect.card_type[j], character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].down_effect.card_power[j], attack_power, attack, hero);
									}

									if (attack)
									{
										hero_action__deal(Action::Range, 1, attack_power, attack, hero);
									}
								}
								else//下面
								{
									for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].down_effect.card_type.size(); j++)
									{
										if (character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].down_effect.card_type[j] != Action::Range && attack)
										{
											hero_action__deal(Action::Range, 1, attack_power, attack, hero);
										}

										hero_action__deal(character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].down_effect.card_type[j], character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].down_effect.card_power[j], attack_power, attack, hero);
									}
									//
									if (attack)
									{
										hero_action__deal(Action::Range, 1, attack_power, attack, hero);
									}

									for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].up_effect.card_type.size(); j++)
									{
										if (character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].up_effect.card_type[j] != Action::Range && attack)
										{
											hero_action__deal(Action::Range, 1, attack_power, attack, hero);
										}

										hero_action__deal(character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].up_effect.card_type[j], character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].up_effect.card_power[j], attack_power, attack, hero);
									}

									if (attack)
									{
										hero_action__deal(Action::Range, 1, attack_power, attack, hero);
									}
								}
							}
							else//第二張行動卡
							{
								if (temp_s[1] == 'u')//上面
								{
									for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].up_effect.card_type.size(); j++)
									{
										if (character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].up_effect.card_type[j] != Action::Range && attack)
										{
											hero_action__deal(Action::Range, 1, attack_power, attack, hero);
										}

										hero_action__deal(character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].up_effect.card_type[j], character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].up_effect.card_power[j], attack_power, attack, hero);
									}
									//
									if (attack)
									{
										hero_action__deal(Action::Range, 1, attack_power, attack, hero);
									}

									for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].down_effect.card_type.size(); j++)
									{
										if (character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].down_effect.card_type[j] != Action::Range && attack)
										{
											hero_action__deal(Action::Range, 1, attack_power, attack, hero);
										}

										hero_action__deal(character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].down_effect.card_type[j], character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].down_effect.card_power[j], attack_power, attack, hero);
									}

									if (attack)
									{
										hero_action__deal(Action::Range, 1, attack_power, attack, hero);
									}
								}
								else//下面
								{
									for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].down_effect.card_type.size(); j++)
									{
										if (character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].down_effect.card_type[j] != Action::Range && attack)
										{
											hero_action__deal(Action::Range, 1, attack_power, attack, hero);
										}

										hero_action__deal(character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].down_effect.card_type[j], character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].down_effect.card_power[j], attack_power, attack, hero);
									}
									//
									if (attack)
									{
										hero_action__deal(Action::Range, 1, attack_power, attack, hero);
									}

									for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].up_effect.card_type.size(); j++)
									{
										if (character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].up_effect.card_type[j] != Action::Range && attack)
										{
											hero_action__deal(Action::Range, 1, attack_power, attack, hero);
										}

										hero_action__deal(character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].up_effect.card_type[j], character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].up_effect.card_power[j], attack_power, attack, hero);
									}

									if (attack)
									{
										hero_action__deal(Action::Range, 1, attack_power, attack, hero);
									}
								}
							}
							//character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[j]];//該行動卡的資料
							for (int ii=0;ii<2;ii++)
							{
								for (int j = 0; j < playingData_hero.hero_status[i].hand.size(); j++)
								{
									if (playingData_hero.hero_status[i].hand[j]== playingData_hero.hero_status[i].action_card[ii])
									{
										playingData_hero.hero_status[i].hand.erase(playingData_hero.hero_status[i].hand.begin()+j);
										playingData_hero.hero_status[i].deadwood.push_back(playingData_hero.hero_status[i].action_card[ii]);
										break;
									}
								}
							}
							break;
						}
						else
						{
							std::cout << "請輸入正確行動格式 格式為:Xu or Xd" << std::endl;
						}
					}
					else
					{
						std::cout << "移動輸入格式錯誤請重新輸入" << std::endl;
					}
				}
			}
		}
	}
}
void gamemanger::hero_action__deal(int type, int power, int& attack_power, bool& attack, char& hero_icon)
{
	if (type == Action::Attack)
	{
		attack = true;
		attack_power = power;
	}
	else if (type == Action::Move)
	{
		std::cout << "Move " << power << std::endl;
		std::string temp_s;
		bool ac = true;
		while (std::getline(std::cin, temp_s))
		{
			if (temp_s=="check")
			{
				print_check();
				continue;
			}
			if (power >= temp_s.size() && temp_s.size() > 0)
			{
				if (temp_s[0] == 'e')
				{
					break;
				}
				for (int i = 0; i < temp_s.size(); i++)
				{
					if (temp_s[i] != 'w' && temp_s[i] != 'a' && temp_s[i] != 's' && temp_s[i] != 'd')
					{
						ac = false;
						break;
					}
				}
				if (ac)
				{
					int temp_i = 0;
					for (int i = 0; i < playingData_hero.hero_amount; i++)
					{
						if (playingData_hero.hero_status[i].icon == hero_icon)
						{
							temp_i = i;
						}
					}
					if (PlayingData_map.character_Move(temp_i, hero_icon, temp_s))
					{
						PlayingData_map.Print_Sightedmap();
						break;
					}
					else
					{
						std::cout << "error move!!!" << std::endl;
					}
				}
				else
				{
					std::cout << "移動輸入含wasd以外字元請重新輸入" << std::endl;
				}
			}
			else
			{
				std::cout << "移動步數輸入錯誤請重新輸入" << std::endl;
			}
		}
	}
	else if (type == Action::Heal)
	{
		std::cout << hero_icon << " heal " << power << ", now hp is ";
		for (int i = 0; i < playingData_hero.hero_amount; i++)
		{
			if (playingData_hero.hero_status[i].icon == hero_icon)
			{
				playingData_hero.hero_status[i].hp += power;
				for (int j = 0; j < character_file.character_amount; j++)
				{
					if (playingData_hero.hero_status[i].name == character_file.name[j])
					{
						if (playingData_hero.hero_status[i].hp > character_file.hp[j])
						{
							playingData_hero.hero_status[i].hp = character_file.hp[j];
						}
					}
				}
				std::cout << playingData_hero.hero_status[i].hp << std::endl;
				break;
			}
		}
	}
	else if (type == Action::Shield)
	{
		for (int i = 0; i < playingData_hero.hero_amount; i++)
		{
			if (playingData_hero.hero_status[i].icon == hero_icon)
			{
				playingData_hero.hero_status[i].shield += power;

				break;
			}
		}
		std::cout << hero_icon << " shield " << power << " this turn" << std::endl;
	}
	else if (type == Action::Range)
	{
		attack = false;
		std::cout << "Attack " << attack_power << " Range " << power << std::endl;

		//
		std::string temp_s;
		while (std::getline(std::cin, temp_s))
		{
			if (temp_s == "check")
			{
				print_check();
				continue;
			}
			if (temp_s.size() == 1)
			{
				bool attacked = false;
				if (temp_s[0] == '0')
				{
					break;
				}
				for (int i = 0; i < playingData_hero.hero_amount; i++)
				{
					if (playingData_hero.hero_status[i].icon == hero_icon)
					{
						bool ha = false;
						for (int j = 0; j < active_monster.size(); j++)
						{
							if (temp_s[0] == active_monster[j])
							{
								ha = true;
							}
						}
						if (ha && PlayingData_map.visible(i, Monster[temp_s[0]].index) && PlayingData_map.countRange(i, Monster[temp_s[0]].index) <= power && (!Monster[temp_s[0]].ifdead))
						{
							attacked = true;
							monster_takedamage(temp_s[0], hero_icon, attack_power);
						}
						else
						{
							std::cout << "error target!!!" << std::endl;
						}
						break;
					}
				}
				if (attacked)
				{
					break;
				}
			}
			else
			{
				std::cout << "輸入格式錯誤請輸入想攻擊的怪物icon或者0放棄攻擊" << std::endl;
			}
		}
	}
}
void gamemanger::print_check()
{
	for (int i=0;i<playingData_hero.hero_amount;i++)
	{
		std::cout<< playingData_hero.hero_status[i].icon << " hp: " << playingData_hero.hero_status[i].hp << ", shield: " << playingData_hero.hero_status[i].shield << std::endl;
	}
	PlayingData_monster.printcheck(active_monster);
}
int gamemanger::find_secagility(char icon)
{
	int sec_agility;
	for (int j = 0; j < playingData_hero.hero_amount; j++)
	{
		if (icon == playingData_hero.hero_status[j].icon)
		{
			for (int k = 0; k < character_file.character_amount; k++)
			{
				if (playingData_hero.hero_status[j].name == character_file.name[k])
				{
					for (int l = 0; l < character_file.deck_amount[k]; l++)
					{
						if (playingData_hero.hero_status[j].action_card[1] == character_file.deck[k][l].card_index)
						{
							sec_agility = character_file.deck[k][l].agility;
							return sec_agility;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
}
void gamemanger::monster_action(const char& icon)//敵人行動
{
	Monster[icon].round_gain.shield_gain = 0;
	int card_index = Monster[icon].drew_card;
	for (auto skill : Monster[icon].cards[card_index].skill)//執行指定怪物 指定卡牌的技能
	{
		if (skill.type == Action::Attack)
		{
			char target = '0';
			int nearest_d = 99999999;
			int fastest = 100;
			if (Monster[icon].range == 0 || Monster[icon].range + skill.attack.range == 1)//近戰
			{
				int m_xpos = Map.monster_coordinate[Monster[icon].index].x, m_ypos = Map.monster_coordinate[Monster[icon].index].y;
				//決定目標
				if (m_xpos + 1 < Map.X_border)//在地圖範圍內
				{
					if (Map.body[m_ypos][m_xpos + 1] >= 'A' && Map.body[m_ypos][m_xpos + 1] <= 'Z')//位置有角色
					{
						char temp_c = Map.body[m_ypos][m_xpos + 1];
						//搜索敏捷
						for (int i = 0; i < round.action_creature_icon.size(); i++)
						{
							if (round.action_creature_icon[i] == temp_c)
							{
								if (round.agility[i] < fastest)//敏捷最小為目標
								{
									fastest = round.agility[i];
									target = temp_c;
								}
								else if (round.agility[i] == fastest)//比較第二張牌
								{
									int sec_agility = find_secagility(temp_c);
									int target_sec_agility = find_secagility(target);
									if (sec_agility < target_sec_agility)
									{
										target = temp_c;
									}
								}
							}
						}
					}
				}
				if (m_xpos - 1 >= 0)//在地圖範圍內
				{
					if (Map.body[m_ypos][m_xpos - 1] >= 'A' && Map.body[m_ypos][m_xpos - 1] <= 'Z')//位置有角色
					{
						char temp_c = Map.body[m_ypos][m_xpos - 1];
						for (int i = 0; i < round.action_creature_icon.size(); i++)
						{
							if (round.action_creature_icon[i] == temp_c)//搜索敏捷
							{
								if (round.agility[i] < fastest)//敏捷最小為目標
								{
									fastest = round.agility[i];
									target = temp_c;
								}
								else if (round.agility[i] == fastest)//比較第二張牌
								{
									int sec_agility = find_secagility(temp_c);
									int target_sec_agility = find_secagility(target);
									if (sec_agility < target_sec_agility)
									{
										target = temp_c;
									}
								}
							}
						}
					}
				}
				if (m_ypos + 1 < Map.Y_border)//在地圖範圍內
				{
					if (Map.body[m_ypos + 1][m_xpos] >= 'A' && Map.body[m_ypos + 1][m_xpos] <= 'Z')//位置有角色
					{
						char temp_c = Map.body[m_ypos + 1][m_xpos];
						for (int i = 0; i < round.action_creature_icon.size(); i++)
						{
							if (round.action_creature_icon[i] == temp_c)//搜索敏捷
							{
								if (round.agility[i] < fastest)//敏捷最小為目標
								{
									fastest = round.agility[i];
									target = temp_c;
								}
								else if (round.agility[i] == fastest)//比較第二張牌
								{
									int sec_agility = find_secagility(temp_c);
									int target_sec_agility = find_secagility(target);
									if (sec_agility < target_sec_agility)
									{
										target = temp_c;
									}
								}
							}
						}
					}
				}
				if (m_ypos - 1 >= 0)//在地圖範圍內
				{
					if (Map.body[m_ypos - 1][m_xpos] >= 'A' && Map.body[m_ypos - 1][m_xpos] <= 'Z')//位置有角色
					{
						char temp_c = Map.body[m_ypos - 1][m_xpos];
						for (int i = 0; i < round.action_creature_icon.size(); i++)
						{
							if (round.action_creature_icon[i] == temp_c)//搜索敏捷
							{
								if (round.agility[i] < fastest)//敏捷最小為目標
								{
									fastest = round.agility[i];
									target = temp_c;
								}
								else if (round.agility[i] == fastest)//比較第二張牌
								{
									int sec_agility = find_secagility(temp_c);
									int target_sec_agility = find_secagility(target);
									if (sec_agility < target_sec_agility)
									{
										target = temp_c;
									}
								}
							}
						}
					}
				}
				//動作
				if (target == '0')
				{
					std::cout << "no one lock\n";
				}
				else
				{
					std::cout << icon << " lock " << target << " in distance 1" << std::endl;
					hero_takedamage(icon, target, Monster[icon].power + skill.attack.attpower);
				}
			}
			else//遠程
			{
				//決定目標
				for (int i = 0; i < playingData_hero.hero_status.size(); i++)
				{
					if (Map.countRange(i, Monster[icon].index) <= Monster[icon].range + skill.attack.range)//在攻擊範圍內
					{
						if (Map.visible(i, Monster[icon].index))//有視野
						{
							if (Map.countRange(i, Monster[icon].index) < nearest_d)//比距離
							{
								nearest_d = Map.countRange(i, Monster[icon].index);//distance
								target = playingData_hero.hero_status[i].icon;//icon
								for (int j = 0; j < round.action_creature_icon.size(); j++)//agility
								{
									if (round.action_creature_icon[j] == playingData_hero.hero_status[i].icon)
									{
										fastest = round.agility[j];
									}
								}
							}
							else if (Map.countRange(i, Monster[icon].index) == nearest_d)
							{
								for (int j = 0; j < round.action_creature_icon.size(); j++)//比敏捷
								{
									if (round.action_creature_icon[j] == playingData_hero.hero_status[i].icon)
									{
										if (round.agility[j] < fastest)
										{
											fastest = round.agility[j];//agility
											target = playingData_hero.hero_status[i].icon;//icon
										}
										else if (round.agility[j] == fastest)//比較第二張牌
										{
											int sec_agiliry = find_secagility(playingData_hero.hero_status[i].icon);
											int target_sec_agiliry = find_secagility(target);
											if (sec_agiliry < target_sec_agiliry)
											{
												target = playingData_hero.hero_status[i].icon;//icon
											}
											//else if (sec_agiliry == target_sec_agiliry)//比ICON
											//{
											//	if(playingData_hero.hero_status[i].icon<target)
											//}
										}
									}
								}
							}
						}
					}
				}
				//動作
				if (target == '0')
				{
					std::cout << "no one lock\n";
				}
				else
				{
					std::cout << icon << " lock " << target << " in distance " << nearest_d << std::endl;
					hero_takedamage(icon, target, Monster[icon].power + skill.attack.attpower);
				}
			}

			if (!Flag_DebugMode)//normalMode 需要GETCHAR等戴
			{
				getchar();
			}
		}
		else if (skill.type == Action::Heal)
		{
			Monster[icon].hp += skill.skillpower;
			if (Monster[icon].hp > Monster[icon].hp_max)//回復超過則修正
			{
				Monster[icon].hp = Monster[icon].hp_max;
			}
			std::cout << icon << ' ' << "heal " << skill.skillpower << ", now hp is " << Monster[icon].hp << std::endl;
			if (!Flag_DebugMode)//normalMode 需要GETCHAR等戴
			{
				getchar();
			}
		}
		else if (skill.type == Action::Move)
		{
			PlayingData_map.creature_Move(Monster[icon].index, icon, skill.movement);
			PlayingData_map.Print_Sightedmap();
			if (!Flag_DebugMode)//normalMode 需要GETCHAR等戴
			{
				getchar();
			}
		}
		else if (skill.type == Action::Shield)
		{
			Monster[icon].round_gain.shield_gain += skill.skillpower;
			std::cout << icon << ' ' << "shield " << skill.skillpower << " this turn\n";
			if (!Flag_DebugMode)//normalMode 需要GETCHAR等戴
			{
				getchar();
			}
		}
	}

	//處理手牌與棄牌
	if (PlayingData_monster[icon].cards[card_index].suffle_sign == 1)//有重洗標誌將牌組重製
	{
		Monster[icon].hand.clear();
		for (int i = 0; i < Monster[icon].cards.size(); i++)
		{
			Monster[icon].hand.push_back(i);
		}

	}
	else//沒有 將牌移至棄牌堆
	{
		//Monster[icon].discard.push_back(Monster[icon].drew_card);

		for (std::vector<int>::iterator hand_iter = PlayingData_monster[icon].hand.begin(); hand_iter < Monster[icon].hand.end(); hand_iter++)
		{
			if (*hand_iter == Monster[icon].drew_card)
			{
				Monster[icon].hand.erase(hand_iter);//清除
				break;
			}
		}
	}
}



void gamemanger::hero_takedamage(char monster_icon,char hero_icon, int damage)
{
	if (damage < 0)//負攻擊修正
		damage = 0;
	for (int i=0;i<playingData_hero.hero_amount;i++)
	{
		if (hero_icon==playingData_hero.hero_status[i].icon)
		{
			std::cout << monster_icon << " attack " << hero_icon << " " << damage << " damage, " << hero_icon << " shield " << playingData_hero.hero_status[i].shield << ", " << hero_icon << " remain ";
			if(playingData_hero.hero_status[i].shield<damage)
			{
				damage -= playingData_hero.hero_status[i].shield;
				playingData_hero.hero_status[i].hp -= damage;
			}
			std::cout << playingData_hero.hero_status[i].hp << " hp" << std::endl;
			if (playingData_hero.hero_status[i].hp<=0)
			{
				remove_dead_hero(hero_icon);
			}
			break;
		}
	}
}
void gamemanger::monster_takedamage(char monster_icon, char character_icon, int damage)
{
	//A attack a 3 damage, a shield 1, a remain 12 hp
	if (damage < 0)//負攻擊修正
		damage = 0;
	std::cout << character_icon << " attack " << monster_icon << ' ' << damage << " damage, " << monster_icon << " shield " << Monster[monster_icon].round_gain.shield_gain << ", " << monster_icon << " remain ";
	if (Monster[monster_icon].round_gain.shield_gain<damage)
	{
		damage -= Monster[monster_icon].round_gain.shield_gain;
		Monster[monster_icon].hp -= damage;
	}

	std::cout << Monster[monster_icon].hp << " hp\n";
	if (Monster[monster_icon].hp <= 0)
	{
		Monster[monster_icon].ifdead = 1;//死亡
		PlayingData_map.monster_killed(Monster[monster_icon].index);//從地圖上磨除
		remove_action_icon(monster_icon);//從行動柱列中移除
		for (int k = 0;k < active_monster_amount;k++)
		{
			if (monster_icon == active_monster[k])
			{
				active_monster.erase(active_monster.begin() + k);
				break;
			}
		}
		active_monster_amount--;
		PlayingData_monster.monster_amount--;
		std::cout << monster_icon << " is killed!!\n";
		PlayingData_map.Print_Sightedmap();
		/////////////////////////處理手牌/////////////////////////////////
		bool if_moved = 0;
		for (int i = 0; i <= Monster[monster_icon].hand.size(); i++)
		{
			if (i == Monster[monster_icon].hand.size())//以行動
			{
				if_moved = 1;
				break;
			}
			else
			{
				if (Monster[monster_icon].hand[i] == Monster[monster_icon].drew_card)
				{
					break;
				}
			}
		}
		if (!if_moved)//為行動 更新手排
		{
			int card_index = Monster[monster_icon].drew_card;
			if (PlayingData_monster[monster_icon].cards[card_index].suffle_sign == 1)//有重洗標誌將牌組重製
			{
				Monster[monster_icon].hand.clear();
				for (int i = 0; i < Monster[monster_icon].cards.size(); i++)
				{
					Monster[monster_icon].hand.push_back(i);
				}

			}
			else//沒有 將牌移至棄牌堆
			{
				//Monster[icon].discard.push_back(Monster[icon].drew_card);

				for (std::vector<int>::iterator hand_iter = PlayingData_monster[monster_icon].hand.begin(); hand_iter < Monster[monster_icon].hand.end(); hand_iter++)
				{
					if (*hand_iter == Monster[monster_icon].drew_card)
					{
						Monster[monster_icon].hand.erase(hand_iter);//清除
						break;
					}
				}
			}
		}
		//更新門後怪物手排
		if (active_monster.empty())
		{
			for (int m = 0; m < Monster.monster_status.size(); m++)
			{
				if (!Monster.monster_status[m].ifdead)//死亡不更新
				{
					if (Monster[monster_icon].name == Monster.monster_status[m].name)
					{
						Monster.monster_status[m].hand = Monster[monster_icon].hand;
					}
				}
			}
		}
		else
		{
			bool lastone = 1;
			for (int i = 0; i < active_monster.size(); i++)
			{
				if (Monster[active_monster[i]].name == Monster[monster_icon].name)
				{
					lastone = 0;
					break;
				}
			}
			if (lastone)
			{
				for (int m = 0; m < Monster.monster_status.size(); m++)
				{
					if (!Monster.monster_status[m].ifdead)//死亡不更新
					{
						if (Monster[monster_icon].name == Monster.monster_status[m].name)
						{
							Monster.monster_status[m].hand = Monster[monster_icon].hand;
						}
					}
				}
			}
		}
	}
}
void gamemanger::remove_dead_hero(char hero_icon)
{
	for (int i =0;i<playingData_hero.hero_amount;i++)
	{
		if (playingData_hero.hero_status[i].icon== hero_icon)
		{
			playingData_hero.hero_status.erase(playingData_hero.hero_status.begin()+i);
			PlayingData_map.character_killed(i);
			remove_action_icon(hero_icon);
			std::cout <<hero_icon<<" is killed"<<std::endl;
			PlayingData_map.Print_Sightedmap();
			break;
		}
	}
	playingData_hero.hero_amount--;
}
void gamemanger::remove_action_icon(char icon)
{
	for (int i=0;i<round.action_creature_icon.size();i++)
	{
		if (round.action_creature_icon[i]==icon)
		{
			round.action_creature_icon[i] = '0';
		}
	}
}



void gamemanger::deal_nextround()//處理每一輪攻擊的重製例如判斷死亡
{
	for (int i=0;i<playingData_hero.hero_amount;i++)//清空所有英雄的護甲值
	{
		playingData_hero.hero_status[i].shield = 0;
	}
	for (auto &mon : PlayingData_monster.monster_status)
	{
		mon.round_gain.shield_gain = 0;
	}

}
void gamemanger::set_startpos() 
{
	std::string iconstr="";
	for (auto i : PlayingData_monster.monster_status)
	{
		iconstr.push_back(i.icon);
	}
	//PlayingData_map.Print_Allmap();
	PlayingData_map.Set_Monsterpos(iconstr);
	PlayingData_map.Set_Characterpos(playingData_hero.hero_amount);
	PlayingData_map.Print_Sightedmap();
}
void gamemanger::set_monster_active()//Map set sight 之後要用!!!!!!!!!!
{
	for (int i = 0;i < PlayingData_monster.monster_status.size();i++)
	{
		int X= Map.monster_coordinate[i].x, Y= Map.monster_coordinate[i].y;
		if (!Monster.monster_status[i].ifdead)
		{
			if (Map.sight[Y][X])
			{
				active_monster_amount++;
				active_monster.push_back(Monster.monster_status[i].icon);//紀錄被激活怪物
			}
		}
	}
}
void gamemanger::open_door()
{
	if (active_monster_amount == 0)//當前關卡無怪物
	{
		bool Flag_print = 0;
		for (auto c_pos : PlayingData_map.character_coordinate)
		{
			for (int k=0;k<Map.door_coordinate.size();k++)
			{
				if (c_pos.x == Map.door_coordinate[k].x && c_pos.y == Map.door_coordinate[k].y)//角色座標在門上
				{
					Flag_print = 1;
					Map.door_coordinate.erase(Map.door_coordinate.begin()+k);
					k--;
					PlayingData_map.door_amount--;
					PlayingData_map.Set_Sight(c_pos.y, c_pos.x);
					set_monster_active();
				}
			}
		}
		if (Flag_print)
		{
			PlayingData_map.Print_Sightedmap();
		}
	}
}
void gamemanger::clearPlayingdata()
{
	round.round_temp = 1;
	PlayingData_monster.monster_status.clear();
	PlayingData_map.character_coordinate.clear();
	PlayingData_map.monster_coordinate.clear();
	PlayingData_map.door_coordinate.clear();
	active_monster.clear();
	active_monster_amount = 0;
	delete[] PlayingData_map.body;
	delete[] PlayingData_map.sight;
}
bool gamemanger::gameover()/////判斷有沒有遊戲結束
{
	if (PlayingData_map.door_amount==0&&PlayingData_monster.monster_amount==0)
	{
		return false;
	}
	else if (playingData_hero.hero_amount==0)
	{
		return false;
	}
	else
	{
		return true;
	}
}