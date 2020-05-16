#pragma once
#include"Map.h"
#include"Monster.h"
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
enum Action
{
	_t_,Move,Attack,Heal,Shield,Range
};

////////////////////////////////////////////////  character
class card_skill
{
public:
	std::vector <int> card_type;
	std::vector <int> card_power;
};
class character_card
{
public:
	int card_index=0;
	int agility=0;
	card_skill up_effect;
	card_skill down_effect;
};
class character_data
{
public:
	int character_amount = 0;
	std::vector<std::string> name;
	std::vector<int> hp;
	std::vector<int> hands_amount;
	std::vector<int> deck_amount;
	std::vector<std::vector<character_card>> deck;
};

//////////////////////////////////////////////////////////playingData_hero
class hero
{
public:
	std::string name="";
	char icon = ' ';
	int hp = 0;
	std::vector<int> hand;//現在手牌
	std::vector<int> deadwood;//棄牌堆
};
class All_hero
{
public:
	int hero_amount = 0;
	std::vector<hero> hero_status;//角色狀態
};




class gamemanger
{
public:
	bool gameloop();
	bool whether_play();
	//////////
	void loadgame();
	void load_file();
	void load_character();
	void load_monster();
	//////////
	void menu();
	void character_amount();
	void characterANDskill();
	void load_map();
	//////////
	void play_game();
	//////////
	void temp_function();
private:
	std::string character_txt;
	std::string monster_txt;
	character_data character_file;
	monster_data monster_file;
	All_hero playingData_hero;
	All_monster PlayingData_monster;
	map_data PlayingData_map;
};