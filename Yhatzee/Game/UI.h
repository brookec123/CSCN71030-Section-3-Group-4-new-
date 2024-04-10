#pragma once
// UI.h file containing all of the UI.c functions
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <stdlib.h>

#include "Die.h"
#include "FileIO.h"
#include "GameManager.h"
#include "GameLogic.h"
#include "Player.h"

void playGame(GAME_MANAGER g);

void displayFinalScores(GAME_MANAGER g);

void playerTurn(GAME_MANAGER* g);

void printMainMenu(GAME_MANAGER g);

void menuChoice(GAME_MANAGER g);

void printScorecard(GAME_MANAGER g, int** scoreArray);

void printRules();

void diceAnimation();
