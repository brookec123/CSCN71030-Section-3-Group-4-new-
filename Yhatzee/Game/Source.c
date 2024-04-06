/// File Name: Source
/// File Author: Brooke Cronin
/// Course Code: CSCN71030 Group 4
/// Description: 
#include "GameLogic.h"
#include "UI.h"

int main(int argc, char* argv) {

    if (argc != 2) {

        fprintf(stderr, "\n\nERROR: No players.\n\n");

        exit(1);

    }

    UI u;

    u.numOfPlayers = atoi(argv[1]);

    printMainMenu(u);

    menuChoice(u);

    return 0;
}
