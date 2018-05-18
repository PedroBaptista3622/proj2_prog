/*
#ifdef _WIN32
#include "stdafx.h"
#endif
*/
/*
#include <iostream>
#include <iomanip>
#include <sstream>


#include "board.h"
#include "Dictionary.h"
#include "player.h"
#include "puzzle.h"

using namespace std;

void printLogo()
{
	cout << "-----------------------------" << endl;
	cout << "-----------CwPlayer----------" << endl;
	cout << "-----------------------------" << endl;
}//To be changed

int guessWord(Puzzle *puzzle, string position, string word)
{
	switch (puzzle->insGuess(position, word))
	{
	case -1:
		cerr << "Word doesn't exist" << endl;
		return -1;
		break;

	case -2:
		cerr << "Ilegal Overlap" << endl;
		return -2;
		break;

	case -3:
		cerr << "Lack of Space" << endl;
		return -3;
		break;

	case -4:
		cerr << "Repeated Words" << endl;
		return -4;
		break;

	case -5:
		cerr << "Invalid Position" << endl;
		return -5;
		break;

	case 0:
		return 0;
		break;
	}
}
*/
/*
int main()
{
	int numberBoardToLoad;
	bool validBoardNumber = false;
	ostringstream boardFileName;
	bool errorOpeningFile = false;

	printLogo();

		cout << "Please enter the number of the board you want to load (0 to 999)" << endl;

		do
		{
			cin >> numberBoardToLoad;

			if (numberBoardToLoad >= 0 && numberBoardToLoad <= 999)
				validBoardNumber = true;

		} while (!validBoardNumber);

		boardFileName << "B";
		boardFileName << fixed << setfill('0');
		boardFileName << setw(3) << numberBoardToLoad;
		boardFileName << ".txt";

		Puzzle puzzle(boardFileName.str(), errorOpeningFile);

		if (errorOpeningFile)
		{
			cerr << "Error Opening Files, try again" << endl;
		}


	string playerName;
	bool confirmation = false;
	bool validAnswer = false;
	char answer;

	cout << "Time to get information about you, what's your name?" << endl;
	
	do
	{
		getline(cin, playerName);

		cin.clear();
		cin.ignore(999999);

		cout << "Is \"" << playerName << "\" your name? (Y/N)" << endl;
		
		do
		{
			cin >> answer;

			if (answer == 'Y' || answer == 'y')
			{	
				confirmation = true;
				validAnswer = true;
			}
			else if (answer == 'N' || answer == 'n')
			{
				validAnswer = true;
				cout << "Enter another name" << endl;
			}
			else
			{
				cout << "Invalid Answer, try again" << endl;
			}

		} while (!validAnswer);

	} while (!confirmation);


	Player player(playerName);
	string position;
	string guess;
	bool validGuess = false;

	puzzle.showPuzzle(); // Empty puzzle?
	puzzle.showSynonyms();

	cout << "Enter the position you want to guess (LcD)" << endl;
	cin >> position;

	do
	{
		cout << "Enter the guess word" << endl;
		cin >> guess;

		if (guessWord(&puzzle, position, guess) == 0)
			validGuess = true;

		if (!validGuess)
			cout << "Try another word" << endl;

	} while (!validGuess);

	return 0;
}
*/