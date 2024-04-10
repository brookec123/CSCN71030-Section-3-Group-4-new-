/// File Name: GameLogic
/// File Author: Brooke Cronin
/// Course Code: CSCN71030 Group 4
/// Description: 
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define NUMBER_OF_DICE 5

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "Die.h"
#include "Player.h"
#include "Game.h"

int calculateUpper(DIE* dice, int valueToCheckFor);

int calculateThreeOfAKind(DIE* dice);

int calculateFourOfAKind(DIE* dice);

int calculateFullHouse(DIE* dice);

int calculateSmallStraight(DIE* dice);

int calculateLargeStraight(DIE* dice);

int calculateFirstYahtzee(DIE* dice);

int calculateChance(DIE* dice);

void calculateCanScore(DIE* dice, PPLAYER p);

void updateCurrentScore(PPLAYER p, int choice);

void calculateUpperSubTotal(PPLAYER p);

void calculateUpperBonus(PPLAYER p);

void calculateUpperTotal(PPLAYER p);

void calculateLowerTotal(PPLAYER p);

void calculateGrandTotal(PPLAYER p);

void calculateFinalTotalsAndBonuses(PPLAYER p);

bool isGameDone(GAME g);

void whoWon(GAME g);
