#ifdef _WIN32
#include "stdafx.h"
#endif
#include "board.h"

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
 * <p>
 * Allocates and constructs internal dictionary with imported filename.
 *
 * @param	filename	Name of the file to import
 * @param	control		Variable to store sucess state of the dictionary
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
		currentColumn = 0;

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
	number.columns = currentColumn;


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

Dictionary* Board::getDicPointer()
{
	return dictionary;
}

/**
 * Removes existing word from the board. Returns -1 if no word in position,
 * 0 if successful.
 * @param	word	The word to be removed
 * @return			The exit code of the procedure
 */

int Board::remWord(string position) //TODO
{
	if (words.find(position) == words.end())
		return -1;

	//separates the elements of the position string
	wordPosition pos = separateWordPos(position);

	//removes the black spaces at the end
	removeBlackSpaces(pos, words.at(position).length());

	//removes word from word list
	words.erase(words.find(position));

	addBlackSpaces();

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

			if (column == number.columns - 1)
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
  cout << "   ";
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
    //cout << ' ';

    for (unsigned int column = 0; column < number.columns; column++)
		{
			if ( ((number.columns / 27) > 0) && (column >= 26))
				cout << ' ';

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
	wordPosition pos = separateWordPos(position);
	if (!wordPosInBoard(pos))
		return "-1";

	if(!wordFits(pos, size))
		return "-2";

	string output;

	for (unsigned int offset = 0; offset < size; offset++)
	{
		if (pos.direction == 'V')
		{
			if (addedChars.find(stringToUpper(cvtPosNr(pos.line + offset)) + cvtPosNr(pos.column)) != addedChars.end())
				output.push_back(addedChars.at(stringToUpper(cvtPosNr(pos.line + offset)) + cvtPosNr(pos.column)));
			else
				output.push_back('?');
		}
		else
		{
			if (addedChars.find(stringToUpper(cvtPosNr(pos.line)) + cvtPosNr(pos.column + offset)) != addedChars.end())
				output.push_back(addedChars.at(stringToUpper(cvtPosNr(pos.line)) + cvtPosNr(pos.column + offset)));
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
		return -1; //inexistent word

	if (words.find(stringToUpper(word)) != words.end())
		return -4; //repeated word

	wordPosition position = separateWordPos(pos);

	if (!wordPosInBoard(position))
		return -5; //invalid position



	if (!wordFits(position, word.length()))
		return -3; //word does not fit

	map<string, char> charMap = tempMap(position, word);



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

	//adds non-redundant characters
	for (map<string, char>::iterator it = charMap.begin(); it != charMap.end(); it++)
		addedChars.emplace( it->first, it->second );

	//adds new black spaces
	addBlackSpaces();

	//adds word to list
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

bool Board::validPosStr(string str)
{
	if (str.length() > 2 || str.length() < 1)
		return false;

	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (!isalpha(str.at(i)))
			return false;
	}

	return true;
}

/**
 * Fills all empty spaces with black spaces
 */
void Board::blackout()
{
	for (unsigned int line = 0; line < (this->number.lines); line++)
		for (unsigned int column = 0; column < (this->number.columns); column++)
		{
			charPosition pos;
				pos.line = line;
				pos.column = column;
				pos.valid = true;
			if (addedChars.find(charPosString(pos)) == addedChars.end())
				addedChars.emplace(charPosString(pos), '#');
		}
}

/**
 * Re-does the addedChars map from the existing added words
 */
void Board::refill() //TODO
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
		wordPosition position = separateWordPos(par->first);
		string word = par->second;


		map<string, char> wordChars = tempMap(position, word); //provisional store of the characters

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

	addBlackSpaces();

}

void Board::addBlackSpaces()
{
	for (map<string,string>::iterator it; it != words.end(); it++)
	{
		wordPosition position = separateWordPos(it->first);
		string word = it->second;

		charPosition before, after;
		if (position.direction == 'V')
		{
			before.line = position.line - 1;
			before.column = position.column;
			before.valid = true;

			after.line = position.line + word.length();
			after.column = position.column;
			after.valid = true;
		}
		else
		{
			before.line = position.line;
			before.column = position.column - 1;
			before.valid = true;

			after.line = position.line;
			after.column = position.column + word.length();
			after.valid = true;
		}

		if (charPosInBoard(before))
		{
			if (addedChars.find(charPosString(before)) == addedChars.end())
				addedChars.emplace(charPosString(before), '#');
		}
		if (charPosInBoard(after))
		{
			if (addedChars.find(charPosString(after)) == addedChars.end())
				addedChars.emplace(charPosString(after), '#');
		}
	}
}

void Board::removeBlackSpaces(const wordPosition& position, unsigned int length)
{
	charPosition before, after;
	if (position.direction == 'V')
	{
		before.line = position.line - 1;
		before.column = position.column;
		before.valid = true;

		after.line = position.line + length;
		after.column = position.column;
		after.valid = true;
	}
	else
	{
		before.line = position.line;
		before.column = position.column - 1;
		before.valid = true;

		after.line = position.line;
		after.column = position.column + length;
		after.valid = true;
	}
	if (charPosInBoard(before))
		addedChars.erase(addedChars.find(charPosString(before)));
	if (charPosInBoard(after))
		addedChars.erase(addedChars.find(charPosString(after)));

}

Board::wordPosition Board::separateWordPos(string position)
{
	wordPosition output;
	output.valid = true;

	string lineStr, colStr;
	char direction = 0;

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
	{
		direction = position.at(0);
		position.erase(0, 1);
	}

	//checks whether a valid position was input
	if (position.length() > 0)
		output.valid = false;

	if (!validPosStr(lineStr) || !validPosStr(colStr))
		output.valid = false;

	if (direction != 'V' && direction != 'H')
		output.valid = false;

	if (output.valid)
	{
		output.line = cvtPosStr(lineStr);
		output.column = cvtPosStr(colStr);
		output.direction = direction;
	}
	else
	{
		output.line = 0;
		output.column = 0;
		output.direction = 0;
	}

	return output;
}

Board::charPosition Board::separateCharPos(string position)
{
	charPosition output;

	string lineStr, colStr;

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

	//checks whether a valid position was input
	if (position.length() > 0)
		output.valid = false;

	if (!validPosStr(lineStr) || !validPosStr(colStr))
		output.valid = false;

	if (output.valid)
	{
		output.line = cvtPosStr(lineStr);
		output.column = cvtPosStr(colStr);
	}
	else
	{
		output.line = 0;
		output.column = 0;
	}

	return output;
}

string Board::wordPosString(const wordPosition& position)
{
	assert(position.valid);
	string line, column;

	line = stringToUpper(cvtPosNr(position.line));
	column = cvtPosNr(position.column);

	string output = line + column;
	output.push_back(position.direction);
	return output;
}

string Board::charPosString(const charPosition& position)
{
	assert(position.valid);
	string line, column;

	line = stringToUpper(cvtPosNr(position.line));
	column = cvtPosNr(position.column);

	string output = line + column;
	return output;
}

bool Board::wordPosInBoard(const wordPosition& position)
{
	if (!position.valid)
		return false;

	bool output;
	output = (position.line >= 0 && position.column >= 0);
	output = output && (position.line < number.lines && position.column < number.columns);
	return output;
}

bool Board::charPosInBoard(const charPosition& position)
{
	if (!position.valid)
		return false;

		bool output;
		output = (position.line >= 0 && position.column >= 0);
		output = output && (position.line < number.lines && position.column < number.columns);
		return output;
}

bool Board::wordFits(const wordPosition& position, unsigned int length)
{
	if (!wordPosInBoard(position))
		return false;

	//can the word fit in the board?
	if (position.direction == 'V')
	{
		if (position.line + length > number.lines)
			return false;
	}
	else
	{
		if (position.column + length > number.columns)
			return false;
	}

	//is there a constrain put in by other words?
	charPosition before, after;
	if (position.direction == 'V')
	{
		before.line = position.line - 1;
		before.column = position.column;
		before.valid = true;

		after.line = position.line + length;
		after.column = position.column;
		after.valid = true;
	}
	else
	{
		before.line = position.line;
		before.column = position.column - 1;
		before.valid = true;

		after.line = position.line;
		after.column = position.column + length;
		after.valid = true;
	}

	if (charPosInBoard(before))
	{
		if (addedChars.find(charPosString(before)) != addedChars.end())
			if (addedChars.at(charPosString(before)) != '#')
				return false;
	}
	if (charPosInBoard(after))
	{
		if (addedChars.find(charPosString(after)) != addedChars.end())
			if (addedChars.at(charPosString(after)) != '#')
				return false;
	}

	return true;
}

map<string,char> Board::tempMap(const wordPosition& position, string word)
{
	map<string,char> output;

	for (unsigned int offset = 0; offset < word.length(); offset++)
	{
		charPosition letter;
		if (position.direction == 'V')
		{
			letter.line = position.line + offset;
			letter.column = position.column;
			letter.valid = true;
		}
		else
		{
			letter.line = position.line;
			letter.column = position.column + offset;
			letter.valid = true;
		}

		output.emplace(charPosString(letter), word.at(offset));
	}

	return output;
}
