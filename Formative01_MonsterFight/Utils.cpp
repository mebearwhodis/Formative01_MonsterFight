#include <iostream>
#include <string>

#include "Battle.h"

int turnNb = 1;
extern bool isAutoBattleOn;

//Resets game variables
void ResetGame()
{
	turnNb = 1;
	system("cls");
}

//Function to Display HUD
void DisplayHUD(const Monster& monster1, const Monster& monster2)
{
	system("cls");
	std::cout << "\t\t\t" << "Turn: " << turnNb << std::endl << std::endl;
	std::cout << "\t" << monster1.Name << " " << monster1.BattleHp << "/" << monster1.BaseHp << "\tversus\t\t" << monster2.BattleHp << "/" << monster2.BaseHp << " " << monster2.Name << std::endl << std::endl;
}

//Asks a Yes/No question, returns true if yes, false if no
bool YesNoQuestion(const std::string& question)
{
	bool restartLoop = true;
	do
	{
		restartLoop = true;
		char answer;

		std::cout << std::endl << question << " Y/N" << std::endl;
		std::cin >> answer;

		switch (tolower(answer))
		{
		case 'y':
			return true;
		case 'n':
			return false;
		default:
			std::cout << std::endl << "Please enter a valid answer: Y/N" << std::endl << std::endl;
			restartLoop = false;
		}
	} while (!restartLoop);

	return false;
}