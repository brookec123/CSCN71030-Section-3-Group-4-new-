//Prototypes for save, load, and anti-cheat functions
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include "Player.h"

int saveGame(char* filename, PLAYER p);

bool loadGame(char* filename, PPLAYER p);

bool antiCheat(PLAYER p);