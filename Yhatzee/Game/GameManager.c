#include "GameManager.h"
GAME_MANAGER initializeGame() { // function that initializes the game values
    GAME_MANAGER g;
    srand(time(NULL));
    for (int i = 0; i < 5; i++) {

        g.dice[i] = CreateDie(); // die is created
    }
    g.currentPlayerIndex = 0;

    return g;
}

int convertAndValidateUserInputToScoreIndex(int input)
{ // function converting the user input to the score index 
    if (input >= 1 && input <= 14)
    {
        return input - 1;
    }
    return -1;
}

void goToNextPlayer(GAME_MANAGER g)
{ // function that goes to next player once turn is done 
    g.currentPlayerIndex = (g.currentPlayerIndex + 1) % g.numOfPlayers;
}