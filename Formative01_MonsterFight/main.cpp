// MonsterFightSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <ctime>
#include <iostream>

#include "Battle.h"
#include "Monster.h"
#include "Utils.h"

int main()
{
	do {
		ResetGame();
		srand(time(nullptr));

		//Constructs monster presets
		Monster orc("Alfred", Orc, 39, 52, 43, 60, 50, 65);
		Monster goblin("Bonnie", Goblin, 44, 48, 65, 50, 64, 43);
		Monster troll("Charles", Troll, 45, 49, 49, 65, 65, 45);

		isAutoBattleOn = YesNoQuestion("Do you want to turn the auto battle on?");

		Monster firstMonster = PickFighter(orc, goblin, troll, "Pick the first monster to fight (this is the one you will control if you decided to turn off the Auto Battle)");
		Monster secondMonster = PickFighter(orc, goblin, troll, "Pick the second monster to fight");

		do
		{
			DisplayHUD(firstMonster, secondMonster);
			Showdown(firstMonster, secondMonster);
			system("pause");

		} while (!IsOneDead(firstMonster, secondMonster));

	} while (YesNoQuestion("Do you want to play again?"));
	exit(0);
}
