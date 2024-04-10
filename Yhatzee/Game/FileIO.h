//Prototypes for save, load, and anti-cheat functions
#pragma once

#include <stdbool.h>
#include "Player.h"

int saveGame(char* filename, PLAYER p);

int loadGame(char* filename, PPLAYER p);

bool antiCheat(PLAYER p);