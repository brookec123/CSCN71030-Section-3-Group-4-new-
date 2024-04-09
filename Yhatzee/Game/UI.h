#pragma once

#include "GameLogic.h"

#include <stdio.h>

#include <stdlib.h>

typedef struct ui {

	int numOfPlayers;

	PLAYER p[10];

	DIE d[5];

}UI;

void printMainMenu(UI u);

void menuChoice(UI u);

void printSubMenu(UI u);

void printScorecard(UI u, int** scoreArray);

void printRules();

void diceAnimation();
