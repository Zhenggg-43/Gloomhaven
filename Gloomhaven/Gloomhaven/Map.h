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
	int X_border, Y_border;//邊界
	std::string *body;//地圖本體
	bool **sight;//地圖視野
	int  position_start[4][2];//可選起始位置  [y][x]
	std::vector<S_coordinate>monster_coordinate;//怪物座標
	std::vector<S_coordinate>character_coordinate;//角色座標
};