#pragma once
#include "Monster.h"

enum Action
{
	Attack,
	Protect,
	Heal,
	Getbuff
};


void DealAttack(const Monster& attacker, Monster& defender);
void UseProtect(Monster& monster);
void CastHeal(Monster& monster);
void GetBuff(Monster& monster);

Action PickRandomAction();
Action AskForAction();

void DoAction(Monster& monster1, Monster& monster2, bool playerChoice, Action playerAction);
