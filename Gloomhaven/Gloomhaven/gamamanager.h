#pragma once
#include<string>
#include<iostream>
class gamemanger
{
public:
	bool gameloop();
	bool whether_play();
	//////////
	void loadgame();
	void load_file();
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
};


class creature_base
{

};


class character_data
{

};

//建構角色與怪獸的檔案class出來