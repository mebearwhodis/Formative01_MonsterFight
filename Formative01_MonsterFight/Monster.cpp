#include "Monster.h"

#include <iostream>


class Monster;

Monster::Monster(const std::string& name, const enum Race race, const int baseHp, const int atk, const int def, const int spatk, const int spdef, const int spd)
{
	Name = name;
	Race = race;
	BaseHp = baseHp;
	BattleHp = baseHp;
	Atk = atk;
	Def = def;
	SpAtk = spatk;
	SpDef = spdef;
	Spd = spd;
	IsProtected = false;
	ProtectTurn = 0;
	IsBuffed = false;
	BuffTurn = 0;
}

std::string Monster::ToString() const
{
	std::string tempRace;
	{
		switch (Monster::Race)
		{
		case Orc:
			tempRace = "Orc";
			break;
		case Goblin:
			tempRace = "Goblin";
			break;
		case Troll:
			tempRace = "Troll";
			break;
		default:
			return "Not a valid race";
		}
	}
	return Monster::Name + " the " + tempRace;
}

void Monster::Display() const
{
	std::cout << this->ToString() << " has: " << BaseHp << " HP, " << Atk << " ATK, " << Def << " DEF, " << SpAtk << " SPATK, " << SpDef << " SPDEF and " << Spd << " SPD." << std::endl << std::endl;
}