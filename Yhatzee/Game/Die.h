/// File Name: Die.h
/// File Author: Brooke Cronin
/// Course Code: CSCN71030 Group 4
/// Description: 
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define MIN_VALUE 1
#define MAX_VALUE 6

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Die
{
    int value;
} DIE, * PDIE;

DIE CreateDie();

int GetValue(DIE d);

void SetValue(PDIE d, int val);

void RollDie(PDIE d);

void RollArrayOfDice(PDIE d, int size);

int TotalAllDice(DIE* dice, int number_of_dice);

int compare(const void* a, const void* b);

void SortDiceSmallestToLargest(PDIE dice, int number_of_dice);

void DisplayArrayOfDice(PDIE d, int size);