#include "UI.h"
#include "GameLogic.h"

void printMainMenu(UI interface) {

	printf("Number of players: %d", interface.numOfPlayers);

	printf("\n\nWelcome to Yhatzee! This is a console based version of the beloved classic dice game... known as Yahtzee.\n");
	printf("\n=================================================================================================================\n");

	printf("Menu:\n\n");
	printf("1. Play Game.\n");
	printf("2. View Rules.\n");
	printf("3. Exit Game.\n");
	printf("\nChoice: ");

}

void menuChoice(UI interface) {

	int choice = 0;

	scanf_s("%d", &choice);

	switch (choice)
	{

	case 1:

		// TODO: Play game

		break;

	case 2:

		printRules();

		printMainMenu(interface);

		break;

	case 3:

		// TODO: Exit & Save game.

		break;

	default:

		fprintf(stderr, "ERROR: Invalid menu selection. ");

		printMainMenu(interface);

		break;
	}

}


void printRules() {

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

void printSubMenu(UI interface) {



}

void printScorecard(UI interface) {

	printf("__   __        _      _                     \n");
	printf("\ \ / /       | |    | |                    \n");
	printf(" \ V /   __ _ | |__  | |_  ____  ___   ___  \n");
	printf("  \ /   / _` || '_ \ | __||_  / / _ \ / _ \ \n");
	printf("  | |  | (_| || | | || |_  / / |  __/|  __/ \n");
	printf("  \_/   \__,_||_| |_| \__|/___| \___| \___| \n");

	// logo^^

	printf(" ___________________________________________________________________________________________________\n");
	printf(" | UPPER SECTION || HOW TO SCORE || GAME #1 || GAME #2 || GAME #3 || GAME #4 || GAME #5 || GAME #6 |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |ACES =   | 1 | ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |TWOS =   | 2 | ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |THREES = | 3 | ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |FOURS =  | 4 | ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |FIVES =  | 5 | ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |SIXES =  | 6 | ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |TOTAL SCORE    || ===========> ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |BONUS          ||   SCORE 35   ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |TOTAL          || ===========> ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||                                                                                |\n");
	printf(" | LOWER SECTION ||                                                                                |\n");
	printf(" |_______________||________________________________________________________________________________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | 3 OF A KIND   ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | 4 OF A KIND   ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | FULL HOUSE    ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | SM. STRAIGHT  ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | LG. STRAIGHT  ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |    YAHTZEE    ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |    CHANCE     ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||  |   |  ||  |   |  ||  |   |  ||  |   |  ||  |   |  ||  |   |  |\n");
	printf(" |               ||              ||  |   |  ||  |   |  ||  |   |  ||  |   |  ||  |   |  ||  |   |  |\n");
	printf(" |    YATZHEE    ||______________||__|___|__||__|___|__||__|___|__||__|___|__||__|___|__||__|___|__|\n");
	printf(" |     BONUS     ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | TOTAL OF UPPER|| ===========> ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | TOTAL OF LOWER|| ===========> ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |  GRAND TOTAL  || ===========> ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");


}
