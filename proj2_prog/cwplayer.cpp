
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
		cerr << "That word is too big" << endl;
		return -1;

		case -2:
		cerr << "There was an ilegal overlap" << endl;
		return -2;

		case -3:
		cerr << "That word is too small" << endl;
		return -3;

		case -4:
		cerr << "You already input that word" << endl;
		return -4;

		case -5:
		cerr << "Invalid Position" << endl;
		return -5;

		case -6:
		cerr << "There is already a word in that position" << endl;
		return -6;

		case 0:
		return 0;
		break;
	}
}


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

		numberBoardToLoad = readInt("Please enter a number from 0 to 999.\nYour input: ");

		if (numberBoardToLoad >= 0 && numberBoardToLoad <= 999)
		validBoardNumber = true;
		else
		cout << "Please enter a number from 0 to 999.\nYour input: ";

	} while (!validBoardNumber);

	boardFileName << "B";
	boardFileName << fixed << setfill('0');
	boardFileName << setw(3) << numberBoardToLoad;
	boardFileName << ".txt";

	Puzzle puzzle(boardFileName.str(), errorOpeningFile);

	if (errorOpeningFile)
	{
		cerr << "Error loading board and dictionary." << endl;
		cerr << "You might have input the wrong number, or the dictionary does not exist anymore" << endl;
	}


	string playerName;
	bool confirmation = false;
	bool validAnswer = false;
	char answer;

	cout << "Time to get information about you, what's your name?" << endl;

	do
	{
		playerName = readString("Please enter your name.\n");

		cout << "Is \"" << playerName << "\" your name? (Y/N)" << endl;

		do
		{
			answer = readChar("Please answer the question (Y/N).\nYour answer: ");

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
				cout << "Please answer the question (Y/N).\nYour answer: " << endl;
			}

		} while (!validAnswer);

	} while (!confirmation);


	Player player(playerName);
	string position;
	string guess;
	bool validGuess = false;
	int action;
	bool correctPuzzle = false;

	player.start();

	do
	{
		do
		{
			puzzle.showPuzzle();
			puzzle.showSynonyms();

			cout << "Select action:" << endl;
			cout << "1 - Guess a word" << endl;
			cout << "2 - Delete word from board" << endl;
			cout << "0 - Exit" << endl;
			cout << "Note: If you exit before completing the puzzle correctly your progress will be lost" << endl;

			do
			{
				action = readInt("Please enter a valid action.\nYour action: ");

				if (action < 0 || action > 2)
				{
					cout << "Please enter a valid action.\nYour action: ";
				}

			} while (action < 0 || action > 2);
			//Takes care of actions. Only accepts actions = 0, 1 or 2.

			if (action == 1)
			{
				wordPosition pos;
				do
				{
					cout << "Enter the position you want to guess (LcD)" << endl;
					position = readString("Please enter a position (LcD)\n");
					pos = wordPosition(position);

					if (!pos.inBoard(puzzle.getLines(),puzzle.getColumns()))
					{
						cout << "Invalid input. You must enter a valid position inside of the board." << endl;
					}
					do
					{
						cout << "Enter your guess" << endl;
						cout << "You can also get some help by entering \'?\'" << endl;
						guess = readString("Enter a word to guess or \"?\"\n");


						if (guess == "?")
						{
							cout << "Hint: " << puzzle.anotherHint(position) << endl;
							player.gotHint();
						}
						else
						{
							if (guessWord(&puzzle, position, guess) == 0)
								validGuess = true;
						}
					} while (!validGuess);
				} while (!pos.isValid());

			}
			else if (action == 2)
			{
				string position;
				wordPosition pos;
				bool validPosition = false;

				cout << "Enter the position of the word you want to remove" << endl;

				do
				{
					position = readString("Enter the position of the word you want to remove\n");
					pos = wordPosition(position);

					if (!pos.inBoard(puzzle.getLines(),puzzle.getColumns()))
					{
						cout << "Invalid position. Please enter a valid position in the board.\n";
						continue;
					}

					if (puzzle.remGuess(position) == 0)
						validPosition = true;
					else
						cerr << "No word in such position, enter another one" << endl;

				} while (!validPosition);

			}

		} while (!puzzle.complete() && action != 0);

		if (puzzle.complete())
		{
			char answer;
			bool validAnswer = false;

			cout << "You completed the puzzle spaces. Do you want to check if it is correct? (Y/N)" << endl;

			do
			{
				cin >> answer;

				if (answer == 'Y' || answer == 'y')
				{
					validAnswer = true;

					if (puzzle.correct())
					{
						player.end();
						correctPuzzle = true;
						cout << "Congratulations, " << player.getName() << " you finished the puzzle in " << player.timeToComplete() << " seconds." << endl;

						ostringstream fileName;
						ofstream outFile;
						outFile.open(fileName.str(), std::ios_base::app);

						fileName << "B";
						fileName << fixed << setfill('0');
						fileName << setw(3) << numberBoardToLoad;
						fileName << "_p.txt";

						outFile << "The player \"" << player.getName() << "\" completed this puzzle in " << player.timeToComplete() << " seconds, and used " << player.getNumHints() << " hints" << endl;

						cout << "You have completed this puzzle in " << player.timeToComplete() << " seconds, and used " << player.getNumHints() << " hints" <<  endl;
						cout << "This information was saved in " << fileName.str() << endl;

					}
					else
					{
						cout << "Some word is not right, you should try to change it..." << endl;
					}

				}

				if (answer == 'N' || answer == 'n')
				{
					validAnswer = true;
				}

				if (!validAnswer)
				cerr << "Invalid answer, try again" << endl;

			} while (!validAnswer);

		}

		if (action == 0)
		{
			cout << "Goodbye" << endl;
		}

	}while (!correctPuzzle);

	return 0;
}
