#include "board.h"
#include "Dictionary.h"
#include "utilities.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cctype>
#ifdef _WIN32
const std::string eofkey = "Ctrl + Z";
#include "colour_windows.h"
#else
const std::string eofkey = "Ctrl + D";
#include "colour_linux.h"
#endif

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

string boardFileName()
{
	ostringstream outputName;

	for (int i = 1; i < 1000; i++)
	{
		outputName << "B";
		outputName << fixed << setfill('0');
		outputName << setw(3) << i;
		outputName << ".txt";

		ifstream fileNameTest(outputName.str());

		if (fileNameTest.is_open())
		{
			fileNameTest.close();
			outputName.str("");
			outputName.clear();
		}
		else
			break;
	}

	return outputName.str();
}

int numberOf(string rowType)
{
	bool good = false;
	int rows;

	cout << "How many " << rowType << " should the board have?" << endl;

	do
	{
		rows = readInt("Invalid input. Please input the number of " + rowType + " in the board (1 to 702).\nYour input: ");
		if (rows < 1 || rows > 702)
		{
			cout << "Invalid input. The board should have between 1 and 702 " << rowType << ". Please try again" << endl;
			cout << "Your input: ";
		}
		else
			good = true;
	} while (!good);

	return rows;
}

void createPuzzle()
{
	int lines = numberOf("lines");
	int columns = numberOf("columns");// Lines/Columns = number of lines/columns
	string filename;
	bool error = false; //Variable used to check if any errors opening the dictionary happened

	cout << "Insert dictionary file name:" << endl;
	filename = readString("Please input something.\nYour input: ");

	Dictionary synonyms(filename, error);

	while (error)
	{
		cout << "Error opening dictionary. Does the file exist?" << endl;

		cout << "Insert dictionary file name:" << endl;
		filename = readString("Please input something.\nYour input: ");

		synonyms = Dictionary(filename, error);
	}

	if (!error)
	{
		Board board(lines, columns, &synonyms); //Creates empty board with the given dimentions and a dictionary associated

		while (true)
		{
			string input; // Contains action entered by user
			string word; // Contains the word entered by the user
			bool validInput = false; // Used to make the program "robust to invalid inputs"

			board.show();

			cout << "Enter Position (LcD / CTRL + Z = Save and Exit / 0 = Exit)" << endl;
			cin >> input;

			if (cin.eof())
			{
				cout << "Press Enter to continue ";
				cin.clear();
				cin.ignore(100000, '\n');

				char answer;
				bool validAnswer = false;

				cout << "Do you want to save the board to resume it later? (Y/N)" << endl;

				do {

					cin >> answer;

					if (answer == 'Y' || answer == 'y')
					{
						string fileName = boardFileName();
						char answer2;
						bool validAnswer2 = false;

						cout << "Is the board finished? (Y/N)" << endl;

						do {

							cin >> answer2;

							if (answer2 == 'y' || answer2 == 'Y')
							{
								validAnswer2 = true;
								board.save(fileName, true);
								cout << "Board successfully saved as \"" << fileName << "\"" << endl;
							}
							else if (answer2 == 'n' || answer2 == 'N')
							{
								validAnswer2 = true;
								board.save(fileName, false);
								cout << "Board successfully saved as \"" << fileName << "\"" << endl;
							}
							else
							{
								cerr << "Invalid answer, try again" << endl;
								cout << "Y = Yes" << endl;
								cout << "N = No" << endl;
							}

						} while (!validAnswer2);

						validAnswer = true;
					}
					else if (answer == 'N' || answer == 'n')
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

			do {

				cout << "Enter Word (- = remove / ? = help / 0 = exit)" << endl;
				cout << "You can also get some words to help by entering \"Word?\"" << endl;

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
					string pos;
					cout << "Enter the position of the word you want to delete" << endl;
					cin >> pos;

					if (board.remWord(pos) == -1)
						cerr << "There is no word in such position" << endl;

				}
				else if (word == "Word?" || word == "word?")
				{
					string position;
					int size;

					validInput = true;

					cout << "Enter the position you want to insert the word (LcD)" << endl;
					cin >> position;

					cout << "Enter the size of the word" << endl;

					do
					{
						cin >> size;

						if (size < 0)
						{
							cerr << "Size of word is to small, enter a greater number" << endl;
						}

					} while (size < 1);


					vector <string> possibleWords = synonyms.getPossibleWords(board.generateWildcard(position, size));
					//Contains every word in the dictionary file that has <size> number of chars and can be inserted in <position> of the board

					cout << "Possible words: " << endl;
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
					//Prints every word usable in the previous case
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

				cout << "Enter Position (LcD / CTRL + Z = Save and Exit / 0 = Exit) ";
				cin >> input;

				if (cin.eof())
				{
					cout << "Press Enter to continue ";
					cin.clear();
					cin.ignore(100000,'\n');

					char answer;
					bool validAnswer = false;

					cout << "Do you want to save the board to resume it later? (Y/N)" << endl;

					do {

						cin >> answer;

						if (answer == 'Y' || answer == 'y')
						{
							string fileName = boardFileName();
							char answer2;
							bool validAnswer2 = false;

							cout << "Is the board finished? (Y/N)" << endl;

							do {

								cin >> answer2;

								if (answer2 == 'y' || answer2 == 'Y')
								{
									validAnswer2 = true;
									board.save(fileName, true);
									cout << "Board successfully saved as \"" << fileName << "\"" << endl;
								}
								else if (answer2 == 'n' || answer2 == 'N')
								{
									validAnswer2 = true;
									board.save(fileName, false);
									cout << "Board successfully saved as \"" << fileName << "\"" << endl;
								}
								else
								{
									cerr << "Invalid answer, try again" << endl;
									cout << "Y = Yes" << endl;
									cout << "N = No" << endl;
								}

							} while (!validAnswer2);

							validAnswer = true;
						}
						else if (answer == 'N' || answer == 'n')
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
						string pos;
						cout << "Enter the position of the word you want to delete" << endl;
						cin >> pos;

						if (board.remWord(pos) == -1)
							cerr << "There is no word in such position" << endl;
					}
					else if (word == "Word?" || word == "word?")
					{
						string position;
						int size;

						cout << "Enter the position you want to insert the word (LcD)" << endl;
						cin >> position;

						cout << "Enter the size of the word you want to insert" << endl;

						do
						{
							cin >> size;

							if (size < 0)
								cerr << "Invalid size, please enter a number greater than 0" << endl;

						} while (size < 0);


						vector <string> possibleWords = board.getDicPointer()->getPossibleWords(board.generateWildcard(position, size));

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
