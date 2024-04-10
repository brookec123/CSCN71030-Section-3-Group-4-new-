/// File Name: Source
/// File Author: Brooke Cronin
/// Course Code: CSCN71030 Group 4
/// Description: 
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>

#include "Die.h"
#include "FileIO.h"
#include "GameManager.h"
#include "GameLogic.h"
#include "Player.h"
#include "UI.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {

        printf("%d", argc);

        printf("%s", argv[1]);

        fprintf(stderr, "\n\nERROR: No players.\n\n");

        exit(1);

    }

    GAME_MANAGER g = initializeGame();

    g.numOfPlayers = atoi(argv[1]);

    char name[100];


    for (int i = 0; i < g.numOfPlayers; i++) {

        printf("Enter player name: ");

        fgets(name, 100, stdin);
        name[strcspn(name, "\n")] = '\0';

        g.players[i] = CreateNewPlayer(name);

    }

    printMainMenu(&g);

    menuChoice(&g);

    return 0;
}
