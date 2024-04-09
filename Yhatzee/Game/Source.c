/// File Name: Source
/// File Author: Brooke Cronin
/// Course Code: CSCN71030 Group 4
/// Description: 
#include "GameLogic.h"
#include "Die.h"
#include "Player.h"
#include "UI.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {

        printf("%d", argc);

        printf("%s", argv[1]);

        fprintf(stderr, "\n\nERROR: No players.\n\n");

        exit(1);

    }

    UI u;

    u.numOfPlayers = atoi(argv[1]);
    
    char name[100];


    for (int i = 0; i < u.numOfPlayers; i++) {

       printf("Enter player name: ");

       fgets(name, 100, stdin);

       u.p[i] = CreateNewPlayer(name);

    }
    
    printMainMenu(u);
    
    menuChoice(u);
 
    return 0;
}
