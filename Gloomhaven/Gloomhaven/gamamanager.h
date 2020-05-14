#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
enum Action
{
	_t_,Move,Attack,Heal,Shield
};
class card_effect
{
public:
	std::vector <int> card_type;
	std::vector <int> card_power;
};
class character_deck
{
public:
	int card_id=0;
	int move_value=0;
	card_effect up_effect;
	card_effect down_effect;
};

class monster_card
{
public:
	int card_index = 0;
	int agility = 0;
	bool suffle_sign = 0;
	std::vector<int>skill;
};


class character_data
{
public:
	int character_amount = 0;
	std::vector<std::string> name;
	std::vector<int> hp;
	std::vector<int> hands_amount;
	std::vector<int> deck_amount;
	std::vector<character_deck> deck;
};
class monster_data
{
public:
	int monster_amount = 0;
	std::vector<std::string>name;
	std::vector<int>hp_normal;
	std::vector<int>power_normal;
	std::vector<int>range_normal;
	std::vector<int>hp_elite;
	std::vector<int>power_elite;
	std::vector<int>range_elite;
	std::vector<monster_card>deck;
};
class creature_base
{

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
	void map_set();
	//////////
	void play_game();
	//////////
	void temp_function();
private:
	std::string character_txt;
	std::string monster_txt;
	character_data character_file;
};
//建構角色與怪獸的檔案class出來