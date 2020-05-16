#include"Monster.h"
enum Action
{
	_t_, Move, Attack, Heal, Shield, Range
};

void All_monster::printAllmonster()
{
	for (auto monster : this->monster_status)
	{
		std::cout << monster.name << ' ' << monster.icon << ' ' << monster.hp << ' ' << monster.power << ' ' << monster.range << std::endl;
		for (auto card : monster.cards)
		{
			std::cout << card.card_index << ' ' << card.agility << ' ';
			for (auto skill : card.skill)
			{
				if (skill.type == Action::Attack)
				{
					std::cout << "attack " << skill.power << ' ' << skill.range << ' ';
				}
				else if (skill.type == Action::Heal)
				{
					std::cout << "heal " << skill.power << ' ';
				}
				else if (skill.type == Action::Move)
				{
					std::cout << "move " << skill.movement << ' ';
				}
				else if (skill.type == Action::Shield)
				{
					std::cout << "shield " << skill.power << ' ';
				}
			}
			std::cout << card.suffle_sign << std::endl;
		}
		std::cout << std::endl;
	}
}