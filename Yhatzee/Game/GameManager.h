#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>

#include "Die.h"
#include "FileIO.h"
#include "GameLogic.h"
#include "Player.h"
#include "UI.h"

typedef struct gameManager { // struct containing GAME_MANAGER values
    int currentPlayerIndex;

    int numOfPlayers;

    PLAYER players[10];

    DIE dice[5];

} GAME_MANAGER, * PGAME_MANAGER;

GAME_MANAGER initializeGame();

int convertAndValidateUserInputToScoreIndex(int input);

void goToNextPlayer(GAME_MANAGER g);