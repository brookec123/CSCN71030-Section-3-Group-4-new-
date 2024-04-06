#pragma once

#include "GameLogic.h"

#include <stdio.h>

#include <stdlib.h>

typedef struct ui {

	char* userInput;

	int numOfPlayers;

}UI;

void printMainMenu(UI u);

void menuChoice(UI u);

void printSubMenu(UI u);

void printScorecard(UI u, int** scoreArray);

void printRules();

void diceAnimation();
