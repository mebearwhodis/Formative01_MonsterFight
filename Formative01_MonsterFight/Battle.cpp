#include <iostream>

#include "Action.h"
#include "Monster.h"
#include "Utils.h"



//Allows the player to pick the 2 fighters
Monster PickFighter(Monster monster1, Monster monster2, Monster monster3, const std::string& sentence)
{
	system("cls");
	std::cout << std::endl << "Here are the available fighters:" << std::endl << std::endl;
	std::cout << "\t1. ";
	monster1.Display();
	std::cout << "\t2. ";
	monster2.Display();
	std::cout << "\t3. ";
	monster3.Display();
	std::cout << sentence << std::endl;

	bool restartLoop = true;
	do
	{
		restartLoop = true;
		char answer;

		std::cin >> answer;

		switch (tolower(answer)) {
		case '1':
			std::cout << "Please give them a name:" << std::endl;
			std::cin >> monster1.Name;
			return monster1;
		case '2':
			std::cout << "Please give them a name:" << std::endl;
			std::cin >> monster2.Name;
			return monster2;
		case '3':
			std::cout << "Please give them a name:" << std::endl;
			std::cin >> monster3.Name;
			return monster3;
		default:
			std::cout << std::endl << "Please enter a valid answer: 1, 2 or 3" << std::endl << std::endl;
			restartLoop = false;
		}
	} while (!restartLoop);

	return monster1;
}

//Checks if one of the monsters is dead
bool IsOneDead(Monster& monster1, Monster& monster2) {
	if (monster1.BattleHp <= 0)
	{
		monster1.BattleHp = 0;
		DisplayHUD(monster1, monster2);
		std::cout << monster1.ToString() << " is dead. Long live our champion, " << monster2.ToString() << "!" << std::endl;
		return true;
	}
	if (monster2.BattleHp <= 0)
	{
		monster2.BattleHp = 0;
		DisplayHUD(monster1, monster2);
		std::cout << monster2.ToString() << " is dead. Long live our champion, " << monster1.ToString() << "!" << std::endl;
		return true;
	}
	return false;
}

//Use speed to determine turn initiative with weighted rand. Returns true if monster1 attacks first
bool DetermineInitiative(const Monster& monster1, const Monster& monster2)
{
	return (rand() % (monster1.Spd + monster2.Spd) <= monster1.Spd);
}

//Applies stats buff
void BuffStats(Monster& monster, const bool buffState, const int amount)
{
	monster.IsBuffed = buffState;
	monster.Atk += amount;
	monster.Def += amount;
	monster.SpAtk += amount;
	monster.Spd += amount;
	monster.Spd += amount;
}

//The turn in itself, contains the other functions
void Showdown(Monster& monster1, Monster& monster2)
{
	turnNb++;

	//If one of the monster had a buff, remove it
	if (monster1.IsBuffed == true && monster1.BuffTurn + 2 == turnNb)
	{
		BuffStats(monster1, false, -5);
		std::cout << monster1.Name << " is no longer buffed." << std::endl;
	}
	if (monster2.IsBuffed == true && monster2.BuffTurn + 2 == turnNb)
	{
		BuffStats(monster2, false, -5);
		std::cout << monster2.Name << " is no longer buffed." << std::endl;
	}

	//If one of the monster had a shield that did not get used, remove it
	if (monster1.IsProtected == true && monster1.ProtectTurn + 2 == turnNb)
	{
		monster1.IsProtected = false;
		std::cout << monster1.Name << " is no longer protected by a shield." << std::endl;
	}
	if (monster2.IsProtected == true && monster2.ProtectTurn + 2 == turnNb)
	{
		monster2.IsProtected = false;
		std::cout << monster2.Name << " is no longer protected by a shield." << std::endl;
	}

	//If monster1 has the initiative
	if (DetermineInitiative(monster1, monster2))
	{
		std::cout << monster1.Name << " has the initiative!" << std::endl << std::endl;
		Action playerAction = Attack;
		if (!isAutoBattleOn) { playerAction = AskForAction(); }
		DoAction(monster1, monster2, true, playerAction);
		DoAction(monster2, monster1, false, playerAction);
	}

	//If monster2 has the initiative
	else
	{
		std::cout << monster2.Name << " has the initiative!" << std::endl << std::endl;
		Action playerAction = Attack;
		if (!isAutoBattleOn) { playerAction = AskForAction(); }
		DoAction(monster2, monster1, false, playerAction);
		DoAction(monster1, monster2, true, playerAction);
	}
}
