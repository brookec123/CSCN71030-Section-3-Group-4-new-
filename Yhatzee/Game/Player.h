/// File Name: Player.h
/// File Author: Brooke Cronin
/// Course Code: CSCN71030 Group 4
/// Description: 
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_LENGTH 51 // including '/0' character at end
#define MAX_NUMBER_OF_GAMES 10
#define NUMBER_OF_ITEMS_TO_SCORE_FOR 19 // includes totals, bonuses, and individual parts of the sections

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Player
{
	char* name;
	int currentGameNumber;
	int** currentScore;
	int** canScore;
	bool hasWonCurrentGame;
	// include file name where player's info is stored????

} PLAYER, * PPLAYER;

PLAYER CreateNewPlayer(char* n);

int GetCurrentGameNumber(PLAYER p);

void SetCurrentGameNumber(PPLAYER p, int gameNumber);

bool IsGameDoneForPlayer(PLAYER p);

void DestroyPlayer(PPLAYER p);
