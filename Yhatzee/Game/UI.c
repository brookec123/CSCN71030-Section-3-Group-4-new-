#include "UI.h"
#include "GameLogic.h"
#include "Die.h"
#include "FileIO.h"

UI u;

void printMainMenu(UI u) {

	printf("__   __        _      _                     \n");
	printf("\ \ / /       | |    | |                    \n");
	printf(" \ V /   __ _ | |__  | |_  ____  ___   ___  \n");
	printf("  \ /   / _` || '_ \ | __||_  / / _ \ / _ \ \n");
	printf("  | |  | (_| || | | || |_  / / |  __/|  __/ \n");
	printf("  \_/   \__,_||_| |_| \__|/___| \___| \___| \n");

	printf("Number of players: %d", u.numOfPlayers);

	printf("\n\nWelcome to Yhatzee! This is a console based version of the beloved classic dice game... known as Yahtzee.\n");
	printf("\n=================================================================================================================\n");

	printf("Menu:\n\n");
	printf("1. Play Game.\n");
	printf("2. Load Saved Game.\n");
	printf("3. View Rules.\n");
	printf("4. Exit Game.\n");
	printf("\nChoice: ");

}

void menuChoice(UI u) {

	DIE d;
	PLAYER p;
	PPLAYER pp;

	int choice = 0;

	scanf_s("%d", &choice);

	switch (choice)
	{

	case 1:

		d = CreateDie(); // die is created

		int dchoice = 0;

		printf("\n\nHow many dice would you like to roll? Please pick a number from 1 to 5:");

		scanf_s("%d", &dchoice);

		// Roll dice based on user input
		
		do {

			if (dchoice == 1) {

				int dicenum = 0;

				printf("Which dice would you like to roll? Please pick a number from 1 to 5: ");
				
				scanf_s("%d", &dicenum);

				if (dicenum != 1) {

					diceAnimation();

					for (int i = 0; i < dicenum; i++) {

						RollDie(&d);

					}

				}
				else {

					diceAnimation();
					
					RollDie(&d);

				}

				printf("\n\nYou have rolled %d dice.\n\n", dicenum);

			} else if (dchoice > 1 && dchoice < 6) {

				diceAnimation();

				RollArrayOfDice(&d, dchoice);

			}
			else {

				fprintf(stderr, "ERROR: Dice number not valid. Please re-enter.");

			}

			char schoice;

			printf("Would you like to roll more dice? Y/N: ");

			scanf_s("%c", &schoice, 1);

			if (schoice == 'Y' || schoice == 'y') {

				dchoice == 1;

			}
			else if (schoice == 'N' || schoice == 'n') {

				dchoice == 0;

				printScorecard(u, 0);

			} 
			else {

				fprintf(stderr, "ERROR: Not a valid input. Please re-enter.");

			}

		} while (dchoice >= 1 && dchoice <= 5);

		break;

	case 2:

		loadGame('r', pp);

	case 3:

		printRules();

		printMainMenu(u);

		break;

	case 4:

		saveGame('w', p);

		printf("\n\nGame successfully saved!\n");
		printf("\nThanks for playing!\n");

		break;


	default:

		fprintf(stderr, "ERROR: Invalid menu selection. ");

		printMainMenu(u);

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

void printSubMenu(UI u) {



}

void printScorecard(UI u, int** scoreArray) {

	PLAYER p;

	printf(" ___________________________________________________________________________________________________\n");
	printf(" | UPPER SECTION || HOW TO SCORE || GAME #1 || GAME #2 || GAME #3 || GAME #4 || GAME #5 || GAME #6 |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |ACES =   | 1 | ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][0], scoreArray[1][0], scoreArray[2][0], scoreArray[3][0], scoreArray[4][0], scoreArray[5][0]);
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |TWOS =   | 2 | ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][1], scoreArray[1][1], scoreArray[2][1], scoreArray[3][1], scoreArray[4][1], scoreArray[5][1]);
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |THREES = | 3 | ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][2], scoreArray[1][2], scoreArray[2][2], scoreArray[3][2], scoreArray[4][2], scoreArray[5][2]);
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |FOURS =  | 4 | ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][3], scoreArray[1][3], scoreArray[2][3], scoreArray[3][3], scoreArray[4][3], scoreArray[5][3]);
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |FIVES =  | 5 | ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][4], scoreArray[1][4], scoreArray[2][4], scoreArray[3][4], scoreArray[4][4], scoreArray[5][4]);
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |SIXES =  | 6 | ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][5], scoreArray[1][5], scoreArray[2][5], scoreArray[3][5], scoreArray[4][5], scoreArray[5][5]);
	printf(" |         +---+ ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |TOTAL SCORE    || ===========> ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][14], scoreArray[1][14], scoreArray[2][14], scoreArray[3][14], scoreArray[4][14], scoreArray[5][14]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |BONUS          ||   SCORE 35   ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][15], scoreArray[1][15], scoreArray[2][15], scoreArray[3][15], scoreArray[4][15], scoreArray[5][15]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |TOTAL          || ===========> ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][16], scoreArray[1][16], scoreArray[2][16], scoreArray[3][16], scoreArray[4][16], scoreArray[5][16]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||                                                                                |\n");
	printf(" | LOWER SECTION ||                                                                                |\n");
	printf(" |_______________||________________________________________________________________________________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | 3 OF A KIND   ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][6], scoreArray[1][6], scoreArray[2][6], scoreArray[3][6], scoreArray[4][6], scoreArray[5][6]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | 4 OF A KIND   ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][7], scoreArray[1][7], scoreArray[2][7], scoreArray[3][7], scoreArray[4][7], scoreArray[5][7]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | FULL HOUSE    ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][8], scoreArray[1][8], scoreArray[2][8], scoreArray[3][8], scoreArray[4][8], scoreArray[5][8]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | SM. STRAIGHT  ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][9], scoreArray[1][9], scoreArray[2][9], scoreArray[3][9], scoreArray[4][9], scoreArray[5][9]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | LG. STRAIGHT  ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][10], scoreArray[1][10], scoreArray[2][10], scoreArray[3][10], scoreArray[4][10], scoreArray[5][10]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |    YAHTZEE    ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][11], scoreArray[1][11], scoreArray[2][11], scoreArray[3][11], scoreArray[4][11], scoreArray[5][11]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |    CHANCE     ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][12], scoreArray[1][12], scoreArray[2][12], scoreArray[3][12], scoreArray[4][12], scoreArray[5][12]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||  |   |  ||  |   |  ||  |   |  ||  |   |  ||  |   |  ||  |   |  |\n");
	printf(" |               ||              ||  |   |  ||  |   |  ||  |   |  ||  |   |  ||  |   |  ||  |   |  |\n");
	printf(" |    YATZHEE    ||______________||__|___|__||__|___|__||__|___|__||__|___|__||__|___|__||__|___|__|\n");
	printf(" |     BONUS     ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |               ||              ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][13], scoreArray[1][13], scoreArray[2][13], scoreArray[3][13], scoreArray[4][13], scoreArray[5][13]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | TOTAL OF UPPER|| ===========> ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][16], scoreArray[1][16], scoreArray[2][16], scoreArray[3][16], scoreArray[4][16], scoreArray[5][16]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" | TOTAL OF LOWER|| ===========> ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][17], scoreArray[1][17], scoreArray[2][17], scoreArray[3][17], scoreArray[4][17], scoreArray[5][17]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");
	printf(" |               ||              ||         ||         ||         ||         ||         ||         |\n");
	printf(" |  GRAND TOTAL  || ===========> ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    ||   %d    |\n", scoreArray[0][18], scoreArray[1][18], scoreArray[2][18], scoreArray[3][18], scoreArray[4][18], scoreArray[5][18]);
	printf(" |_______________||______________||_________||_________||_________||_________||_________||_________|\n");


}

void diceAnimation() {

	// Dice animation whenever someone rolls

	printf("\n ____\n");
	printf(" /\' .\    _____\n");
	printf("/: \___\  / .  /\\n");
	printf("\' / . / /____/..\\n");
	printf(" \/___/  \'  '\  /\n");
	printf("          \'__'\/\n");

}
