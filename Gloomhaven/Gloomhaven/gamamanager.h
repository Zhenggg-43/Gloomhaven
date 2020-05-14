#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
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


class creature_base
{

};


class character_data
{
	int character_amount = 0;
	std::vector<std::string> name;
	std::vector<int> hp;
	std::vector<int> hands_amount;
	std::vector<int> deck_amount;
	std::vector<character_deck> deck;
};
class monster_data
{

};

class character_deck
{
	int card_id;
	std::vector<card_effect>up_effect;
	std::vector<card_effect>down_effect;
};
class card_effect
{
	std::vector <int> card_type;
	std::vector <int> card_power;
};
//建構角色與怪獸的檔案class出來