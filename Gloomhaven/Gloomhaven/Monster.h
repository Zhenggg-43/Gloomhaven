#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>

//怪物基礎資料型別
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
//載入的遊戲資料
class monster_data
{
public:
	int monster_amount = 0;
	std::vector<std::string>name;
	std::vector<S_monster>elite;
	std::vector<S_monster>normal;
	typedef std::vector < monster_card> Deck;
	std::vector<Deck>All_deck;

};//遊戲怪物資料
//遊戲中資料
class monster
{
public:
	bool ifactive;
	std::string name;
	char icon;
	int hp_max, power, range;
	int hp;
	typedef std::vector < monster_card> Deck;
	Deck cards;//怪物卡牌
};
class All_monster
{
public:
	void printAllmonster();

	int monster_amount = 0;
	std::vector<monster>monster_status;//怪物狀態
};