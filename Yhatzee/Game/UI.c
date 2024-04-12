#include "UI.h"

void playGame(GAME g)
{ // functions to check if game is done, if not the game starts 
	while (!isGameDone(g)) {
		printf("\n\n%s's turn.\n", g.players[g.currentPlayerIndex].name);
		// Player's turn
		playerTurn(&g);
		goToNextPlayer(&g);
	}

	// Display final scores and winner
	displayFinalScores(g);
}

void displayFinalScores(GAME g)
{ // function that displays final scores 
	whoWon(g);
	printf("Winner(s): ");
	for (int i = 0; i < g.numOfPlayers; i++)
	{
		if (g.players[i].hasWonCurrentGame)
		{
			printf("%s ", g.players[i].name);
		}
	}
	printf("\n");

	for (int i = 0; i < g.numOfPlayers; i++)
	{
		calculateFinalTotalsAndBonuses(&g.players[i]);
		printf("\n\n%s's Final Score card:", g.players[i].name);
		printScorecard(g, g.players[i].currentScore);
	}
}

void playerTurn(GAME* g) { // function that plays the game when it is the specified player's turn

	int numberOfRolls = 1;

	RollArrayOfDice(g->dice, 5);

	DisplayArrayOfDice(g->dice, 5);

	calculateCanScore(g->dice, &g->players[g->currentPlayerIndex]);

	printScorecard(*g, g->players[g->currentPlayerIndex].canScore); // rolling and printing the die & scorecard

	char doneTurn = ' ';
	printf("Do you want to finish your turn (y/n)?");
	scanf_s(" %c", &doneTurn, 1);

	while (numberOfRolls <= 3 && (doneTurn == 'n'))
	{
		for (int i = 0; i < NUMBER_OF_DICE; i++)
		{
			char rerollCurrentDie = ' ';
			printf("Do you want to reroll die # %d?", i + 1);
			scanf_s(" %c", &rerollCurrentDie, 1);
			if (rerollCurrentDie == 'y')
			{
				RollDie(&g->dice[i]);
			}
		}
		DisplayArrayOfDice(g->dice, 5);

		calculateCanScore(g->dice, &g->players[g->currentPlayerIndex]);

		printScorecard(*g, g->players[g->currentPlayerIndex].canScore);

		printf("Do you want to finish your turn (y/n)?");
		scanf_s(" %c", &doneTurn, 1);

		numberOfRolls++;
	} // adding to the number of rolls until max

	int scoreChoice = -1;
	printf("What do you want to score for?");
	scanf_s("%d", &scoreChoice);

	if (g->players[g->currentPlayerIndex].canScore[g->players->currentGameNumber - 1][scoreChoice - 1] != -1 && convertAndValidateUserInputToScoreIndex(scoreChoice) != -1)
	{
		updateCurrentScore(&g->players[g->currentPlayerIndex], convertAndValidateUserInputToScoreIndex(scoreChoice));
		saveGame(g->players[g->currentPlayerIndex].saveFileName, g->players[g->currentPlayerIndex]);
	}
}


void printMainMenu(GAME* g) { // main menu print 


	printf("\n__   __        _      _                     \n");
	printf("\\ \\ / /       | |    | |                    \n");
	printf(" \\ V /   __ _ | |__  | |_  ____  ___   ___  \n");
	printf("  \\ /   / _` || '_ \\ | __||_  / / _ \\ / _ \\ \n");
	printf("  | |  | (_| || | | || |_  / / |  __/|  __/ \n");
	printf("  \\_/   \\__,_||_| |_| \\__|/___| \\___| \\___| \n");

	printf("\nNumber of players: %d", g->numOfPlayers);

	printf("\n\nWelcome to Yhatzee! This is a console based version of the beloved classic dice game... known as Yhatzee.\n");
	printf("\n=================================================================================================================\n");

	printf("Menu:\n\n");
	printf("1. Play Game.\n");
	printf("2. Load Saved Game.\n");
	printf("3. View Rules.\n");
	printf("4. Exit Game.\n");
	printf("\nChoice: ");

}

void menuChoice(GAME* g) { // option to select from the main menu 

	int choice = 0;

	scanf_s("%d", &choice);

	switch (choice)
	{

	case 1:
		initializeGame();
		playGame(*g);
		printMainMenu(g);
		menuChoice(g);
		break;

	case 2:

		loadGame(g->players[g->currentPlayerIndex].saveFileName, &g->players[g->currentPlayerIndex]);

		printMainMenu(g);

		menuChoice(g);

		break;

	case 3:

		printRules();

		printMainMenu(g);

		menuChoice(g);

		break;

	case 4:

		saveGame(g->players[g->currentPlayerIndex].saveFileName, g->players[g->currentPlayerIndex]);
		printf("\n\nGame successfully saved!\n");
		printf("\nThanks for playing!\n");

		break;


	default:

		fprintf(stderr, "\nERROR: Invalid menu selection.");

		printMainMenu(g);

		break;
	}

}

void printRules() { // Game rules print

	printf("\nGameplay:\n\n");

	printf("On a player's turn, they roll all five dice up to three times to achieve desired combinations.");
	printf("\nAfter the first roll, the player can choose which dice to keep and which to reroll.");
	printf("\nOnce all three rolls are taken, or if the player decides to stop early, the result is recorded on the scorecard.");

	printf("\nScoring:\n\n");

	printf("Players score points by achieving specific combinations of dice rolls as listed on the scorecard.");
	printf("\nThe combinations include ones, twos, threes, fours, fives, and sixes, where the score for each category is the total of those numbers rolled.");
	printf("\nAdditionally, there are bonus points awarded if the total of ones through sixes exceeds a certain threshold (usually 63).");
	printf("\nOther combinations include three of a kind, four of a kind, full house, small straight, large straight, Yahtzee (five of a kind), and chance (the total of all five dice).");
	printf("\nPlayers must select a category for their score each turn, and once a category is chosen, it cannot be used again in subsequent turns.");

	printf("\nBonus:\n\n");

	printf("If a player scores 63 or more points in the ones through sixes categories, they receive a bonus of 35 points.");

	printf("\nYatzhee Bonus:\n\n");

	printf("If a player rolls a Yahtzee and already has a score of 50 in the Yahtzee category, they receive a Yahtzee bonus of 100 points.");

	printf("\nEnd of Game:\n\n");

	printf("The game ends when all categories on the scorecard are filled.");
	printf("\nThe player with the highest total score wins the game.");

}

void printScorecard(GAME g, int** scoreArray) { // scoresheet with continuous updating 

	char score[5];

	printf("\n\n___________________________________________________________________________________________________\n");
	printf(" |Score # | UPPER SECTION || HOW TO SCORE || GAME #1 || GAME #2 || GAME #3 || GAME #4 || GAME #5 || GAME #6 |\n");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |        |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |    1   |ACES =   | 1 | ||              ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[0][0] != -1 ? (sprintf(score, "%d", scoreArray[0][0]), score) : " ",
		scoreArray[0][1] != -1 ? (sprintf(score, "%d", scoreArray[0][1]), score) : " ",
		scoreArray[0][2] != -1 ? (sprintf(score, "%d", scoreArray[0][2]), score) : " ",
		scoreArray[0][3] != -1 ? (sprintf(score, "%d", scoreArray[0][3]), score) : " ",
		scoreArray[0][4] != -1 ? (sprintf(score, "%d", scoreArray[0][4]), score) : " ",
		scoreArray[0][5] != -1 ? (sprintf(score, "%d", scoreArray[0][5]), score) : " ");

	printf(" |        |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |        |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |    2   |TWOS =   | 2 | ||              ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[1][0] != -1 ? (sprintf(score, "%d", scoreArray[1][0]), score) : " ",
		scoreArray[1][1] != -1 ? (sprintf(score, "%d", scoreArray[1][1]), score) : " ",
		scoreArray[1][2] != -1 ? (sprintf(score, "%d", scoreArray[1][2]), score) : " ",
		scoreArray[1][3] != -1 ? (sprintf(score, "%d", scoreArray[1][3]), score) : " ",
		scoreArray[1][4] != -1 ? (sprintf(score, "%d", scoreArray[1][4]), score) : " ",
		scoreArray[1][5] != -1 ? (sprintf(score, "%d", scoreArray[1][5]), score) : " ");
	printf(" |        |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |        |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |    3   |THREES = | 3 | ||              ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[2][0] != -1 ? (sprintf(score, "%d", scoreArray[2][0]), score) : " ",
		scoreArray[2][1] != -1 ? (sprintf(score, "%d", scoreArray[2][1]), score) : " ",
		scoreArray[2][2] != -1 ? (sprintf(score, "%d", scoreArray[2][2]), score) : " ",
		scoreArray[2][3] != -1 ? (sprintf(score, "%d", scoreArray[2][3]), score) : " ",
		scoreArray[2][4] != -1 ? (sprintf(score, "%d", scoreArray[2][4]), score) : " ",
		scoreArray[2][5] != -1 ? (sprintf(score, "%d", scoreArray[2][5]), score) : " ");
	printf(" |        |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |        |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   4    |FOURS =  | 4 | ||              ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[3][0] != -1 ? (sprintf(score, "%d", scoreArray[3][0]), score) : " ",
		scoreArray[3][1] != -1 ? (sprintf(score, "%d", scoreArray[3][1]), score) : " ",
		scoreArray[3][2] != -1 ? (sprintf(score, "%d", scoreArray[3][2]), score) : " ",
		scoreArray[3][3] != -1 ? (sprintf(score, "%d", scoreArray[3][3]), score) : " ",
		scoreArray[3][4] != -1 ? (sprintf(score, "%d", scoreArray[3][4]), score) : " ",
		scoreArray[3][5] != -1 ? (sprintf(score, "%d", scoreArray[3][5]), score) : " ");
	printf(" |        |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |        |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |    5   |FIVES =  | 5 | ||              ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[4][0] != -1 ? (sprintf(score, "%d", scoreArray[4][0]), score) : " ",
		scoreArray[4][1] != -1 ? (sprintf(score, "%d", scoreArray[4][1]), score) : " ",
		scoreArray[4][2] != -1 ? (sprintf(score, "%d", scoreArray[4][2]), score) : " ",
		scoreArray[4][3] != -1 ? (sprintf(score, "%d", scoreArray[4][3]), score) : " ",
		scoreArray[4][4] != -1 ? (sprintf(score, "%d", scoreArray[4][4]), score) : " ",
		scoreArray[4][5] != -1 ? (sprintf(score, "%d", scoreArray[4][5]), score) : " ");
	printf(" |        |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |        |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   6    |SIXES =  | 6 | ||              ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[5][0] != -1 ? (sprintf(score, "%d", scoreArray[5][0]), score) : " ",
		scoreArray[5][1] != -1 ? (sprintf(score, "%d", scoreArray[5][1]), score) : " ",
		scoreArray[5][2] != -1 ? (sprintf(score, "%d", scoreArray[5][2]), score) : " ",
		scoreArray[5][3] != -1 ? (sprintf(score, "%d", scoreArray[5][3]), score) : " ",
		scoreArray[5][4] != -1 ? (sprintf(score, "%d", scoreArray[5][4]), score) : " ",
		scoreArray[5][5] != -1 ? (sprintf(score, "%d", scoreArray[5][5]), score) : " ");
	printf(" |        |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   N/A  |TOTAL SCORE    || ===========> ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[14][0] != -1 ? (sprintf(score, "%d", scoreArray[14][0]), score) : " ",
		scoreArray[14][1] != -1 ? (sprintf(score, "%d", scoreArray[14][1]), score) : " ",
		scoreArray[14][2] != -1 ? (sprintf(score, "%d", scoreArray[14][2]), score) : " ",
		scoreArray[14][3] != -1 ? (sprintf(score, "%d", scoreArray[14][3]), score) : " ",
		scoreArray[14][4] != -1 ? (sprintf(score, "%d", scoreArray[14][4]), score) : " ",
		scoreArray[14][5] != -1 ? (sprintf(score, "%d", scoreArray[14][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   N/A  |BONUS          ||   SCORE 35   ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[15][0] != -1 ? (sprintf(score, "%d", scoreArray[15][0]), score) : " ",
		scoreArray[15][1] != -1 ? (sprintf(score, "%d", scoreArray[15][1]), score) : " ",
		scoreArray[15][2] != -1 ? (sprintf(score, "%d", scoreArray[15][2]), score) : " ",
		scoreArray[15][3] != -1 ? (sprintf(score, "%d", scoreArray[15][3]), score) : " ",
		scoreArray[15][4] != -1 ? (sprintf(score, "%d", scoreArray[15][4]), score) : " ",
		scoreArray[15][5] != -1 ? (sprintf(score, "%d", scoreArray[15][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   N/A  |TOTAL          || ===========> ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[16][0] != -1 ? (sprintf(score, "%d", scoreArray[16][0]), score) : " ",
		scoreArray[16][1] != -1 ? (sprintf(score, "%d", scoreArray[16][1]), score) : " ",
		scoreArray[16][2] != -1 ? (sprintf(score, "%d", scoreArray[16][2]), score) : " ",
		scoreArray[16][3] != -1 ? (sprintf(score, "%d", scoreArray[16][3]), score) : " ",
		scoreArray[16][4] != -1 ? (sprintf(score, "%d", scoreArray[16][4]), score) : " ",
		scoreArray[16][5] != -1 ? (sprintf(score, "%d", scoreArray[16][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||                                                                                |\n");
	printf(" |        | LOWER SECTION ||                                                                                |\n");
	printf(" |________|_______________||________________________________________________________________________________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   7    | 3 OF A KIND   ||             ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[6][0] != -1 ? (sprintf(score, "%d", scoreArray[6][0]), score) : " ",
		scoreArray[6][1] != -1 ? (sprintf(score, "%d", scoreArray[6][1]), score) : " ",
		scoreArray[6][2] != -1 ? (sprintf(score, "%d", scoreArray[6][2]), score) : " ",
		scoreArray[6][3] != -1 ? (sprintf(score, "%d", scoreArray[6][3]), score) : " ",
		scoreArray[6][4] != -1 ? (sprintf(score, "%d", scoreArray[6][4]), score) : " ",
		scoreArray[6][5] != -1 ? (sprintf(score, "%d", scoreArray[6][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   8    | 4 OF A KIND   ||             ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[7][0] != -1 ? (sprintf(score, "%d", scoreArray[7][0]), score) : " ",
		scoreArray[7][1] != -1 ? (sprintf(score, "%d", scoreArray[7][1]), score) : " ",
		scoreArray[7][2] != -1 ? (sprintf(score, "%d", scoreArray[7][2]), score) : " ",
		scoreArray[7][3] != -1 ? (sprintf(score, "%d", scoreArray[7][3]), score) : " ",
		scoreArray[7][4] != -1 ? (sprintf(score, "%d", scoreArray[7][4]), score) : " ",
		scoreArray[7][5] != -1 ? (sprintf(score, "%d", scoreArray[7][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   9    | FULL HOUSE    ||             ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[8][0] != -1 ? (sprintf(score, "%d", scoreArray[8][0]), score) : " ",
		scoreArray[8][1] != -1 ? (sprintf(score, "%d", scoreArray[8][1]), score) : " ",
		scoreArray[8][2] != -1 ? (sprintf(score, "%d", scoreArray[8][2]), score) : " ",
		scoreArray[8][3] != -1 ? (sprintf(score, "%d", scoreArray[8][3]), score) : " ",
		scoreArray[8][4] != -1 ? (sprintf(score, "%d", scoreArray[8][4]), score) : " ",
		scoreArray[8][5] != -1 ? (sprintf(score, "%d", scoreArray[8][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   10   | SM. STRAIGHT  ||           ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[9][0] != -1 ? (sprintf(score, "%d", scoreArray[9][0]), score) : " ",
		scoreArray[9][1] != -1 ? (sprintf(score, "%d", scoreArray[9][1]), score) : " ",
		scoreArray[9][2] != -1 ? (sprintf(score, "%d", scoreArray[9][2]), score) : " ",
		scoreArray[9][3] != -1 ? (sprintf(score, "%d", scoreArray[9][3]), score) : " ",
		scoreArray[9][4] != -1 ? (sprintf(score, "%d", scoreArray[9][4]), score) : " ",
		scoreArray[9][5] != -1 ? (sprintf(score, "%d", scoreArray[9][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||           ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   11   | LG. STRAIGHT  ||           ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[10][0] != -1 ? (sprintf(score, "%d", scoreArray[10][0]), score) : " ",
		scoreArray[10][1] != -1 ? (sprintf(score, "%d", scoreArray[10][1]), score) : " ",
		scoreArray[10][2] != -1 ? (sprintf(score, "%d", scoreArray[10][2]), score) : " ",
		scoreArray[10][3] != -1 ? (sprintf(score, "%d", scoreArray[10][3]), score) : " ",
		scoreArray[10][4] != -1 ? (sprintf(score, "%d", scoreArray[10][4]), score) : " ",
		scoreArray[10][5] != -1 ? (sprintf(score, "%d", scoreArray[10][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||            ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   12   |    YAHTZEE    ||            ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[11][0] != -1 ? (sprintf(score, "%d", scoreArray[11][0]), score) : " ",
		scoreArray[11][1] != -1 ? (sprintf(score, "%d", scoreArray[11][1]), score) : " ",
		scoreArray[11][2] != -1 ? (sprintf(score, "%d", scoreArray[11][2]), score) : " ",
		scoreArray[11][3] != -1 ? (sprintf(score, "%d", scoreArray[11][3]), score) : " ",
		scoreArray[11][4] != -1 ? (sprintf(score, "%d", scoreArray[11][4]), score) : " ",
		scoreArray[11][5] != -1 ? (sprintf(score, "%d", scoreArray[11][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||             ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   13   |    CHANCE     ||             ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[12][0] != -1 ? (sprintf(score, "%d", scoreArray[12][0]), score) : " ",
		scoreArray[12][1] != -1 ? (sprintf(score, "%d", scoreArray[12][1]), score) : " ",
		scoreArray[12][2] != -1 ? (sprintf(score, "%d", scoreArray[12][2]), score) : " ",
		scoreArray[12][3] != -1 ? (sprintf(score, "%d", scoreArray[12][3]), score) : " ",
		scoreArray[12][4] != -1 ? (sprintf(score, "%d", scoreArray[12][4]), score) : " ",
		scoreArray[12][5] != -1 ? (sprintf(score, "%d", scoreArray[12][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||  |   |  ||  |   |  ||  |   |  ||  |   |  ||  |   |  ||  |   |  |\n");
	printf(" |        |               ||              ||  |   |  ||  |   |  ||  |   |  ||  |   |  ||  |   |  ||  |   |  |\n");
	printf(" |        |    YATZHEE    ||______________||__|___|__||__|___|__||__|___|__||__|___|__||__|___|__||__|___|__|\n");
	printf(" |   14   |     BONUS     ||            ||         ||         ||         ||         ||         ||         |\n");
	printf(" |        |               ||              ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[13][0] != -1 ? (sprintf(score, "%d", scoreArray[13][0]), score) : " ",
		scoreArray[13][1] != -1 ? (sprintf(score, "%d", scoreArray[13][1]), score) : " ",
		scoreArray[13][2] != -1 ? (sprintf(score, "%d", scoreArray[13][2]), score) : " ",
		scoreArray[13][3] != -1 ? (sprintf(score, "%d", scoreArray[13][3]), score) : " ",
		scoreArray[13][4] != -1 ? (sprintf(score, "%d", scoreArray[13][4]), score) : " ",
		scoreArray[13][5] != -1 ? (sprintf(score, "%d", scoreArray[13][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   N/A  | TOTAL OF UPPER|| ===========> ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[16][0] != -1 ? (sprintf(score, "%d", scoreArray[16][0]), score) : " ",
		scoreArray[16][1] != -1 ? (sprintf(score, "%d", scoreArray[16][1]), score) : " ",
		scoreArray[16][2] != -1 ? (sprintf(score, "%d", scoreArray[16][2]), score) : " ",
		scoreArray[16][3] != -1 ? (sprintf(score, "%d", scoreArray[16][3]), score) : " ",
		scoreArray[16][4] != -1 ? (sprintf(score, "%d", scoreArray[16][4]), score) : " ",
		scoreArray[16][5] != -1 ? (sprintf(score, "%d", scoreArray[16][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   N/A  | TOTAL OF LOWER|| ===========> ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[17][0] != -1 ? (sprintf(score, "%d", scoreArray[17][0]), score) : " ",
		scoreArray[17][1] != -1 ? (sprintf(score, "%d", scoreArray[17][1]), score) : " ",
		scoreArray[17][2] != -1 ? (sprintf(score, "%d", scoreArray[17][2]), score) : " ",
		scoreArray[17][3] != -1 ? (sprintf(score, "%d", scoreArray[17][3]), score) : " ",
		scoreArray[17][4] != -1 ? (sprintf(score, "%d", scoreArray[17][4]), score) : " ",
		scoreArray[17][5] != -1 ? (sprintf(score, "%d", scoreArray[17][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |        |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |   N/A  |  GRAND TOTAL  || ===========> ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     ||  %s     |\n",
		scoreArray[18][0] != -1 ? (sprintf(score, "%d", scoreArray[18][0]), score) : " ",
		scoreArray[18][1] != -1 ? (sprintf(score, "%d", scoreArray[18][1]), score) : " ",
		scoreArray[18][2] != -1 ? (sprintf(score, "%d", scoreArray[18][2]), score) : " ",
		scoreArray[18][3] != -1 ? (sprintf(score, "%d", scoreArray[18][3]), score) : " ",
		scoreArray[18][4] != -1 ? (sprintf(score, "%d", scoreArray[18][4]), score) : " ",
		scoreArray[18][5] != -1 ? (sprintf(score, "%d", scoreArray[18][5]), score) : " ");
	printf(" |________|_______________||______________||_________||_________||_________||_________||_________||_________|\n");


}
void diceAnimation() {

	// Dice animation whenever someone rolls

	printf("\n ____\n");
	printf(" /\\' .\\    _____\n");
	printf("/: \\___\\  / .  /\\\n");
	printf("\\' / . / /____/..\\\n");
	printf(" \\/___/  \\'  '\\  /\n");
	printf("          \\'__'\\/\n");

}
