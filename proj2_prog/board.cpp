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

	for (unsigned int line = 0, line < size.lines, line++)
		for (unsigned int column = 0, column < size.columns, column++)
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

	return 0;
}

/**
* Shows the board on screen.
*/
void Board::show()
{
  //prints column header
  cout << "  "
  if ((size.lines / 27) > 0)
    cout << ' ';
  setcolor(RED);
  for (unsigned int column = 0; column < size.columns; column++)
    cout << cvtPosNr(column) << ' ';
  cout << endl;

  //prints each row
  for (unsigned int line = 0; line < size.lines; line++)
  {
    setcolor(RED, BLACK_B);
    cout << stringToUpper(cvtPosNr(line));
    if ( ((size.lines / 27) > 0) && (line < 26))
      cout << "  ";
    else
      cout << ' ';

    setcolor(BLACK, WHITE_B);
    cout << ' ';

    for (unsigned int column = 0, column < size.columns, column++)
		{
      if ( ((size.columns / 27) > 0) && (column >= 26))
        cout << ' ';

			if (addedChars.find( stringToUpper(cvtPosNr(line)) + cvtPosNr(column) ) != addedChars.end())
      {
        if (addedChars.at(stringToUpper(cvtPosNr(line)) + cvtPosNr(column)) == '#')
          setcolor(WHITE, BLACK_B);

				cout << addedChars.at(stringToUpper(cvtPosNr(line)) + cvtPosNr(column));

        if (addedChars.at(stringToUpper(cvtPosNr(line)) + cvtPosNr(column)) == '#')
          setcolor(BLACK, WHITE_B);
      }
      else
				cout << '.';
		}

    setcolor(DEFAULT_TEXT, DEFAULT_BG);

    cout << endl;

  }
}

/**
 * Tries to insert a word from the dictionary into the board, checking
 * for any ilegal overlap, inexistent words, repeated words, and lack of
 * space. Then updates the black space list.
 * <p>
 * Returns the following exit codes:
 * <p>
 *  0: success;
 * <p>
 * -1: invalid position string;
 * <p>
 * -2: ilegal overlap (different characters, black spaces);
 * <p>
 * -3: lack of space;
 * <p>
 * -4: repeated words.
 *
 * @param	position	The position string to insert the word in
 * @param	word		The word to insert
 * @return				The exit code of the procedure
 */
int insWord(string pos, string word)
{
	if (words.find(stringToUpper(word)) =! words.end())
		return -4;
	
	//separates the elements of the position string
	string lineStr, colStr;
	char direction;

	while ((pos.length() > 0) ? isupper(pos.at(0)) : false)
	{
		lineStr.push_back(pos.at(0));
		pos.erase(0, 1);
	}

	while ((pos.length() > 0) ? islower(pos.at(0)) : false)
	{
		colStr.push_back(pos.at(0));
		pos.erase(0, 1);
	}

	if (pos.length() > 0)
		if (isupper(pos.at(0)))
			direction = pos.at(0);

	//checks whether a valid position was input 
	if (pos.length() > 0)
		return -1;
	if (lineStr.length() > 2 || lineStr.length() < 1)
		return -1;
	if (colStr.length() > 2 || colStr.length() < 1)
		return -1;
	if (direction != 'V' && direction != 'H')
		return -1;

	unsigned int firstLine, firstColumn;
	firstLine = cvtPosStr(lineStr);
	firstColumn = cvtPosStr(colStr);

	//checks whether the board is big enough to place the word
	if (firstLine >= size.lines && firstColumn >= size.columns)
		return -1;

	if (direction == 'V')
		if (firstLine + word.length() > size.lines)
			return -3;
	else
		if (firstColumn + word.length() > size.columns)
			return -3;

	map<string, char> charMap; //provisional store of the characters
	for (unsigned int offset = 0; offset < word.length(); offset++)
	{
		if (direction == 'V')
			charMap.emplace( stringToUpper(cvtPosNr(firstLine + offset)) + cvtPosNr(firstColumn), stringToUpper(word).at(offset));
		else
			charMap.emplace( stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn + offset), stringToUpper(word).at(offset));
	}

	for (map<string, char>::iterator it = charMap.begin(); it != charMap.end(); it++)
	{
		if (addedChars.find(it.first()) != addedChars.end())
		{
			if (addedChars.at(it.first()) != it.second())
				return -2;
			else
				charMap.erase(it);	
		}
	}

	for (map<string, char>::iterator it = charMap.begin(); it != charMap.end; it++)
		addedChars.emplace( it.first(), it.second() );

	words.emplace(pos, stringToUpper(word));

	return 0;
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
 * Re-does the addedChars map from the existing added words
 */
void Board::refill()
{
	map<string, char> newMap;

	for (map<string, char>::iterator it = addedChars.begin(); it != addedChars.end(); it++)
	{
		if (it.second() == '#')
			newMap.emplace(it.first(), '#');
	}

	for (map<string, string>::iterator par = addedChars.begin(); par != words.end(); par++)
	{
		string pos = par.first();
		string word = par.first();

		//separates the elements of the position string
		string lineStr, colStr;
		char direction;

		while ((pos.length() > 0) ? isupper(pos.at(0)) : false)
		{
			lineStr.push_back(pos.at(0));
			pos.erase(0, 1);
		}

		while ((pos.length() > 0) ? islower(pos.at(0)) : false)
		{
			colStr.push_back(pos.at(0));
			pos.erase(0, 1);
		}

		if (pos.length() > 0)
			if (isupper(pos.at(0)))
			direction = pos.at(0);

		unsigned int firstLine, firstColumn;
		firstLine = cvtPosStr(lineStr);
		firstColumn = cvtPosStr(colStr);

		map<string, char> wordChars; //provisional store of the characters
		for (unsigned int offset = 0; offset < word.length(); offset++)
		{
			if (direction == 'V')
				wordChars.emplace( stringToUpper(cvtPosNr(firstLine + offset)) + cvtPosNr(firstColumn), stringToUpper(word).at(offset));
			else
				wordChars.emplace( stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn + offset), stringToUpper(word).at(offset));
		}

		for (map<string, char>::iterator it = wordChars.begin(); it != wordChars.end(); it++)
		{
			if (addedChars.find(it.first()) != addedChars.end())
			{
				wordChars.erase(it);	
			}
		}

		for (map<string, char>::iterator it = charMap.begin(); it != charMap.end; it++)
			newMap.emplace( it.first(), it.second() );
	}

	addedChars = newMap;

}
		
		