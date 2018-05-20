#include "board.h"

using namespace std;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *                          board.h - IMPLEMENTATION                           *
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
Board::Board(int lines, int columns)
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
Board::Board(int lines, int columns, Dictionary* dictionary)
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

	int currentLine = 0;
	int currentColumn = 0;

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

/**
 * Returns a copy of the dictionary pointer.
 * @return	A copy of the dictionary pointer.
 */
Dictionary* Board::getDicPointer() const
{
	return dictionary;
}

/**
 * Removes existing word from the board. Returns -1 if no word in position,
 * 0 if successful.
 * @param	word	The word to be removed
 * @return			The exit code of the procedure
 */
int Board::remWord(string position)
{
	if (words.find(position) == words.end())
		return -1;

	//separates the elements of the position string
	wordPosition pos(position);

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

	for (int line = 0; line < number.lines; line++)
		for (int column = 0; column < number.columns; column++)
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
void Board::show() const
{
  //prints column header
  cout << "   ";
  if ((number.lines / 27) > 0)
    cout << ' ';
  setcolor(RED);
  for (int column = 0; column < number.columns; column++)
    cout << cvtPosNr(column) << ' ';
  cout << endl;

  //prints each row
  for (int line = 0; line < number.lines; line++)
  {
    setcolor(RED, BLACK_B);
    cout << stringToUpper(cvtPosNr(line));

	if ( ((number.lines / 27) > 0) && (line < 26))
      cout << "  ";
    else
      cout << ' ';

    setcolor(BLACK, WHITE_B);
    //cout << ' ';

    for (int column = 0; column < number.columns; column++)
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
string Board::generateWildcard(string position, int size) const
{
	wordPosition pos(position);
	if (!pos.inBoard(number.lines, number.columns))
		return "-1";

	if(!wordFits(pos, size))
		return "-2";

	string output;

	for (int offset = 0; offset < size; offset++)
	{
		if (pos.getDirection() == 'V')
		{
			if (addedChars.find(stringToUpper(cvtPosNr(pos.getLine() + offset)) + cvtPosNr(pos.getColumn())) != addedChars.end())
				output.push_back(addedChars.at(stringToUpper(cvtPosNr(pos.getLine() + offset)) + cvtPosNr(pos.getColumn())));
			else
				output.push_back('?');
		}
		else
		{
			if (addedChars.find(stringToUpper(cvtPosNr(pos.getLine())) + cvtPosNr(pos.getColumn() + offset)) != addedChars.end())
				output.push_back(addedChars.at(stringToUpper(cvtPosNr(pos.getLine())) + cvtPosNr(pos.getColumn() + offset)));
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
	word = stringToUpper(word);

	if (!(dictionary->checkWordDictionary (word)))
		return -1; //inexistent word

	if (words.find(stringToUpper(word)) != words.end())
		return -4; //repeated word

	wordPosition position(pos);

	if (!position.inBoard(number.lines, number.columns))
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

	//adds word to list
	words.emplace(pos, stringToUpper(word));

	//adds non-redundant characters
	for (map<string, char>::iterator it = charMap.begin(); it != charMap.end(); it++)
		addedChars.emplace( it->first, it->second );

	//adds new black spaces
	addBlackSpaces();



	return 0;
}


//PRIVATE MEMBER FUNCTIONS
/**
 * Fills all empty spaces with black spaces
 */
void Board::blackout()
{
	for (int line = 0; line < (this->number.lines); line++)
		for (int column = 0; column < (this->number.columns); column++)
		{
			charPosition pos(line, column);
			if (pos.isValid())
				if (addedChars.find(pos.str()) == addedChars.end())
					addedChars.emplace(pos.str(), '#');
		}
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
		wordPosition position(par->first);
		string word = par->second;


		map<string, char> wordChars = tempMap(position, word); //provisional store of the characters

		//deletes redundant characters
		for (map<string, char>::iterator it = wordChars.begin(); it != wordChars.end(); it++)
		{
			if (newMap.find(it->first) != newMap.end())
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

/**
 * Adds black spaces to the extremities of the words
 */
void Board::addBlackSpaces()
{
	for (map<string,string>::iterator it = words.begin(); it != words.end(); it++)
	{
		wordPosition position(it->first);
		string word = it->second;

		charPosition before(0, 0);
		charPosition after(0, 0);
		if (position.getDirection() == 'V')
		{
			before = charPosition(position.getLine() - 1, position.getColumn());
			after = charPosition(position.getLine() + word.length(), position.getColumn());
		}
		else
		{
			before = charPosition(position.getLine(), position.getColumn() - 1);
			after = charPosition(position.getLine(), position.getColumn() + word.length());
		}

		if (before.inBoard(number.lines, number.columns))
		{
			if (addedChars.find(before.str()) == addedChars.end())
				addedChars.emplace(before.str(), '#');
		}
		if (after.inBoard(number.lines, number.columns))
		{
			if (addedChars.find(after.str()) == addedChars.end())
				addedChars.emplace(after.str(), '#');
		}
	}
}

/**
 * Removes the black spaces from around a word.
 *
 * @param	position	The starting position of the word
 * @param	length		The length of the word
 */
void Board::removeBlackSpaces(const wordPosition& position, int length)
{
	charPosition before(0, 0);
	charPosition after(0, 0);
	if (position.getDirection() == 'V')
	{
		before = charPosition(position.getLine() - 1, position.getColumn());
		after = charPosition(position.getLine() + length, position.getColumn());
	}
	else
	{
		before = charPosition(position.getLine(), position.getColumn() - 1);
		after = charPosition(position.getLine(), position.getColumn() + length);
	}
	if (before.inBoard(number.lines, number.columns))
		addedChars.erase(addedChars.find(before.str()));
	if (after.inBoard(number.lines, number.columns))
		addedChars.erase(addedChars.find(after.str()));

}

/**
 * Returns whether a word of given length fits in a given position
 *
 * @param	position	Starting position of the word
 * @param	length		Length of the word
 * @return				Value of the predicate
 */
bool Board::wordFits(wordPosition& position, int length) const
{
	if (!position.inBoard(number.lines, number.columns))
		return false;

	//can the word fit in the board?
	if (position.getDirection() == 'V')
	{
		if (position.getLine() + length > number.lines)
			return false;
	}
	else
	{
		if (position.getColumn() + length > number.columns)
			return false;
	}

	//is there a constrain put in by other words?
	charPosition before(0, 0);
	charPosition after(0, 0);
	if (position.getDirection() == 'V')
	{
		before = charPosition(position.getLine() - 1, position.getColumn());
		after = charPosition(position.getLine() + length, position.getColumn());
	}
	else
	{
		before = charPosition(position.getLine(), position.getColumn() - 1);
		after = charPosition(position.getLine(), position.getColumn() + length);
	}

	if (before.inBoard(number.lines, number.columns))
	{
		if (addedChars.find(before.str()) != addedChars.end())
			if (addedChars.at(before.str()) != '#')
				return false;
	}

	if (after.inBoard(number.lines, number.columns))
	{
		if (addedChars.find(after.str()) != addedChars.end())
			if (addedChars.at(after.str()) != '#')
				return false;
	}

	return true;
}

/**
 * Produces a map with the characters of the given word and their position
 * strings.
 *
 * @param	position	The starting position of the word
 * @param	word		The word
 * @return				A map of the characters and their position strings
 */
map<string,char> Board::tempMap(const wordPosition& position, string word) const
{
	map<string,char> output;

	for (int offset = 0; offset < word.length(); offset++)
	{
		charPosition letter(0, 0);
		if (position.getDirection() == 'V')
		{
			letter = charPosition(position.getLine() + offset, position.getColumn());
		}
		else
		{
			letter = charPosition(position.getLine(), position.getColumn() + offset);
		}

		output.emplace(letter.str(), word.at(offset));
	}

	return output;
}

/**
 * Constructs object from coordinates. Updates validity internally.
 *
 * @param	line	Line to be set
 * @param	column	Column to be set
 */
charPosition::charPosition(int line, int column)
{
  setCoords(line, column);
}

/**
 * Converts character position string to numeric coordinates and constructs
 * the object.
 *
 * @param	position	The position string
 */
charPosition::charPosition(string position)
{
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
	if (position.length() == 0 )
		if (validPosStr(lineStr) && validPosStr(colStr))
			setCoords(cvtPosStr(lineStr), cvtPosStr(colStr));
}

/**
 * Returns whether the position can describe a valid position in a board of
 * specified dimensions.
 *
 * @param	nLines	The number of lines of the board
 * @param	nColumn	The number of columns of the board
 * @return			The truth vale of the afore mentioned predicate
 */
bool charPosition::inBoard(int nLines, int nColumns) const
{
	return (isValid() && getLine() < nLines && getColumn() < nColumns);
}

/**
 * Converts the position coordinates to a position string. If the position is
 * not valid, it returns an empty string instead.
 *
 * @return	The corresponding position string
 */
string charPosition::str() const
{
	if (isValid())
	{
	string line, column;

	line = stringToUpper(cvtPosNr(getLine()));
	column = cvtPosNr(getColumn());

	string output = line + column;
	return output;
	}
	else
		return "";
}

/**
 * Constructs object from its coordinates. Internally determines validity
 *
 * @param	line		Starting line
 * @param	column		Starting column
 * @param	direction	Direction in which the word is laid out
 */
wordPosition::wordPosition(int line, int column, char direction)
{
	setCoords(line, column, direction);
	updateValidity();
}

/**
 * Converts the coordinates from a position string to their numeric values
 * and constructs the object. Internally determines validity
 *
 * @param	position	The position string
 */
wordPosition::wordPosition(string position)
{
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
	{
		direction = position.at(0);
		position.erase(0, 1);
	}

	//checks whether a valid position was input
	if (position.length() == 0 )
	{
		if (validPosStr(lineStr) && validPosStr(colStr))
			if (direction == 'H' || direction == 'V')
				setCoords(cvtPosStr(lineStr), cvtPosStr(colStr), direction);
	}
	else
		this->direction = 0;

}

/**
 * Determines whether the position is valid and inside of a board of
 * specified dimension.
 *
 * @param	nLines		Number of lines the board has
 * @param	nColumn		Number of columns the board has
 * @return				The value of the afore mentioned predicate
 */
bool wordPosition::inBoard(int nLines, int nColumns) const
{
	return (isValid() && getLine() < nLines && getColumn() < nColumns);
}

/**
 * Returns a position string corresponding to the position.
 *
 * @return	The corresponding position string
 */
string wordPosition::str() const
{
	if (isValid())
	{
	string line, column;

	line = stringToUpper(cvtPosNr(getLine()));
	column = cvtPosNr(getColumn());

	string output = line + column + direction;
	return output;
	}
	else
		return "";
}

/**
 * Returns the direction in which the word is laid out.
 *
 * @return		The direction in which the word is laid out
 */
char wordPosition::getDirection() const
{
	return direction;
}

/**
 * Default constructor for the object. Initialises line and column as -1,
 * the direction as null and as invalid.
 */
wordPosition::wordPosition()
{
	direction = 0;
}

/**
 * Sets the value of the direction character. Updates validity.
 *
 * @param	direction	The direction in which the word is laid out
 */
void wordPosition::setDirection(char direction)
{
	this->direction = direction;
	updateValidity();
}

/**
 * Sets the coordinates of the position. Updates validity.
 *
 * @param	line		The starting line
 * @param	column		The starting column
 * @param	direction	The direction in which the word is laid out
 */
void wordPosition::setCoords(int line, int column, char direction)
{
	setLine(line);
	setColumn(column);
	setDirection(direction);
}

/**
 * Updates the validity value, which obeys the following criteria:
 * <p>
 * - Positive integer between (and including) 0 and 701 for line and column
	 * <p>
 * - Direction character 'V' (vertical) or 'H' (horizontal)
 */
void wordPosition::updateValidity()
{
	bool validity = (getLine() >= 0 && getLine() < 702);
	validity = validity && (getColumn() >= 0 && getColumn() < 702);
	setValidity(validity && (direction == 'V' || direction == 'H'));
}

/*
 * Returns the number of lines in the board
 *
 * @return	The number of lines in the board
 */
int Board::getLines() const
{
	return number.lines;
}

/**
 * Returns the number of columns in the board
 *
 * @return The number of column in the board
 */
int Board::getColumns() const
{
	return number.columns;
}


/**
 * Returns a string "a" to "zz" correspoding to a number up to 701.
 *
 * @param	number	In range [0, 701]
 * @return			String from "a" to "zz"
 */
string cvtPosNr(int number)
{
	assert(number >= 0);
	assert(number <= 701);
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
 * Returns a number up to 701 corresponding to a string
 * from "a" to "zz".
 *
 * @param	string	From "a" to "zz"
 * @return			Number in range [0, 701]
 */
int cvtPosStr(string str)
{
	assert(str.length() > 0);
	assert(str.length() <= 2);

	str = stringToLower(str);

	if (str.length() == 1)
		return int(str[0]) - int ('a');
	else
	{
		int rightChar = int(str[1]) - int ('a');
		int leftChar = int(str[0]) - int ('a');
		return rightChar + 26*(leftChar + 1);
	}
}

/**
 * Returns whether the board is has a character in all possible positions
 * 
 * @return		If the board is complete
 */
bool Board::complete() const
{
	return addedChars.size() == (number.lines * number.columns);
}
