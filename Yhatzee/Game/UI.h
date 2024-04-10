#pragma once
// UI.h file containing all of the UI.c functions
#include "GameLogic.h"
#include "Game.h"

#include <stdio.h>

#include <stdlib.h>
void playGame(GAME g);

void displayFinalScores(GAME g);

void playerTurn(GAME* g);

void printMainMenu(GAME* g);

void menuChoice(GAME* g);

void printScorecard(GAME g, int** scoreArray);

void printRules();

void diceAnimation();
