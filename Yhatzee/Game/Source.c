/// File Name: Source
/// File Author: Brooke Cronin
/// Course Code: CSCN71030 Group 4
/// Description: 
#include "GameLogic.h"
#include "Die.h"
#include "Player.h"
#include "UI.h"
#include <time.h>

int main(int argc, char* argv[]) {
    srand(time(NULL));

    if (argc != 2) {

        printf("%d", argc);

        printf("%s", argv[1]);

        fprintf(stderr, "\n\nERROR: No players.\n\n");

        exit(1);

    }

    GAME g = initializeGame();

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
