#include "Action.h"

#include <iostream>

#include "Battle.h"
#include "Utils.h"


//Attack: deals damage based on atk/matk stat from attacker, def/spdef from defender with a small chance to crit and a small chance to dodge
void DealAttack(const Monster& attacker, Monster& defender)
{
	std::cout << attacker.Name << " chose to attack." << std::endl;

	//Checks if the defender is protected
	if (defender.IsProtected == true)
	{
		defender.IsProtected = false;
		std::cout << defender.Name << " was protected. They did not take any damage this time, but their shield is now down." << std::endl << std::endl;
	}

	//The opponent has a 5% chance to dodge. 
	else if (rand() % 100 < 5)
	{
		std::cout << attacker.Name << " attacked " << defender.Name << ", but they managed to dodge." << std::endl << std::endl;
	}
	else
	{
		//The attack has a 5% chance to crit
		const bool isCrit = rand() % 100 < 5;

		//80% chance to deal a physical attack, 20% for a magic (slightly better) one
		if (rand() % 100 < 80)
		{
			//Physical attack
			const int damageDealt = (rand() % static_cast<int>(round(attacker.Atk * defender.Def / 400)) + attacker.Atk * defender.Def / 400) * (isCrit + 1);
			defender.BattleHp -= damageDealt;
			if (isCrit)
			{
				std::cout << "It's a critical strike! " << defender.Name << " lost " << damageDealt << " hitpoints." << std::endl << std::endl;
			}
			else
			{
				std::cout << defender.Name << " lost " << damageDealt << " hitpoints." << std::endl << std::endl;
			}
		}
		else
		{
			//Magical attack
			const int damageDealt = (rand() % static_cast<int>(round(attacker.SpAtk * defender.SpDef / 400)) + attacker.SpAtk * defender.SpDef / 400) * (isCrit + 1);
			defender.BattleHp -= damageDealt;
			if (isCrit)
			{
				std::cout << "It's a critical spell! " << defender.Name << " lost " << damageDealt << " hitpoints." << std::endl << std::endl;
			}
			else
			{
				std::cout << defender.Name << " lost " << damageDealt << " hitpoints." << std::endl << std::endl;
			}
		}
	}
}

//Protect: nullify next instance of damage taken (this turn if going first, next turn if going second) but not if in 2+ turns
void UseProtect(Monster& monster)
{
	std::cout << monster.Name << " chose to protect themselves." << std::endl;

	//Trying to stack protections ends up in losing a turn
	if (monster.IsProtected == true)
	{
		std::cout << monster.Name << " tried to shield themselves but already had a shield. They lost their turn." << std::endl << std::endl;
	}
	else
	{
		monster.ProtectTurn = turnNb;
		monster.IsProtected = true;
		std::cout << monster.Name << " gets a protective shield against one attack for one turn!" << std::endl << std::endl;
	}
}

//Heal: regain Hp based on Matk, chance to crit (heal double hp)
void CastHeal(Monster& monster)
{
	std::cout << monster.Name << " chose to heal themselves." << std::endl;

	const bool isCrit = rand() % 100 < 5;

	int healedAmount = rand() % (monster.SpAtk / 5) * (isCrit + 1);

	//Prevents healing over base HP
	if (monster.BattleHp + healedAmount > monster.BaseHp)
	{
		healedAmount = monster.BaseHp - monster.BattleHp;
		monster.BattleHp = monster.BaseHp;
	}
	else
	{
		monster.BattleHp += healedAmount;
	}
	if (isCrit)
	{
		std::cout << "It's a critical heal! " << monster.Name << " regained " << healedAmount << " hitpoints." << std::endl << std::endl;
	}
	else
	{
		std::cout << monster.Name << " regained " << healedAmount << " hitpoints." << std::endl << std::endl;
	}
}

//Get an all stats buff on next turn
void GetBuff(Monster& monster)
{
	std::cout << monster.Name << " chose to buff themselves." << std::endl;

	//Trying to stack buffs ends up in losing a turn
	if (monster.IsBuffed == true)
	{
		std::cout << monster.Name << " tried to get a buff but already had one. They lost their turn." << std::endl << std::endl;
	}
	else
	{
		monster.BuffTurn = turnNb;
		BuffStats(monster, true, 5);
		std::cout << monster.Name << " is buffed until the end of next turn!" << std::endl << std::endl;
	}
}

//If player chose Autobattle: weighted rand to determine action, might need fine-tuning
Action PickRandomAction()
{
	const int randomAction = rand() % 100;

	//Attack 51%, Protect 18%, Heal 18%, Getbuff 13%

	if (randomAction >= 0 && randomAction <= 50)
	{
		return Attack;
	}
	else if (randomAction >= 51 && randomAction <= 68)
	{
		return Protect;
	}
	else if (randomAction >= 69 && randomAction <= 86)
	{
		return Heal;
	}
	else
	{
		return Getbuff;
	}
}

//If player did not choose Autobattle: let them pick
Action AskForAction()
{
	std::cout << "What would you like to do?" << std::endl << "1. Attack\t\t2. Protect yourself for a turn\n3. Heal\t\t4. Get a one turn stats buff" << std::endl;

	bool restartLoop = true;
	do
	{
		restartLoop = true;

		char answer;
		std::cin >> answer;

		switch (tolower(answer)) {
		case '1':
			return Attack;
		case '2':
			return Protect;
		case '3':
			return Heal;
		case '4':
			return Getbuff;
		default:
			std::cout << std::endl << "Please enter a valid answer: 1, 2, 3 or 4" << std::endl << std::endl;
			restartLoop = false;
		}
	} while (!restartLoop);

	return Attack;
}

//One monster action
void DoAction(Monster& monster1, Monster& monster2, const bool playerChoice, const Action playerAction)
{
	Action chosenAction;
	if (isAutoBattleOn == true || playerChoice == false) {
		chosenAction = PickRandomAction();
	}
	else
	{
		chosenAction = playerAction;
	}

	switch (chosenAction)
	{
	case Attack:
		DealAttack(monster1, monster2);
		break;
	case Protect:
		UseProtect(monster1);
		break;
	case Heal:
		CastHeal(monster1);
		break;
	case Getbuff:
		GetBuff(monster1);
		break;
	default:
		break;
	}
}