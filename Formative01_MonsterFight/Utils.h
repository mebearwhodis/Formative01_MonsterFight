#pragma once

extern int turnNb;
bool isAutoBattleOn = true;

void ResetGame();
void DisplayHUD(const Monster& monster1, const Monster& monster2);

bool YesNoQuestion(const std::string& question);