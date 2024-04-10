#include "FileIO.h"
#include <stdio.h>

int saveGame(char* filename, PLAYER p)
{
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: file failed to open!");
        return 1;
    }

    fprintf(fp, "%s\n", p.name);
    fprintf(fp, "%d\n", p.currentGameNumber);
    //DO the current score
    for (int i = 0; i < NUMBER_OF_ITEMS_TO_SCORE_FOR; i++) {
        for (int j = 0; j < MAX_NUMBER_OF_GAMES; j++) {
            fprintf(fp, "%d\n", p.currentScore[i][j]);
        }
    }
    //do the possible scores
    for (int i = 0; i < NUMBER_OF_ITEMS_TO_SCORE_FOR; i++) {
        for (int j = 0; j < MAX_NUMBER_OF_GAMES; j++) {
            fprintf(fp, "%d\n", p.canScore[i][j]);
        }
    }

    fclose(fp);

    return 0;
}

bool loadGame(char* filename, PPLAYER p) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: file failed to open!");
        return 1;
    }

    char buffer[MAX_NAME_LENGTH];

    fgets(buffer, MAX_NAME_LENGTH, fp);
    strncpy(p->name, buffer, MAX_NAME_LENGTH);

    fgets(buffer, MAX_NAME_LENGTH, fp);
    int holder = atoi(buffer);
    p->currentGameNumber = holder;

    for (int i = 0; i < NUMBER_OF_ITEMS_TO_SCORE_FOR; i++) {
        for (int j = 0; j < MAX_NUMBER_OF_GAMES; j++) {
            fgets(buffer, MAX_NAME_LENGTH, fp);
            holder = atoi(buffer);
            p->currentScore[i][j] = holder;
        }
    }

    for (int i = 0; i < NUMBER_OF_ITEMS_TO_SCORE_FOR; i++) {
        for (int j = 0; j < MAX_NUMBER_OF_GAMES; j++) {
            fgets(buffer, MAX_NAME_LENGTH, fp);
            holder = atoi(buffer);
            p->canScore[i][j] = holder;
        }
    }

    bool result = antiCheat(*p);
    fclose(fp);

    return result;  

}

bool antiCheat(PLAYER p)
{
    if (GetCurrentGameNumber(p) > 10 || GetCurrentGameNumber(p) < 1) {
        return false;
    }
    for (int j = 0; j < MAX_NUMBER_OF_GAMES; j++) {
        //if outside of the bounds                                 OR        IN bounds, not 0, and marked as scorable (could overwrite the score)
        if ((p.currentScore[0][j] > 5 || p.currentScore[0][j] < 0) || (p.currentScore[0][j] != 0 && p.canScore[0][j] == -1)) {
            return false;//Ones
        }//Twos  v
        else if ((p.currentScore[1][j] > 10 || p.currentScore[1][j] < 0) || (p.currentScore[1][j] != 0 && p.canScore[1][j] == -1)) {
            return false;
        }//Threes  v
        else if ((p.currentScore[2][j] > 15 || p.currentScore[2][j] < 0) || (p.currentScore[2][j] != 0 && p.canScore[2][j] == -1)) {
            return false;
        }//Fours  v
        else if ((p.currentScore[3][j] > 20 || p.currentScore[3][j] < 0) || (p.currentScore[3][j] != 0 && p.canScore[3][j] == -1)) {
            return false;
        }//Fives  v
        else if ((p.currentScore[4][j] > 25 || p.currentScore[4][j] < 0) || (p.currentScore[4][j] != 0 && p.canScore[4][j] == -1)) {
            return false;
        }//Sixes  v
        else if ((p.currentScore[5][j] > 30 || p.currentScore[5][j] < 0) || (p.currentScore[5][j] != 0 && p.canScore[5][j] == -1)) {
            return false;
        }//3 of a kind  v
        else if ((p.currentScore[6][j] > 30 || p.currentScore[6][j] < 0) || (p.currentScore[6][j] != 0 && p.canScore[6][j] == -1)) {
            return false;
        }//4 of a kind  v
        else if ((p.currentScore[7][j] > 30 || p.currentScore[7][j] < 0) || (p.currentScore[7][j] != 0 && p.canScore[7][j] == -1)) {
            return false;
        }//Full House  v
        else if ((p.currentScore[8][j] > 28 || p.currentScore[8][j] < 0) || (p.currentScore[8][j] != 0 && p.canScore[8][j] == -1)) {
            return false;
        }//Small Straight  v
        else if ((p.currentScore[9][j] > 30 || p.currentScore[9][j] < 0) || (p.currentScore[9][j] != 0 && p.canScore[9][j] == -1)) {
            return false;
        }//Large Straight  v
        else if ((p.currentScore[10][j] > 40 || p.currentScore[10][j] < 0) || (p.currentScore[10][j] != 0 && p.canScore[10][j] == -1)) {
            return false;
        }//First Yahtzee  v
        else if ((p.currentScore[11][j] > 50 || p.currentScore[11][j] < 0) || (p.currentScore[11][j] != 0 && p.canScore[11][j] == -1)) {
            return false;
        }//Chance  v
        else if ((p.currentScore[12][j] > 30 || p.currentScore[12][j] < 0) || (p.currentScore[12][j] != 0 && p.canScore[12][j] == -1)) {
            return false;
        }//Subsequent Yahtzees  v       //Theoretically infinite, but needs to be divisible by 100
        else if ((p.currentScore[13][j] % 100 != 0 || p.currentScore[13][j] < 0) || (p.currentScore[13][j] != 0 && p.canScore[13][j] == -1)) {
            return false;
        }//Upper Subtotal  v
        else if ((p.currentScore[14][j] > 105 || p.currentScore[14][j] < 0) || (p.currentScore[14][j] != 0 && p.canScore[14][j] == -1)) {
            return false;
        }//Upper Bonus  v
        else if ((p.currentScore[15][j] > 35 || p.currentScore[15][j] < 0) || (p.currentScore[15][j] != 0 && p.canScore[15][j] == -1)) {
            return false;
        }//Upper Total  v
        else if ((p.currentScore[16][j] > 140 || p.currentScore[16][j] < 0) || (p.currentScore[16][j] != 0 && p.canScore[16][j] == -1)) {
            return false;
        }//Lower Total  v               total non-yahtzee bonus'd possible score is 238, yahtzeeBonus is divisible by 100 
        else if (((p.currentScore[17][j] - 238) % 100 == 0 || p.currentScore[17][j] < 0) || (p.currentScore[17][j] != 0 && p.canScore[17][j] == -1)) {
            return false;
        }//GRAND TOTAL  v             Similar to lower total (since it Includes lower total)
        else if (((p.currentScore[18][j] - 378) % 100 == 0 || p.currentScore[2][j] < 0) || (p.currentScore[2][j] != 0 && p.canScore[2][j] == -1)) {
            return false;
        }
    }
    return true;
}