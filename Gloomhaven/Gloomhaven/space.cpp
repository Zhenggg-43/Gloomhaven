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
	std::cout << "��Jplay �άO exit" << std::endl;
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
	set_debugmode();
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
	std::cout << "Ū�������ɮפ�~~" << std::endl;
	load_character();
	std::cout << "����Ū������" << std::endl;

	std::cout << "Ū���Ǫ��ɮפ�~~" << std::endl;
	load_monster();
	std::cout << "�Ǫ�Ū������" << std::endl;
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
	std::cout << "�O�_�n�n�ҥ�Debug Mode (0/1)\n";
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
			std::cout << "��J���~!!!\n";
		}
	}
}
void gamemanger::load_map()
{
	std::cout << "�п�ܦa��\n";
	std::string map_txt;
	std::cin >> map_txt;
	std::fstream file;
	file.open(map_txt, std::ios::in);
	if (file.is_open())
	{
		int xb_temp, yb_temp;
		//�]�wXY���
		file>> yb_temp >> xb_temp;
		PlayingData_map.Y_border = yb_temp;
		PlayingData_map.X_border = xb_temp;
		//�]�w�a��
		PlayingData_map.body = new std::string[yb_temp];
		for (int i = 0;i < yb_temp;i++)
		{
			file >> PlayingData_map.body[i];
		}
		//��l�Ƶ���
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
		//�]�w�i��_�l��m
		for (int i = 0;i < 4;i++)
		{
			file >> PlayingData_map.position_start[i][1] >> PlayingData_map.position_start[i][0];
		}
		//�]�w�Ǫ����
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
						temp_monster.index = index;//�]�windex
						index++;
						break;
					}
				}
				PlayingData_monster.monster_status.push_back(temp_monster);//�Ǫ����
				PlayingData_map.monster_coordinate.push_back(temp_coor);//�Ǫ��y��
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
						temp_monster.index = index;//�]�windex
						index++;
						break;
					}
				}
				PlayingData_monster.monster_status.push_back(temp_monster);//�Ǫ����
				PlayingData_map.monster_coordinate.push_back(temp_coor);//�Ǫ��y��
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
	std::cout << "�A��J�F�a�ϧA�u��!!" << std::endl;
}


void gamemanger::menu()
{
	character_amount();
	characterANDskill();
	load_map();
}
void gamemanger::character_amount()
{
	std::cout << "�п�J�X������ƶq:" << std::endl;
	while (std::cin >> playingData_hero.hero_amount)
	{
		if (playingData_hero.hero_amount >= 2 && playingData_hero.hero_amount <= 4)
		{
			break;
		}
		else
		{
			std::cout << "��J���~�п�J2~4" << std::endl;
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
	std::cout << "��J����W�ٻP�d��:" << std::endl;
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
							std::cout << "�A��J�F������S�����d�P�A�Э��s��J!" << std::endl;
						}
					}
					temp_i_vector.clear();
					if (!deck_amount_crrect)
					{
						std::cout << "��P�ƶq���ŦX�Э��s��J!" << std::endl;
					}
					break;
				}
			}
			temp_i_vector.clear();
			ss.clear();
			if (!have_char)
			{
				std::cout << "����W�٤��A��Ʈw��~~�Э��s��J!" << std::endl;
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


void gamemanger::play_game()
{
	std::cout << "���C����~�o�Ӧn���F�a" << std::endl;
	//�]�w�_�l��m
	set_startpos();
	set_monster_active();
	//////////////////
	std::cin.ignore();
	while (gameover())
	{
		print_round();
		hero_turn();
		monster_turn();
		set_order();
		print_drawing();
		round_action();
	}

	std::cout << "��Ĺ�F��??�H�K��..." << std::endl;

	clearPlayingdata();
}
void gamemanger::print_round()
{
	std::cout << "round " << round.round_temp++ << ":" << std::endl;
}
void gamemanger::hero_turn()
{
	std::stringstream ss;
	std::string temp_s="";
	int temp_i = 0;
	//////////(�C�����sround����ʶ��Ǫ����)
	round.canmove_icon.clear();
	round.agility.clear();
	round.action_creature_icon.clear();
	//////////
	for (int i = 0; i < playingData_hero.hero_amount; i++)
	{
		round.canmove_icon.push_back(playingData_hero.hero_status[i].icon);
	}
	//(��CANMOVEICON���S�����D)
	/*for (int i=0;i<round.canmove_icon.size();i++)
	{
		std::cout << round.canmove_icon[i] << " ";
	}
	std::cout << std::endl;*/
	//
	while (std::getline(std::cin,temp_s))
	{
		bool exist = false;
		ss.str("");
		ss.clear();
		ss << temp_s;
		ss >> temp_s;
		if (temp_s.size()>1)
		{
			std::cout << "��J����W�ٿ��~�Э��s��J!" << std::endl;
		}
		else
		{
			for (int i = 0; i < playingData_hero.hero_amount; i++)
			{
				if (playingData_hero.hero_status[i].icon == temp_s[0])
				{
					exist = true;
					ss >> temp_s;
					if (temp_s == "check")//�d�ݤ�P
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
					else if (temp_s == "-1")//��ܪ���
					{
						if (playingData_hero.hero_status[i].deadwood.size()<2)
						{
							std::cout << "��P��֩�2�����⤣�����Э��s��J" << std::endl;
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
									round.canmove_icon.erase(round.canmove_icon.begin() + j);
									round.action_creature_icon.push_back(playingData_hero.hero_status[i].icon);
									round.agility.push_back(99);
								}
							}
							if (moved)
							{
								std::cout << "������w�g���ʹL�F�п�J�O������!" << std::endl;
							}
						}
					}
					else//��ܦ�ʪ���i��P
					{
						bool havecard1=false, havecard2 = false;;
						int temp_i=0;
						std::stringstream temp;
						temp << temp_s;
						temp >> temp_i;
						for (int j=0;j<playingData_hero.hero_status[i].hand.size();j++)
						{
							if (playingData_hero.hero_status[i].hand[j]==temp_i)
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
						if (!havecard1||!havecard2)
						{
							std::cout << "������S���A��J���d�P" << std::endl;
						}
						else
						{
							if (playingData_hero.hero_status[i].action_card[0]!= playingData_hero.hero_status[i].action_card[1])
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
									std::cout << "������w�g���ʹL�F�п�J�O������!" << std::endl;
								}
							}
							else
							{
								std::cout << "�A��J�F���ƥd�P�Э��s��J" << std::endl;
							}
						}
					}
				}
			}
			if (!exist)
			{
				std::cout << "�����⤣�s�b�Э��s��J!" << std::endl;
			}

			if (round.canmove_icon.size()==0)
			{
				break;
			}
		}
	}
	//(��icon�P�ӱ��Ȧ��S�����D)
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
		for (int i = 0;i < active_monster_amount;i++)
		{
			char acting_icon = active_monster[i];
			Monster[acting_icon].drew_card = Monster[acting_icon].hand[0];
			round.agility.push_back(Monster[acting_icon].cards[Monster[acting_icon].hand[0]].agility);//�Ĥ@�i��P���ӱ���
			round.action_creature_icon.push_back(acting_icon);
		}
	}
	else
	{
		std::string str_mon;
		for (int i = 0;i < active_monster_amount;i++)
		{
			str_mon.push_back(active_monster[i]);
		}
		for (int i = 0;i < str_mon.length();i++)
		{
			char acting_icon = str_mon[i];
			int hand_index = rand() % Monster[acting_icon].hand.size();//�{����Pindex  

			round.action_creature_icon.push_back(acting_icon);//��Upos
			Monster[acting_icon].drew_card = Monster[acting_icon].hand[hand_index];
			round.agility.push_back(Monster[acting_icon].cards[Monster[acting_icon].hand[hand_index]].agility);//�H����P���ӱ���
			for (int j = i + 1;j < str_mon.length();j++)
			{
				if (Monster[acting_icon].name == Monster[str_mon[j]].name)//�P�ةǪ������ۦP�d�P
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

void gamemanger::set_order()//�̷ӱӱ��]�w����
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
	for (int i=0; i < round.action_creature_icon.size()-1; i++)
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
					if (temp_c_2[j][1] > temp_c_2[j + 1][1])
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

	for (int i = 0; i < round.action_creature_icon.size(); i++)
	{
		round.agility[i] = temp_c_2[i][0];
		round.action_creature_icon[i] = temp_c_2[i][1];
	}
	/*for (int i = 0; i < round.action_creature_icon.size(); i++)
	{
		std::cout << round.action_creature_icon[i] << " " << round.agility[i] << std::endl;
	}*/
}
void gamemanger::print_drawing()//��X��ʶ���
{
	for (int i = 0; i < round.action_creature_icon.size(); i++)
	{
		if (round.action_creature_icon[i]<='Z'&& round.action_creature_icon[i]>='A')//���a
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
		else if (round.action_creature_icon[i] <= 'z' && round.action_creature_icon[i] >= 'a')//���~
		{
			Monster.printmonstercard(round.action_creature_icon[i], Monster[round.action_creature_icon[i]].drew_card);
		}
		
	}
}
void gamemanger::round_action()
{
	for (int i = 0; i < round.action_creature_icon.size(); i++)
	{
		if (round.action_creature_icon[i] <= 'Z' && round.action_creature_icon[i] >= 'A')//���a
		{
			hero_action(round.action_creature_icon[i]);
		}
		else if (round.action_creature_icon[i] <= 'z' && round.action_creature_icon[i] >= 'a')//���~
		{
			monster_action(round.action_creature_icon[i]);
		}
	}
	deal_nextround();
}
void gamemanger::hero_action(char &hero)//���a���
{
	for (int i=0;i<playingData_hero.hero_amount;i++)
	{
		if (playingData_hero.hero_status[i].icon==hero)//��n��ʨ���
		{
			if (playingData_hero.hero_status[i].action_card[0]==-1)
			{
				std::cout << hero << "'s turn: card " << playingData_hero.hero_status[i].action_card[0] << std::endl;
				int b; bool a; hero_action__deal(3, 2, b, a, hero);
				int temp_i=0;
				bool have_card = false;
				while (std::cin >> temp_i)
				{
					for (int j=0;j<playingData_hero.hero_status[i].deadwood.size();j++)//���P��n�������P
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
						std::cout << "�A��J�F��P��S�����P�Э��s��J" << std::endl;
					}
				}
				std::cin.ignore();
			}
			else
			{
				std::cout << hero << "'s turn: card " << playingData_hero.hero_status[i].action_card[0] << " " << playingData_hero.hero_status[i].action_card[1] << std::endl;
				std::string temp_s;
				bool attack = false;
				int attack_power = 0;
				while (std::getline(std::cin, temp_s))
				{
					if (temp_s.size() == 2)
					{
						if ((temp_s[0] - '0' == playingData_hero.hero_status[i].action_card[0] || temp_s[0] - '0' == playingData_hero.hero_status[i].action_card[1]) && (temp_s[1] == 'u' || temp_s[1] == 'd'))
						{
							if (temp_s[0] - '0' == playingData_hero.hero_status[i].action_card[0])//�Ĥ@�i��ʥd
							{
								if (temp_s[1] == 'u')//�W��
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
								else//�U��
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
							else//�ĤG�i��ʥd
							{
								if (temp_s[1] == 'u')//�W��
								{
									for (int j = 0; j < character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[1]].up_effect.card_type.size(); j++)
									{
										if (character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[0]].up_effect.card_type[j] != Action::Range && attack)
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
								else//�U��
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
							//character_file[playingData_hero[hero].name][playingData_hero.hero_status[i].action_card[j]];//�Ӧ�ʥd�����
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
							std::cout << "�п�J���T��ʮ榡 �榡��:Xu or Xd" << std::endl;
						}
					}
					else
					{
						std::cout << "���ʿ�J�榡���~�Э��s��J" << std::endl;
					}
				}
			}
		}
	}
}
void gamemanger::hero_action__deal(int type,int power,int &attack_power,bool &attack,char &hero_icon)
{
	if (type == Action::Attack)
	{
		attack = true;
		attack_power = power;
	}
	else if(type == Action::Move)
	{
		std::cout << "Move " << power << std::endl;
		std::string temp_s;
		bool ac = true;
		while (std::getline(std::cin, temp_s))
		{
			if (power>=temp_s.size()&&temp_s.size()>0)
			{
				if (temp_s[0]=='e')
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
					if (PlayingData_map.creature_Move(hero_icon, temp_s))
					{
						PlayingData_map.Print_Sightmap();
						break;
					}
					else
					{
						std::cout << "error move!!!" << std::endl;
					}
				}
				else
				{
					std::cout << "���ʿ�J�twasd�H�~�r���Э��s��J" << std::endl;
				}
			}
			else
			{
				std::cout << "���ʨB�ƿ�J���~�Э��s��J" << std::endl;
			}
		}
	}
	else if (type == Action::Heal)
	{
		std::cout <<hero_icon<< " heal " << power <<", now hp is ";
		for (int i = 0; i < playingData_hero.hero_amount; i++)
		{
			if (playingData_hero.hero_status[i].icon == hero_icon)
			{
				playingData_hero.hero_status[i].hp += power;
				for (int j=0;j<character_file.character_amount;j++)
				{
					if (playingData_hero.hero_status[i].name== character_file.name[j])
					{
						if (playingData_hero.hero_status[i].hp> character_file.hp[j])
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
		std::cout << "Attack " << attack_power<<" Range "<<power << std::endl;

		//
		std::string temp_s;
		std::getline(std::cin, temp_s);
	}
}

void gamemanger::monster_action(const char &icon)//�ĤH���
{
	Monster[icon].round_gain.power_gain = 0;
	Monster[icon].round_gain.shield_gain = 0;
	int card_index = Monster[icon].drew_card;
	for (auto skill : Monster[icon].cards[card_index].skill)//������w�Ǫ� ���w�d�P���ޯ�
	{
		if (skill.type == Action::Attack)
		{
			std::cout << "�Ǫ�Attack!!!!\n";
			Monster[icon].round_gain.power_gain += skill.attack.attpower;//�����W�q
			//char Map.attack_function (monster index,charater index)
			//if lock (a lock A in distance 3) return 'A'
			//else (no one lock) return'0'
			if (!Flag_DebugMode)//normalMode �ݭnGETCHAR����
			{
				getchar();
			}
		}
		else if (skill.type == Action::Heal)
		{
			Monster[icon].hp += skill.skillpower;
			if (Monster[icon].hp > Monster[icon].hp_max)//�^�_�W�L�h�ץ�
			{
				Monster[icon].hp = Monster[icon].hp_max;
			}
			std::cout << icon << ' ' << "heal " << skill.skillpower << ", now hp is" << Monster[icon].hp << std::endl;
			if (!Flag_DebugMode)//normalMode �ݭnGETCHAR����
			{
				getchar();
			}
		}
		else if (skill.type == Action::Move)
		{
			PlayingData_map.creature_Move(Monster[icon].index, icon, skill.movement);
			PlayingData_map.Print_Sightmap();
			if (!Flag_DebugMode)//normalMode �ݭnGETCHAR����
			{
				getchar();
			}
		}
		else if (skill.type == Action::Shield)
		{
			Monster[icon].round_gain.shield_gain += skill.skillpower;
			std::cout << icon << ' ' <<"shield "<< skill.skillpower <<  " this turn\n";
			if (!Flag_DebugMode)//normalMode �ݭnGETCHAR����
			{
				getchar();
			}
		}
	}
	//�B�z��P�P��P
	if (Monster[icon].cards[card_index].suffle_sign == 1)//�����~�лx�N�P�խ��s????????????????????????????????/
	{
		Monster[icon].hand.clear();
		for (int i = 0;i < Monster[icon].cards.size();i++)
		{
			Monster[icon].hand.push_back(i);
		}
	}
	else//�S�� �N�P���ܱ�P��
	{
		Monster[icon].discard.push_back(Monster[icon].drew_card);

		for (std::vector<int>::iterator hand = PlayingData_monster[icon].hand.begin();hand < Monster[icon].hand.end();hand++)
		{
			if (*hand == Monster[icon].drew_card)
			{
				Monster[icon].hand.erase(hand);//�M��
				break;
			}
		}
	}
}
void gamemanger::deal_nextround()//�B�z�C�@�����������s�Ҧp�P�_���`
{
	for (int i=0;i<playingData_hero.hero_amount;i++)//�M�ũҦ��^�����@�ҭ�
	{
		playingData_hero.hero_status[i].shield = 0;
	}
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
void gamemanger::set_monster_active()//Map set sight ����n��!!!!!!!!!!
{
	for (int i = 0;i < PlayingData_monster.monster_amount;i++)
	{
		int X= Map.monster_coordinate[i].x, Y= Map.monster_coordinate[i].y;
		if (!Monster.monster_status[i].ifdead)
		{
			if (Map.sight[Y][X])
			{
				active_monster_amount++;
				active_monster.push_back(Monster.monster_status[i].icon);//�����Q�E���Ǫ�

				for (int j = 0;j < Monster.monster_status[i].cards.size();j++)
				{
					Monster.monster_status[i].hand.push_back(j);//�]�w�_�l���cardVec
				}
			}
		}
	}
}
void gamemanger::clearPlayingdata()
{
	PlayingData_monster.monster_status.clear();
	PlayingData_map.character_coordinate.clear();
	PlayingData_map.monster_coordinate.clear();
	delete[] PlayingData_map.body;
	delete[] PlayingData_map.sight;
}
bool gamemanger::gameover()/////�P�_���S���C������
{
	return true;
}