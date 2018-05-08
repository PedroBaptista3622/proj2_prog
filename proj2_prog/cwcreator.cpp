#include "stdafx.h"
#include "board.h"
#include "Dictionary.h"
#include <iostream>
#include <string>

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
		cin >> word;

		if (input == "0")
			break;

		if (word == "-")
		{
			input.clear();
			cout << "Enter Position (LcD / 0 = exit)";
			cin >> input;
			// DELETE WORD FUNCTION MISSING
		}

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

int main()
{
	int action; // Contains entered action (1=Create Puzzle, 2=Resume Puzzle, 0=Exit)
	
	printLogo();
	printPossibleActions();
	cout << "LcD stands for line column and direction" << endl;

	if (action == 1)
	{
		createPuzzle();
	}

	if (action == 2)
	{

	}



	return 0;
}