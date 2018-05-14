//#include "stdafx.h"
#include "board.h"
#include <cassert>
#include <cctype>
#include "utilities.h"
#include "colour_linux.h"
#include "Dictionary.h"

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
	internalDictionary = false;
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
	internalDictionary = false;
}

/**
 * Constructs a Board object by loading an unfinished board from a file.
 * The dictionary pointer is initialised as NULL.
 * <p>
 * Requires a Dictionary to be later associated.
 *
 * @param	filename	Name of the file to import
 */
Board::Board(string filename, bool& control)
{
	ifstream file;
	file.open(filename);
	string inputBuffer;

	getline(file, inputBuffer);
	dictionary = new Dictionary(inputBuffer, control);
	internalDictionary = true;

	getline(file, inputBuffer);

	unsigned int currentLine = 0;
	unsigned int currentColumn = 0;

	getline(file, inputBuffer);

	do
	{
		while (inputBuffer.length() > 0)
		{
			if (isspace(inputBuffer.at(0)))
				inputBuffer.erase(0, 1);
			else if (inputBuffer.at(0) == '.')
			{
				inputBuffer.erase(0, 1);
				currentColumn++;
			}
			else
			{
				addedChars.emplace(stringToUpper(cvtPosNr(currentLine)) + cvtPosNr(currentColumn), inputBuffer.at(0));
				inputBuffer.erase(0, 1);
				currentColumn++;
			}
		}

		currentLine++;
		getline(file, inputBuffer);
	}
	while (inputBuffer.length() > 0);

	number.lines = currentLine;
	number.lines = currentColumn;


	while (getline(file, inputBuffer))
	{
		if (inputBuffer.length() > 0)
		{
			string word, position;
			bool hitSpace = false;

			while(inputBuffer.length() > 0)
			{
				if (!hitSpace)
				{
					if (inputBuffer.at(0) == ' ')
					{
						inputBuffer.erase(0, 1);
						hitSpace = true;
					}
					else
					{
						position.push_back(inputBuffer.at(0));
						inputBuffer.erase(0, 1);
					}
				}
				else
				{
					word.push_back(inputBuffer.at(0));
					inputBuffer.erase(0, 1);
				}
			}

			words.emplace(position, word);
		}
	}
}

//DESTRUCTOR

/**
 * Destructs Board object
 */
Board::~Board()
{
	if (internalDictionary)
		delete dictionary;
}

//PUBLIC MEMBER FUNCTIONS

/**
 * Associates a Dictionary object by its pointer to the Board object.
 *
 * @param	dictionary	Pointer to the Dictionary object
 */
void Board::linkDic(Dictionary* dictionary, bool replace)
{
	if (replace)
		delete this->dictionary;
	this->dictionary = dictionary;
}

/**
 * Removes existing word from the board. Returns -1 if word does not exist, 0 if successful.
 *
 * @param	word	The word to be removed
 * @return			The exit code of the procedure
 */
int Board::remWord(string word)
{
	map<string,string>::iterator wordToRemove = words.end();
	bool found = false;
	for (map<string, string>::iterator it = words.begin(); it != words.end(); it++)
		if (it->second == word)
		{
			found = true;
			wordToRemove = it;
			break;
		}

	if (!found)
		return -1;

	words.erase(wordToRemove);

	refill();

	return 0;
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
		blackout();

	ofstream outp;
	outp.open(filename);

	if (!outp.is_open())
		return -1;

	outp << dictionary->dictName() << '\n';

	outp << '\n';

	for (unsigned int line = 0; line < number.lines; line++)
		for (unsigned int column = 0; column < number.columns; column++)
		{
			if (addedChars.find( stringToUpper(cvtPosNr(line)) + cvtPosNr(column) ) != addedChars.end())
				outp << addedChars.at(stringToUpper(cvtPosNr(line)) + cvtPosNr(column));
			else
				outp << '.';

			if (column == number.columns - 2)
				outp << '\n';
			else
				outp << ' ';
		}

	outp << '\n';

	for (map<string, string>::iterator i = words.begin(); i != words.end(); i++)
		outp << i->first << ' ' << i->second << '\n';

	return 0;
}

/**
* Shows the board on screen.
*/
void Board::show()
{
  //prints column header
  cout << "  ";
  if ((number.lines / 27) > 0)
    cout << ' ';
  setcolor(RED);
  for (unsigned int column = 0; column < number.columns; column++)
    cout << cvtPosNr(column) << ' ';
  cout << endl;

  //prints each row
  for (unsigned int line = 0; line < number.lines; line++)
  {
    setcolor(RED, BLACK_B);
    cout << stringToUpper(cvtPosNr(line));
    if ( ((number.lines / 27) > 0) && (line < 26))
      cout << "  ";
    else
      cout << ' ';

    setcolor(BLACK, WHITE_B);
    cout << ' ';

    for (unsigned int column = 0; column < number.columns; column++)
		{
      if ( ((number.columns / 27) > 0) && (column >= 26))
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
 * Constructs a wilcard for the specified position taking into account
 * possible overlaps. Can also return "0" if no wildcard can be constructed,
 * "-1" if the position is invalid, "-2" if length is too big.
 *
 * @param	position	the position string where it should start generating
 * @returns					wildcard string, or exit code string
 */
string Board::generateWildcard(string position, unsigned int size)
{
	//separates the elements of the position string
	string lineStr, colStr;
	char direction;

	while ((position.length() > 0) ? isupper(position.at(0)) : false)
	{
		lineStr.push_back(position.at(0));
		position.erase(0, 1);
	}

	while ((position.length() > 0) ? islower(position.at(0)) : false)
	{
		colStr.push_back(position.at(0));
		position.erase(0, 1);
	}

	if (position.length() > 0)
		if (isupper(position.at(0)))
			direction = position.at(0);

	//checks whether a valid position was input
	if (position.length() > 0)
		return "-1";
	if (lineStr.length() > 2 || lineStr.length() < 1)
		return "-1";
	if (colStr.length() > 2 || colStr.length() < 1)
		return "-1";
	if (direction != 'V' && direction != 'H')
		return "-1";

	unsigned int firstLine, firstColumn;
	firstLine = cvtPosStr(lineStr);
	firstColumn = cvtPosStr(colStr);

	//checks whether the position is inside the board
	if (firstLine >= number.lines && firstColumn >= number.columns)
		return "-1";

	if (direction == 'V')
	{
		if (firstLine + size < number.lines)
			return "-2";
	}
	else
	{
		if (firstColumn + size < number.columns)
			return "-2";
	}

	for (unsigned int offset = 0; offset < size; offset++)
	{
		if (direction == 'V')
		{
			if (addedChars.find(stringToUpper(cvtPosNr(firstLine + offset)) + cvtPosNr(firstColumn)) != addedChars.end())
				if (addedChars.at(stringToUpper(cvtPosNr(firstLine + offset)) + cvtPosNr(firstColumn)) == '#')
					return "-1";
		}
		else
		{
			if (addedChars.find(stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn + offset)) != addedChars.end())
				if (addedChars.at(stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn + offset)) == '#')
					return "-1";
		}
	}

	if (direction == 'V')
	{
		if (addedChars.find(stringToUpper(cvtPosNr(firstLine + size)) + cvtPosNr(firstColumn)) != addedChars.end())
			if (addedChars.at(stringToUpper(cvtPosNr(firstLine + size)) + cvtPosNr(firstColumn)) != '#')
				return "0";
	}
	else
	{
		if (addedChars.find(stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn + size)) != addedChars.end())
			if (addedChars.at(stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn + size)) != '#')
				return "0";
	}

	string output;

	for (unsigned int offset = 0; offset < size; offset++)
	{
		if (direction == 'V')
		{
			if (addedChars.find(stringToUpper(cvtPosNr(firstLine + offset)) + cvtPosNr(firstColumn)) != addedChars.end())
				output.push_back(addedChars.at(stringToUpper(cvtPosNr(firstLine + offset)) + cvtPosNr(firstColumn)));
			else
				output.push_back('?');
		}
		else
		{
			if (addedChars.find(stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn + offset)) != addedChars.end())
				output.push_back(addedChars.at(stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn + offset)));
			else
				output.push_back('?');
		}
	}

	return output;
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
 * -1: inexistent word;
 * <p>
 * -2: ilegal overlap (different characters, black spaces);
 * <p>
 * -3: lack of space;
 * <p>
 * -4: repeated words;
 * <p>
 * -5: invalid position.
 *
 * @param	position	The position string to insert the word in
 * @param	word		The word to insert
 * @return				The exit code of the procedure
 */
int Board::insWord(string pos, string word)
{
	if (!(dictionary->checkWordDictionary (word)))
		return -1;

	if (words.find(stringToUpper(word)) != words.end())
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
		return -5;
	if (lineStr.length() > 2 || lineStr.length() < 1)
		return -5;
	if (colStr.length() > 2 || colStr.length() < 1)
		return -5;
	if (direction != 'V' && direction != 'H')
		return -5;

	unsigned int firstLine, firstColumn;
	firstLine = cvtPosStr(lineStr);
	firstColumn = cvtPosStr(colStr);

	//checks whether the board is big enough to place the word
	if (firstLine >= number.lines && firstColumn >= number.columns)
		return -5;

	if (direction == 'V')
	{
		if (firstLine + word.length() > number.lines)
			return -3;
	}
	else
	{
		if (firstColumn + word.length() > number.columns)
			return -3;
	}

	map<string, char> charMap; //provisional store of the characters

	//adds a black space before, if needed
	if (direction == 'V')
	{
		if (firstLine > 0)
			charMap.emplace( stringToUpper( cvtPosNr(firstLine - 1)) + cvtPosNr(firstColumn), '#');
	}
	else
	{
		if (firstColumn > 0)
			charMap.emplace( stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn - 1), '#');
	}

	//adds each character in the word
	for (unsigned int offset = 0; offset < word.length(); offset++)
	{
		if (direction == 'V')
			charMap.emplace( stringToUpper(cvtPosNr(firstLine + offset)) + cvtPosNr(firstColumn), stringToUpper(word).at(offset));
		else
			charMap.emplace( stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn + offset), stringToUpper(word).at(offset));
	}

	//adds black space at the end of word, if needed
	if (direction == 'V')
	{
		if (firstLine + word.length() < number.lines)
			charMap.emplace( stringToUpper( cvtPosNr(firstLine - word.length())) + cvtPosNr(firstColumn), '#');
	}
	else
	{
		if (firstColumn + word.length() < number.columns)
			charMap.emplace( stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn + word.length()), '#');
	}

	//checks for illegal overlaps and redundant characters
	for (map<string, char>::iterator it = charMap.begin(); it != charMap.end(); it++)
	{
		if (addedChars.find(it->first) != addedChars.end())
		{
			if (addedChars.at(it->first) != it->second)
				return -2;
			else
				charMap.erase(it);
		}
	}

	for (map<string, char>::iterator it = charMap.begin(); it != charMap.end(); it++)
		addedChars.emplace( it->first, it->second );

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
unsigned int Board::cvtPosStr(string str)
{
	assert(str.length() > 0);
	assert(str.length() <= 2);

	str = stringToLower(str);

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
	for (unsigned int line = 0; line < (this->number.lines); line++)
		for (unsigned int column = 0; column < (this->number.columns); column++)
			if (this->addedChars.find( stringToUpper(cvtPosNr(line)) + cvtPosNr(column) ) == this->addedChars.end())
				this->addedChars.emplace(stringToUpper(cvtPosNr(line)) + cvtPosNr(column), '#');
}

/**
 * Re-does the addedChars map from the existing added words
 */
void Board::refill()
{
	map<string, char> newMap;

	/*
	for (map<string, char>::iterator it = addedChars.begin(); it != addedChars.end(); it++)
	{
		if (it->second == '#')
			newMap.emplace(it->first, '#');
	}
	*/

	//iterates through all position-word pairs
	for (map<string, string>::iterator par = words.begin(); par != words.end(); par++)
	{
		string pos = par->first;
		string word = par->second;

		//separates the elements of the position string
		string lineStr, colStr;
		char direction;

		while (isupper(pos.at(0)))
		{
			lineStr.push_back(pos.at(0));
			pos.erase(0, 1);
		}

		while (islower(pos.at(0)))
		{
			colStr.push_back(pos.at(0));
			pos.erase(0, 1);
		}

		direction = pos.at(0);

		unsigned int firstLine, firstColumn;
		firstLine = cvtPosStr(lineStr);
		firstColumn = cvtPosStr(colStr);

		map<string, char> wordChars; //provisional store of the characters

		//adds position-character pairs to temporary storage
		for (unsigned int offset = 0; offset < word.length(); offset++)
		{
			if (direction == 'V')
				wordChars.emplace( stringToUpper(cvtPosNr(firstLine + offset)) + cvtPosNr(firstColumn), stringToUpper(word).at(offset));
			else
				wordChars.emplace( stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn + offset), stringToUpper(word).at(offset));
		}

		//adds black spaces to temporary storage
		if (direction == 'V')
		{
			if (firstLine > 0)
				wordChars.emplace( stringToUpper(cvtPosNr(firstLine - 1)) + cvtPosNr(firstColumn), '#');

			if (firstLine + word.length() < number.lines)
				wordChars.emplace( stringToUpper(cvtPosNr(firstLine + word.length())) + cvtPosNr(firstColumn), '#');
		}
		else
		{
			if (firstColumn > 0)
				wordChars.emplace( stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn - 1), '#');

			if (firstColumn + word.length() < number.columns)
				wordChars.emplace( stringToUpper(cvtPosNr(firstLine)) + cvtPosNr(firstColumn + word.length()), '#');
		}

		//deletes redundant characters
		for (map<string, char>::iterator it = wordChars.begin(); it != wordChars.end(); it++)
		{
			if (addedChars.find(it->first) != addedChars.end())
			{
				wordChars.erase(it);
			}
		}

		//adds the characters from temporary storage to the new character map
		for (map<string, char>::iterator it = wordChars.begin(); it != wordChars.end(); it++)
			newMap.emplace( it->first, it->second );
	}

	addedChars = newMap;

}
