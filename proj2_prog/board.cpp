#include "stdafx.h"
#include "board.h"
#include <cassert>
#include <cctype>
#include "utilities.h"

using namespace std;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *                       BOARD CLASS - IMPLEMENTATION                          *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//CONSTRUCTORS

/**
 * Constructs a Board object without associating any Dictionary to it.
 * The dictionary pointer is initialised as NULL.
 * <p>
 * Requires that a Dictionary is later added using the linkDictionary
 * procedure.
 *
 * @param	lines	The number of lines the board will have
 * @param	columns	The number of columns in the board will have
 */
Board::Board(unsigned int lines, unsigned int columns)
{
	this->number.lines = lines;
	this->number.columns = columns;
	dictionary = NULL;
}

/**
 * Constructs a Board object and associates a Dictionary to it.
 *
 * @param	lines		The number of lines the board will have
 * @param	columns		The number of columns in the board will have
 * @param	dictionary	Pointer to the Dictionary object
 */
Board::Board(unsigned int lines, unsigned int columns, Dictionary* dictionary)
{
	this->number.lines = lines;
	this->number.columns = columns;
	this->dictionary = dictionary;
}

//PUBLIC MEMBER FUNCTIONS

/**
 * Associates a Dictionary object by its pointer to the Board object.
 *
 * @param	dictionary	Pointer to the Dictionary object
 */
void Board::linkDic(Dictionary* dictionary)
{
	this->dictionary = dictionary;
}

//PRIVATE MEMBER FUNCTIONS

/**
 * Returns a string "a" to "zz" correspoding to a number up to 26^2 + 25.
 *
 * @param	number	In range [0, 26^2 + 25]
 * @return			String from "a" to "zz"
 */
string Board::cvtPosNr(unsigned int number)
{
	assert(number >= 0);
	assert(number <= (26*26 + 25));
	if ((number / 26) == 0)
	{
		string output;
		output.push_back(char(int('a') + number));
		return output;
	}
	else
	{
		string output;
		output.push_back(char(int('a') + number / 26 - 1));
		output.push_back(char(int('a') + number % 26));
		return output;
	}
}

/**
 * Returns a number up to 26^2 - 1 corresponding to a string
 * from "a" to "zz".
 *
 * @param	string	From "a" to "zz"
 * @return			Number in range [0, 26^2 - 1]
 */
unsigned int Board::cvtPosStr(const string& str)
{
	assert(str.length() > 0);
	assert(str.length() <= 2);
	
	for (int i = 0; i < str.length(); i++)
		tolower(str[i]);
	
	if (str.length() == 1)
		return int(str[0]) - int ('a');
	else
	{
		unsigned int rightChar = int(str[1]) - int ('a');
		unsigned int leftChar = int(str[0]) - int ('a');
		return rightChar + 26*(leftChar + 1);
	}
}

/**
 * Fills all empty spaces with black spaces
 */
void Board::blackout()
{
	for (unsigned int line = 0, line < (this->size.lines), line++)
		for (unsigned int column = 0, column < (this->size.columns), column++);
			if (this->addedChars.find( stringToUpper(cvtPosNr(line)) + cvtPosNr(column) ) == this->addedChars.end())
				this->addedChars.emplace(stringToUpper(cvtPosNr(line)) + cvtPosNr(column), '#');
}
				
	
/**
 * Saves the board to a file, returning 0 if sucessful and -1 if not.
 *
 * @param	filename	Name of the file to store the board in
 * @param	finished	Determines whether to save board as finished
 * @returns				Exit code
 */
int Board::save(string filename, bool finished)
{
	if (finished)
		this->blackout();
	
	ofstream outp;
	outp.open(filename);

	if (!outp.is_open())
		return -1;

	outp << this->dictionary->dictName() << '\n';
	
	outp << '\n';

	for (unsigned int line = 0, line < (this->size.lines), line++)
		for (unsigned int column = 0, column < (this->size.columns), column++)
		{
			if (this->addedChars.find( stringToUpper(cvtPosNr(line)) + cvtPosNr(column) ) != this->addedChars.end())
				outp << this->addedChars.at(stringToUpper(cvtPosNr(line)) + cvtPosNr(column));
			else
				outp << '.';
			
			if (column == columns - 2)
				outp << '\n';
			else
				outp << ' ';
		}

	outp << '\n';

	for (map<string, string>::iterator i = this->words.begin(); i != this->words.end(); i++)
		outp << i->first << ' ' << i->second << '\n';
}
