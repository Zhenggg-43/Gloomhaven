#pragma once
#include"Map.h"
#include"Monster.h"
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include <algorithm>
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
	std::vector<character_card> operator[](std::string temp)
	{
		for (int i=0;i<character_amount;i++)
		{
			if (name[i]==temp)
			{
				return deck[i];
			}
		}
	}
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
	int shield = 0;
	std::vector<int> hand;//現在手牌
	std::vector<int> deadwood;//棄牌堆
	int action_card[2] = {-1,-1};//如果第1張是-1代表長休不考慮第2張
};
class All_hero
{
public:
	hero operator[](char temp)
	{
		for (int i=0;i<hero_amount;i++)
		{
			if (hero_status[i].icon==temp)
			{
				return hero_status[i];
			}
		}
	}
	int hero_amount = 0;
	std::vector<hero> hero_status;//角色狀態
};
//////////////////////////////////////////////////////////
class Round
{
public:
	int round_temp = 1;
	std::vector<char> canmove_icon;
	std::vector<char> action_creature_icon;
	std::vector<int> agility;
};



class gamemanger
{
public:
	bool gameloop();
	bool whether_play();
	//////////初始化
	void loadgame();
	void set_debugmode();
	void load_file();
	void load_character();
	void load_monster();
	//////////設定遊戲資料
	void menu();
	void character_amount();
	void characterANDskill();
	void load_map();
	void set_door_amount();
	//////////遊戲流程
	void play_game();
	void set_startpos();//設定玩家怪物進入地圖
	void print_round();
	void hero_turn();//玩家選擇卡牌
	void monster_turn();//怪物抽取卡牌
	void set_order();//依照敏捷設定順序
	void print_drawing();//輸出行動順序

	void round_action();//依照行動順序行動
	void hero_action(char&);//玩家移動
	void hero_action__deal(int,int,int&,bool&,char&);
	void print_check();
	int find_secagility(char);
	void monster_action(const char&);//敵人移動
	void deal_nextround();//每次行動玩需變動的事項例如判斷死亡之類的

	bool gameover();//遊戲是否結束

	void hero_takedamage(char,char,int);//給予英雄傷害
	void monster_takedamage(char,char, int);//給予怪物傷害
	void remove_dead_hero(char);//死亡英雄移除
	void remove_action_icon(char);//死亡生物從行動列中移除

	void open_door();//判斷是否開門
	//設定怪物
	void set_monster_active();
	

	//////////
	void temp_function(std::string,std::string,int);
private:
	void clearPlayingdata();

	bool Flag_DebugMode=0;
	std::string character_txt;
	std::string monster_txt;
	character_data character_file;
	monster_data monster_file;
	All_hero playingData_hero;
	All_monster PlayingData_monster;
	map_data PlayingData_map;
	Round round;

	int active_monster_amount = 0;
	std::vector<char>active_monster;
};
/*
角色選牌(玩家) 指令(check {character icon} ) / 怪物選牌(active/function操作)
排序
輪流動作 / check(角色動作時)
判斷 角色 怪物,門
遊戲是否結束
*/