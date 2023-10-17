#pragma once
#include <string>

enum Race
{
	Orc,
	Goblin,
	Troll
};

class Monster
{
public:
	std::string Name;
	Race Race;
	int BaseHp;
	int BattleHp;
	int Atk;
	int Def;
	int SpAtk;
	int SpDef;
	int Spd;
	bool IsProtected;
	int ProtectTurn;
	bool IsBuffed;
	int BuffTurn;

	/*
	 *HP/Atk/Def/SpAtk/SpDef/Spd
	 *
	 * hp = max hitpoints
	 * atk = augments max physical damage
	 * def = reduces incoming physical damage
	 * spatk = augments max heal and magic damage
	 * spdef = reduces incoming magical damage
	 * spd = higher chance to attack first
	 */

	//Constructor
	Monster(const std::string& name, enum Race race, int baseHp, int atk, int def, int spatk, int spdef, int spd);

	//Function that returns "NAME the RACE"
	std::string ToString() const;

	//Displays name & stats
	void Display() const;

};