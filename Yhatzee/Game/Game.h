#pragma once

#include "Die.h"
#include "FileIO.h"

typedef struct game { // struct containing GAME values
	int currentPlayerIndex;

	int numOfPlayers;

	PLAYER players[10];

	DIE dice[5];

} GAME, * PGAME;

GAME initializeGame();

int convertAndValidateUserInputToScoreIndex(int input);

void goToNextPlayer(GAME g);

