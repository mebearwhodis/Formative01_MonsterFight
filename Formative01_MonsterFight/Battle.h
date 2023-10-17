#pragma once
#include "Monster.h"

Monster PickFighter(Monster monster1, Monster monster2, Monster monster3, const std::string& sentence);

bool IsOneDead(Monster& monster1, Monster& monster2);

bool DetermineInitiative(const Monster& monster1, const Monster& monster2);

void BuffStats(Monster& monster, const bool buffState, const int amount);

void Showdown(Monster& monster1, Monster& monster2);
