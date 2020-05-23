#include"Monster.h"
using namespace std;
#define attack_power attack.attpower
#define attack_range attack.range
enum Action
{
	_t_, Move, Attack, Heal, Shield, Range
};
monster& All_monster::operator[](char icon)
{
	for (int i=0;i<monster_status.size();i++)
	{
		if (monster_status[i].icon == icon)
		{
			return monster_status[i];
		}
	}
	cout << "monster icon ERROR in operater[]\n";
	return monster_status[0];
}
void All_monster::printAllmonster()
{
	for (auto monster : this->monster_status)
	{
		std::cout <<monster.index<< monster.name << ' ' << monster.icon << ' ' << monster.hp << ' ' << monster.power << ' ' << monster.range << std::endl;
		for (auto card : monster.cards)
		{
			std::cout << card.card_index << ' ' << card.agility << ' ';
			for (auto skill : card.skill)
			{
				if (skill.type == Action::Attack)
				{
					std::cout << "attack " << skill.attack_power << ' ';
					if (skill.attack.ifrange)
					{
						std::cout << "range " << skill.attack_range << ' ';
					}
				}
				else if (skill.type == Action::Heal)
				{
					std::cout << "heal " << skill.skillpower << ' ';
				}
				else if (skill.type == Action::Move)
				{
					std::cout << "move " << skill.movement << ' ';
				}
				else if (skill.type == Action::Shield)
				{
					std::cout << "shield " << skill.skillpower << ' ';
				}
			}
			std::cout << card.suffle_sign << std::endl;
		}
		std::cout << std::endl;
	}
}
void All_monster::printmonstercard(char icon, int card_Vecindex)
{
	for (auto monster : monster_status)
	{
		if (monster.icon == icon)
		{
			std::cout << monster.name << ' ';//名稱

			auto card = monster.cards[card_Vecindex];//卡牌//////////////////
			cout << card.agility << ' ';//敏捷值
			for (auto skill : card.skill)//技能
			{
				if (skill.type == Action::Attack)
				{
					std::cout << "attack " << skill.attack_power << ' ';
					if (skill.attack.ifrange)
					{
						std::cout << "range " << skill.attack_range << ' ';
					}
				}
				else if (skill.type == Action::Heal)
				{
					std::cout << "heal " << skill.skillpower << ' ';
				}
				else if (skill.type == Action::Move)
				{
					std::cout << "move " << skill.movement << ' ';
				}
				else if (skill.type == Action::Shield)
				{
					std::cout << "shield " << skill.skillpower << ' ';
				}
			}
			cout << endl;
			break;
		}
	}
}