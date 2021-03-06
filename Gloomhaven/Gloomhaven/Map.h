#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
struct S_coordinate
{
	int x = 0, y = 0;
};
class map_data
{
public:
	void Set_Characterpos(int);
	void Set_Monsterpos(std::string);
	void Set_Sight(int,int);
	void Print_Allmap();
	void Print_Sightedmap();
	bool character_Move(int,char, std::string);//for character
	bool creature_Move(int,char, std::string);//for monster
	int countRange(int, int);
	bool visible(int, int);

	void character_killed(int);
	void monster_killed(int);

	int X_border, Y_border;//邊界
	std::string *body;//地圖本體
	bool **sight;//地圖視野
	int  position_start[4][2];//可選起始位置  [y][x]
	int door_amount = 0;
	std::vector<S_coordinate>door_coordinate;//
	std::vector<S_coordinate>monster_coordinate;//怪物座標
	std::vector<S_coordinate>character_coordinate;//角色座標
};