#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include "CppUnitTest.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <stdbool.h>
#include "../Game/Die.h"
#include "../Game/Game.h"
#include "../Game/Player.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
extern "C" int convertAndValidateUserInputToScoreIndex(int);
extern "C" void goToNextPlayer(GAME*);
extern "C" GAME initializeGame();
extern "C" int calculateUpper(DIE*, int);
extern "C" DIE CreateDie();
extern "C" void diceAnimation();
extern "C" void printMainMenu(GAME* g);
extern "C" int saveGame(char* n, PLAYER p);
extern "C" int loadGame(char* n, PPLAYER p);
extern "C" bool antiCheat(PLAYER p);


namespace GameTests
{
	TEST_CLASS(UITests)
	{
	public:
		TEST_METHOD(TestPrintingMainMenu)
		{
			// Open the file
			FILE* outputFile;
			if (fopen_s(&outputFile, "output.txt", "w") != 0) {
				Logger::WriteMessage("Failed to open output file.");
				return;
			}

			// Redirect stdout to the file
			if (freopen_s(&outputFile, "output.txt", "w", stdout) != 0 || outputFile == nullptr) {
				// Close the file stream if it was opened
				if (outputFile != nullptr) {
					fclose(outputFile);
				}
				return; // Return from the function or handle the error accordingly
			}

			// Call the function to be tested
			GAME g = initializeGame();
			printMainMenu(&g);

			// Close the redirected stream
			fflush(stdout);
			fclose(outputFile);

			// Read the contents of the file
			std::ifstream inputFile("output.txt");
			std::string output;
			if (inputFile.is_open()) {
				std::string line;
				while (std::getline(inputFile, line)) {
					output += line + "\n";
				}
				inputFile.close();
			}

			// Assert the output
			std::string expectedOutput = "\n__   __        _      _                     \n"
				"\\ \\ / /       | |    | |                    \n"
				" \\ V /   __ _ | |__  | |_  ____  ___   ___  \n"
				"  \\ /   / _` || '_ \\ | __||_  / / _ \\ / _ \\ \n"
				"  | |  | (_| || | | || |_  / / |  __/|  __/ \n"
				"  \\_/   \\__,_||_| |_| \\__|/___| \\___| \\___| \n"
				"\nNumber of players: 3"
				"\n\nWelcome to Yhatzee! This is a console based version of the beloved classic dice game... known as Yhatzee.\n"
				"\n=================================================================================================================\n"
				"Menu:\n\n"
				"1. Play Game.\n"
				"2. Load Saved Game.\n"
				"3. View Rules.\n"
				"4. Exit Game.\n"
				"\nChoice: ";
			Assert::AreEqual(expectedOutput, output);
		}
		TEST_METHOD(TestPrintingDiceAnimation)
		{
			// Open the file
			FILE* outputFile;
			if (fopen_s(&outputFile, "output.txt", "w") != 0) {
				Logger::WriteMessage("Failed to open output file.");
				return;
			}

			// Redirect stdout to the file
			if (freopen_s(&outputFile, "output.txt", "w", stdout) != 0 || outputFile == nullptr) {
				// Close the file stream if it was opened
				if (outputFile != nullptr) {
					fclose(outputFile);
				}
				return; // Return from the function or handle the error accordingly
			}

			// Call the function to be tested
			diceAnimation();

			// Close the redirected stream
			fflush(stdout);
			fclose(outputFile);

			// Read the contents of the file
			std::ifstream inputFile("output.txt");
			std::string output;
			if (inputFile.is_open()) {
				std::string line;
				while (std::getline(inputFile, line)) {
					output += line + "\n";
				}
				inputFile.close();
			}

			// Assert the output
			std::string expectedOutput = "\n ____\n"
				" /\\' .\\    _____\n"
				"/: \\___\\  / .  /\\\n"
				"\\' / . / /____/..\\\n"
				" \\/___/  \\'  '\\  /\n"
				"          \\'__'\\/\n";
			Assert::AreEqual(expectedOutput, output);
		}
	};

	TEST_CLASS(FileIOTests)
	{
	public:

		TEST_METHOD(TC_005_03_TestSaveGameWithValidPlayerAndFile) {

			char* filename = "testfile.txt";

			PLAYER p = CreateNewPlayer("Test_Player");

			int result = saveGame(filename, p);

			Assert::AreEqual(0, result);

		}

		TEST_METHOD(TC_005_03_TestSaveGameWithInvalidFile) {

			char* filename = " ";

			PLAYER p = CreateNewPlayer("Test Player");

			int result = saveGame(filename, p);

			Assert::AreEqual(1, result);

		}

		TEST_METHOD(TC_005_03_TestSaveGameWithInvalidPlayer) {

			char* filename = "testfile.txt";

			PLAYER p = CreateNewPlayer(" ");

			int result = saveGame(filename, p);

			Assert::AreEqual(0, result);

		}

		TEST_METHOD(TC_005_03_TestSaveGameWithMaxGames) {

			char* filename = "testfile.txt";

			PLAYER p = CreateNewPlayer("Test_Player");

			SetCurrentGameNumber(&p, MAX_NUMBER_OF_GAMES);

			int result = saveGame(filename, p);

			Assert::AreEqual(0, result);

		}

		TEST_METHOD(TC_005_03_TestSaveGameWithNoGames) {

			char* filename = "testfile.txt";

			PLAYER p = CreateNewPlayer("Test_Player");

			SetCurrentGameNumber(&p, 0);

			int result = saveGame(filename, p);

			Assert::AreEqual(0, result);

		}

		TEST_METHOD(TC_005_03_TestLoadGameWithValidPlayerAndFile) {

			char* filename = "testfile.txt";

			PLAYER p = CreateNewPlayer("Test_Player");

			int result = loadGame(filename, &p);

			Assert::AreEqual(0, result);

		}

		TEST_METHOD(TC_005_03_TestLoadGameWithInvalidFile) {

			char* filename = " ";

			PLAYER p = CreateNewPlayer("Test_Player");

			int result = loadGame(filename, &p);

			Assert::AreEqual(1, result);

		}

		TEST_METHOD(TC_005_03_TestLoadGameWithMaxGames) {

			char* filename = "testfile.txt";

			PLAYER p = CreateNewPlayer("Test_Player");

			SetCurrentGameNumber(&p, MAX_NUMBER_OF_GAMES);

			int result = loadGame(filename, &p);

			Assert::AreEqual(0, result);

		}

		TEST_METHOD(TC_005_03_TestLoadGameWithNoGames) {

			char* filename = "testfile.txt";

			PLAYER p = CreateNewPlayer("Test_Player");

			SetCurrentGameNumber(&p, 0);

			int result = loadGame(filename, &p);

			Assert::AreEqual(0, result);

		}

		TEST_METHOD(TC_005_03_TestAntiCheatWithValidPlayer) {

			PLAYER p = CreateNewPlayer("Test_Player");

			bool result = antiCheat(p);

			Assert::IsFalse(result);

		}

		TEST_METHOD(TC_005_03_TestAntiCheatWithInvalidGameNumber) {

			PLAYER p = CreateNewPlayer("Test_Player");

			SetCurrentGameNumber(&p, 11);

			bool result = antiCheat(p);

			Assert::IsFalse(result);

		}

		TEST_METHOD(TC_005_03_TestAntiCheatWithScoreOutOfBounds) {

			PLAYER p = CreateNewPlayer("Test_Player");

			p.currentScore[0][0] = 6;

			bool result = antiCheat(p);

			Assert::IsFalse(result);

		}

		TEST_METHOD(TC_005_03_TestAntiCheatWithScorableScore) {

			PLAYER p = CreateNewPlayer("Test_Player");

			p.currentScore[0][0] = 5;

			p.canScore[0][0] = -1;

			bool result = antiCheat(p);

			Assert::IsFalse(result);

		}

	};
	TEST_CLASS(GameTests)
	{
	public:

		TEST_METHOD(TestconvertAndValidateUserInputToScoreIndex01)
		{//Handles valid values
			int result = convertAndValidateUserInputToScoreIndex(8);
			Assert::AreEqual(result, 7);
		}
		TEST_METHOD(TestconvertAndValidateUserInputToScoreIndex02)
		{//Handles values too small
			int result = convertAndValidateUserInputToScoreIndex(-12321);
			Assert::AreEqual(result, -1);
		}
		TEST_METHOD(TestconvertAndValidateUserInputToScoreIndex03)
		{//Handles values that are too large
			int result = convertAndValidateUserInputToScoreIndex(15);
			Assert::AreEqual(result, -1);
		}
		TEST_METHOD(TestconvertAndValidateUserInputToScoreIndex04)
		{//LowerBoundary Test
			int result = convertAndValidateUserInputToScoreIndex(1);
			Assert::AreEqual(result, 0);
		}
		TEST_METHOD(TestconvertAndValidateUserInputToScoreIndex05)
		{//Upper Boundary Test
			int result = convertAndValidateUserInputToScoreIndex(14);
			Assert::AreEqual(result, 13);
		}
		TEST_METHOD(TestNextPlayer)
		{//Does going to the next player actually work
			GAME g = initializeGame();
			int result = 1;
			goToNextPlayer(&g);
			Assert::AreEqual(result, g.currentPlayerIndex);
		}

	};
	TEST_CLASS(DieTests) {
		TEST_METHOD(TestCreateDie) {
			DIE d = CreateDie();
			Assert::AreEqual(d.value, 0);
		}
		TEST_METHOD(TestRollDie) {
			DIE d = CreateDie();
			RollDie(&d);
			Assert::AreNotEqual(d.value, 0);
		}
	};


	TEST_CLASS(GameLogicTests) {
		TEST_METHOD(TestcalaculateUpper01) {
			DIE d[5];
			for (int i = 0; i < 5; i++) {
				d[i] = CreateDie();
				SetValue(&d[i], 3);
			}
			//should be all 5
			int result = calculateUpper(d, 3);
			Assert::AreEqual(result, 15);
		}
		TEST_METHOD(TestcalaculateUpper02) {
			DIE d[5];
			for (int i = 0; i < 5; i++) {
				d[i] = CreateDie();
				SetValue(&d[i], 6);
			}
			//none of them should have a 3
			int result = calculateUpper(d, 3);
			Assert::AreEqual(result, 0);
		}
		TEST_METHOD(TestSetValue) {
			DIE d[5];
			for (int i = 0; i < 5; i++) {
				d[i] = CreateDie();
				SetValue(&d[i], 3);
			}

			int result = calculateUpper(d, 3);
			Assert::AreEqual(result, 15);
		}
	};

	TEST_CLASS(PlayerTests) {
		TEST_METHOD(TestIsGameDoneForPlayer) {
			PLAYER p = CreateNewPlayer("Tester");
			bool result = IsGameDoneForPlayer(p);
			Assert::AreEqual(result, false);
		}


	};
}
