#pragma once

#include "GameLogic.h"

#include <stdio.h>

#include <stdlib.h>

typedef struct ui {

	char* userInput;

	int numOfPlayers

}UI;

void printMainMenu(UI interface);

void menuChoice(UI interface);

void printSubMenu(UI interface);

void printScorecard(UI interface);

void printRules();
