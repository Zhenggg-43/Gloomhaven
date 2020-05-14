#pragma once
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
////////////////////////////////////////////////////////// monster
struct monster_cardskill
{
	int type = -1;
	int power = 0;
	int range = 0;
	std::string movement = "";
};

struct S_monster
{
	int hp;
	int power;
	int range;
};

class monster_card
{
public:
	int card_index = 0;
	int agility = 0;
	bool suffle_sign = 0;
	std::vector<monster_cardskill>skill;
};
class monster_data
{
public:
	int monster_amount = 0;
	std::vector<std::string>name;
	std::vector<S_monster>elite;
	std::vector<S_monster>normal;
	std::vector<std::vector<monster_card>>deck;
};
//////////////////////////////////////////////////////////
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
	monster_data monster_file;
};
//建構角色與怪獸的檔案class出來