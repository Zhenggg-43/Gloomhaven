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
	int X_border, Y_border;//���
	std::string *body;//�a�ϥ���
	bool **sight;//�a�ϵ���
	int  position_start[4][2];//�i��_�l��m  [y][x]
	std::vector<S_coordinate>monster_coordinate;//�Ǫ��y��
	std::vector<S_coordinate>character_coordinate;//����y��
};