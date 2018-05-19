#include "stdafx.h"
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


int main()
{
	int numberBoardToLoad;
	bool validBoardNumber = false;
	ostringstream boardFileName;
	ifstream inFileTest;
	bool errorOpeningFile = false;
	

	printLogo();

		cout << "Please enter the number of the board you want to load (0 to 999)" << endl;

		do
		{
			cin >> numberBoardToLoad;

			if ((numberBoardToLoad > -1) && (numberBoardToLoad <= 999))
			{

				boardFileName << "B";
				boardFileName << fixed << setfill('0');
				boardFileName << setw(3) << numberBoardToLoad;
				boardFileName << ".txt";

				inFileTest.open(boardFileName.str());

				if (inFileTest.is_open())
				{
					validBoardNumber = true;
				}
				else
				{
					boardFileName.str("");
					boardFileName.clear();


					cout << "Board with number " << numberBoardToLoad << " doesn't exist, try another one" << endl;

					cin.ignore(999999, '\n');
					cin.clear();
				}

			}
			else
			{
				cout << "Board number out of boundaries (Min: 0 Max: 999), try a different number" << endl;
			}



		} while (!validBoardNumber);


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

	cin.ignore(999999, '\n');
	cin.clear();
	
	do
	{
		getline(cin, playerName);

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
				cin.ignore(999999, '\n');
				cin.clear();
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
	int action;
	bool correctPuzzle = false;

	player.start();
	
	do
	{
		do
		{
			puzzle.showPuzzle();
			puzzle.showSynonyms();

			cin.ignore(999999, '\n');
			cin.clear();

			cout << "Select action:" << endl;
			cout << "1 - Guess a word" << endl;
			cout << "2 - Delete word from board" << endl;
			cout << "0 - Exit" << endl;
			cout << "Note: If you exit before completing the puzzle correctly the progress will be lost" << endl;

			do
			{
				cin >> action;


				if (action < 0 || action > 2)
				{
					cerr << "Invalid action, try again" << endl;
				}

			} while (action < 0 || action > 2);
			//Takes care of actions. Only accepts actions = 0, 1 or 2.

			cin.ignore(999999, '\n');
			cin.clear();

			if (action == 1)
			{
				cout << "Enter the position you want to guess (LcD)" << endl;
				cin >> position;

				do
				{
					cout << "Enter the guess word" << endl;
					cout << "You can also get some help by entering \'?\'" << endl;
					cin >> guess;


					if (guess == "?")
					{
						cout << "Hint: " << puzzle.anotherHint(position) << endl;
						player.gotHint();
					}
					else
					{
						if (guessWord(&puzzle, position, guess) == 0)
							validGuess = true;

						if (!validGuess)
						{
							cout << "Try another word" << endl;
						}
					}

				} while (!validGuess);

				// WORKING ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			}
			else if (action == 2)
			{
				
				string position;
				bool validPosition = false;

				cout << "Enter the position of the word you want to remove" << endl;

				do
				{
					cin >> position;

					if (puzzle.remGuess(position) == 0)
					{
						validPosition = true;
					}
					else
					{
						cerr << "No word in such position, enter another one" << endl;
					}

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
			return 0;
		}

	}while (!correctPuzzle);

	return 0;
}
