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
	std::vector<int> hand;//�{�b��P
	std::vector<int> deadwood;//��P��
	int action_card[2] = {-1,-1};//�p�G��1�i�O-1�N����𤣦Ҽ{��2�i
};
class All_hero
{
public:
	int hero_amount = 0;
	std::vector<hero> hero_status;//���⪬�A
};
//////////////////////////////////////////////////////////
class Round
{
public:
	int round_temp = 1;
	std::vector<char> canmove_icon;
	std::vector<char> action_icon;
	std::vector<int> agility;
};



class gamemanger
{
public:
	bool gameloop();
	bool whether_play();
	//////////��l��
	void loadgame();
	void set_debugmode();
	void load_file();
	void load_character();
	void load_monster();
	//////////�]�w�C�����
	void menu();
	void character_amount();
	void characterANDskill();
	void load_map();
	//////////�C���y�{
	void play_game();
	void set_startpos();//�]�w���a�Ǫ��i�J�a��
	void print_round();
	void hero_turn();//���a��ܥd�P
	void monster_turn();//�Ǫ�����d�P
	void set_order();//�̷ӱӱ��]�w����
	void hero_action();//���a����
	void monster_action();//�ĤH����
	void gameover();//�C���O�_����

	void takedamage();//�����ˮ`
	bool visible();//�T�{���L�ؼе���
	void check_dead_creature();//�M�䦺�`�ؼШò���

	void open_door();//�P�_�O�_�}��
	void re_sight();//�}���᭫�s�]�w����
	//�]�w�Ǫ�
	void set_monster_active();
	

	//////////
	void temp_function();
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
�����P(���a) ���O(check {character icon} ) / �Ǫ���P(active/function�ާ@)
�Ƨ�
���y�ʧ@ / check(����ʧ@��)
�P�_ ���� �Ǫ�,��
�C���O�_����
*/