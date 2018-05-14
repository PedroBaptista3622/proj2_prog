//#include "stdafx.h"
#include "board.h"
#include "Dictionary.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printLogo()
{
	cout << "-----------------------------------" << endl;
	cout << "-------- Cross Word Creator -------" << endl;
	cout << "-----------------------------------" << endl;
}
// To be changed

void printPossibleActions()
{
	cout << endl;
	cout << "Possible Actions:" << endl;
	cout << "1 - Create Puzzle" << endl << "2 - Resume Puzzle" << endl << "0 - Exit" << endl;
}

void printInputHelp()
{
	cout << "Input type: LcD" << endl;
	cout << "Examples:" << endl;
	cout << "BaH is used to add a word horizontally starting in the line B and column a" << endl;
	cout << "AcV is used to add a word vertically starting in the line A and column c" << endl;
}

void createPuzzle()
{
	unsigned int lines, columns; // Lines/Columns = number of lines/columns
	string filename;
	bool error = false; //Variable used to check if any errors opening the dictionary happened

	cout << "Insert size of board (lines and then columns)" << endl;
	cin >> lines >> columns;
	cout << "Insert dictionary file name" << endl;
	cin >> filename;

	Dictionary synonyms(filename, error);

	if (!error)
	{
		Board board(lines, columns, &synonyms); //Creates empty board with the given dimentions and a dictionary associated

		while (true)
		{
			string input; // Contains action entered by user
			string word; // Contains the word entered by the user
			bool validInput = false; // Used to make the program "robust to invalid inputs"

			board.show();

			cout << "Enter Position (LcD / CTRL + Z = Save and Exit / 0 = Exit)";
			cin >> input;

			if (cin.eof())
			{
				char answer;
				bool validAnswer = false;

				cout << "Do you want to save the board to resume it later? (Y/N)" << endl;

				do {

					cin >> answer;

					if (answer == 'Y')
					{
						string fileName;
						char answer2;
						bool validAnswer2 = false;

						cout << "Enter the name of the file to store the board in" << endl;
						cin >> fileName;

						cout << "Is the board finished? (Y/N)" << endl;

						do {

							cin >> answer2;

							if (answer2 == 'y' || answer2 == 'Y')
							{
								validAnswer2 = true;
								board.save(fileName, true);
							}
							else if (answer2 == 'n' || answer2 == 'N')
							{
								validAnswer2 = true;
								board.save(fileName, false);
							}
							else
							{
								cerr << "Invalid answer, try again" << endl;
							}

						} while (!validAnswer2);
						
						validAnswer = true;
					}
					else if (answer == 'N')
					{
						validAnswer = true;
					}
					else
					{
						cout << "Invalid answer, try again" << endl;
					}

				} while (!validAnswer);

				if (answer == 'Y' || answer == 'N')
					break;
			}
			else if (input == "0")
			{
				break;
			}

			cout << "Enter Word (- = remove / ? = help / 0 = exit)";
			cout << "You can also get some words to help by entering \"Word?\"" << endl;
			
			do {

				cin >> word;

				if (input == "0")
				{
					validInput = true;
					break;
				}
				else if (input == "?")
				{
					validInput = true;
					printInputHelp();
				}
				else if (word == "-")
				{
					validInput = true;
					string wordToRemove;
					cout << "Enter the word you want to delete" << endl;
					cin >> wordToRemove;

					if (board.remWord(wordToRemove) == -1)
						cerr << "Entered word does not exist" << endl;

				}
				else if (word == "Word?" || word == "word?")
				{
					validInput = true;
					cout << "Possible words: " << endl;

					vector <string> possibleWords = synonyms.getPossibleWords(/*MISSING SEARCH PARAMETER*/);

					for (int i = 0; i < possibleWords.size(); i++)
					{
						if (i == possibleWords.size() - 1)
						{
							cout << possibleWords.at(i) << endl;
						}
						else
						{
							cout << possibleWords.at(i) << ", ";
						}
					}
				}
				else
				{

					switch (board.insWord(input, word))
					{
					case 0:
						validInput = true;
						board.show();
						break;

					case -1:
						cerr << "Word doesn't exist, try again" << endl;
						break;

					case -2:
						cerr << "Ilegal Overlap, try again" << endl;
						break;

					case -3:
						cerr << "Lack of Space, try a smaller word" << endl;
						break;

					case -4:
						cerr << "Repeated Words, try another one" << endl;
						break;

					case -5:
						cerr << "Invalid Position" << endl;
						break;
					}

				}

			} while (!validInput);
		}
	}

}

void resumePuzzle()
{
	string nameOfFile;
	bool errorOpeningFile = false;

	cout << "Enter the name of the file that contains the board you want to load" << endl;

	do
	{
		cin >> nameOfFile;

		Board board(nameOfFile, errorOpeningFile);

		if (errorOpeningFile)
		{
			cerr << "Error Opening File, try again" << endl;
		}
		else
		{
			while (true)
			{
				string input; // Contains action entered by user
				string word; // Contains the word entered by the user
				bool validInput = false; // Used to make the program "robust to invalid inputs"

				board.show();

				cout << "Enter Position (LcD / CTRL + Z = Save and Exit / 0 = Exit)";
				cin >> input;

				if (cin.eof())
				{
					char answer;
					bool validAnswer = false;

					cout << "Do you want to save the board to resume it later? (Y/N)" << endl;

					do {

						cin >> answer;

						if (answer == 'Y')
						{
							string fileName;
							char answer2;
							bool validAnswer2 = false;

							cout << "Enter the name of the file to store the board in" << endl;
							cin >> fileName;

							cout << "Is the board finished? (Y/N)" << endl;

							do {

								cin >> answer2;

								if (answer2 == 'y' || answer2 == 'Y')
								{
									validAnswer2 = true;
									board.save(fileName, true);
								}
								else if (answer2 == 'n' || answer2 == 'N')
								{
									validAnswer2 = true;
									board.save(fileName, false);
								}
								else
								{
									cerr << "Invalid answer, try again" << endl;
								}

							} while (!validAnswer2);

							validAnswer = true;
						}
						else if (answer == 'N')
						{
							validAnswer = true;
						}
						else
						{
							cout << "Invalid answer, try again" << endl;
						}

					} while (!validAnswer);

					if (answer == 'Y' || answer == 'N')
						break;
				}
				else if (input == "0")
				{
					break;
				}

				cout << "Enter Word (- = remove / ? = help / 0 = exit)";
				cout << "You can also get some words to help by entering \"Word?\"" << endl;

				do {

					cin >> word;

					if (input == "0")
					{
						validInput = true;
						break;
					}
					else if (input == "?")
					{
						validInput = true;
						printInputHelp();
					}
					else if (word == "-")
					{
						validInput = true;
						string wordToRemove;
						cout << "Enter the word you want to delete" << endl;
						cin >> wordToRemove;

						if (board.remWord(wordToRemove) == -1)
							cerr << "Entered word does not exist" << endl;

					}
					else if (word == "Word?" || word == "word?")
					{
						validInput = true;
						cout << "Possible words: " << endl;

						vector <string> possibleWords = synonyms.getPossibleWords(/*MISSING SEARCH PARAMETER*/);

						for (int i = 0; i < possibleWords.size(); i++)
						{
							if (i == possibleWords.size() - 1)
							{
								cout << possibleWords.at(i) << endl;
							}
							else
							{
								cout << possibleWords.at(i) << ", ";
							}
						}
					}
					else
					{

						switch (board.insWord(input, word))
						{
						case 0:
							validInput = true;
							board.show();
							break;

						case -1:
							cerr << "Word doesn't exist, try again" << endl;
							break;

						case -2:
							cerr << "Ilegal Overlap, try again" << endl;
							break;

						case -3:
							cerr << "Lack of Space, try a smaller word" << endl;
							break;

						case -4:
							cerr << "Repeated Words, try another one" << endl;
							break;

						case -5:
							cerr << "Invalid Position" << endl;
							break;
						}

					}

				} while (!validInput);
			}
		}

	} while (errorOpeningFile);
	
	/*


	MISSING DICTIONARY ASSOCIATION


	*/


	}



int main()
{
	int action; // Contains entered action (1=Create Puzzle, 2=Resume Puzzle, 0=Exit)
	bool validAction = false;

	printLogo();
	printPossibleActions();
	cout << "LcD stands for line column and direction" << endl;

	do 
	{
		cin >> action;

		if (action == 1)
		{
			validAction = true;
			createPuzzle();
		}
		else if (action == 2)
		{
			validAction = true;
			resumePuzzle();
			//MISSING STUFF
		}
		else if (action == 0)
		{
			validAction = true;
		}
		else
		{
			cout << "Invalid Input, try again" << endl;
		}

	} while (!validAction);

	return 0;
}