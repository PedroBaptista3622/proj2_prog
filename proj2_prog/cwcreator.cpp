#include "stdafx.h"
#include "board.h"
#include "Dictionary.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


//MISSING CTRL + Z STUFF *-*

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
	unsigned int lines, columns; // xLenght = horizontal length of board, yLength = vertical length of board
	string filename;

	cout << "Insert size of board (lines and then columns)" << endl;
	cin >> lines >> columns;
	cout << "Insert dictionary file name" << endl;
	cin >> filename;

	Dictionary synonyms(filename);
	Board board(lines, columns, &synonyms); //Creates empty board with the given dimentions and a dictionary associated

	while (true)
	{
		string input; // Contains commands entered by user
		string word; // Contains the word entered by the user

		board.show();

		cout << "Enter Position (LcD / 0 = exit)";
		cin >> input;

		if (input == "0")
			break;

		cout << "Enter Word (- = remove / ? = help / 0 = exit)";
		cout << "You can also get some words to help by entering \"Word?\"" << endl;
		cin >> word;

		if (input == "0")
		{
			break;
		}
		else if (input == "?")
		{
			printInputHelp();
		}
		else if (word == "-")
		{
			input.clear();
			cout << "Enter Position (LcD / 0 = exit)";
			cin >> input;
			// DELETE WORD FUNCTION MISSING
		}
		else if (word == "Word?" || word == "word?")
		{
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
				board.show();
				break;

			case -1:
				cerr << "Word doesn't exist" << endl;
				break;

			case -2:
				cerr << "Ilegal Overlap" << endl;
				break;

			case -3:
				cerr << "Lack of Space" << endl;
				break;

			case -4:
				cerr << "Repeated Words" << endl;
				break;
			}

		}

	}
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
			//MISSING STUFF
		}
		else if (action == 0)
		{
			validAction = true;
		}
		else
		{
			cout << "Invalid Input" << endl;
		}

	} while (!validAction);

	return 0;
}