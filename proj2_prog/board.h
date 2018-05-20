//Compiler directives
//#ifndef BOARD_H
//#define BOARD_H
#pragma once

#ifdef _WIN32
#include "colour_windows.h"
#else
#include "colour_linux.h"
#endif

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cassert>
#include <cctype>
#include "Dictionary.h"
#include "utilities.h"
using namespace std;

//Definitions

/**
 * Represents the position occupied by a character on the crosswords board.
 * Very light additions to the base Position class.
 *
 * @author	João N. Matos
 * @version	1.0
 * @see		Position
 */
class charPosition : public Position
{
public:

	/**
	 * Constructs object from coordinates. Updates validity internally.
	 *
	 * @param	line	Line to be set
	 * @param	column	Column to be set
	 */
	charPosition(int line, int column);

	/**
	 * Converts character position string to numeric coordinates and constructs
	 * the object.
	 *
	 * @param	position	The position string
	 */
	charPosition(string position);

	/**
	 * Returns whether the position can describe a valid position in a board of
	 * specified dimensions.
	 *
	 * @param	nLines	The number of lines of the board
	 * @param	nColumn	The number of columns of the board
	 * @return			The truth vale of the afore mentioned predicate
	 */
	bool inBoard(int nLines, int nColumn) const;

	/**
	 * Converts the position coordinates to a position string. If the position
	 * is not valid, returns an empty string instead.
	 *
	 * @return	The corresponding position string
	 */
	string str() const;

};

/**
 * Adds functionality to the base class Position to deal with word start
 * positions in a crosswords board. Specifically, it supports indication
 * of the direction in which the word is laid out.
 *
 * @author	João N. Matos
 * @version 1.0
 * @see		Position
 */
class wordPosition : public Position
{
public:

	/**
	 * Constructs object from its coordinates. Internally determines validity
	 *
	 * @param	line		Starting line
	 * @param	column		Starting column
	 * @param	direction	Direction in which the word is laid out
	 */
	wordPosition(int line, int column, char direction);

	/**
	 * Converts the coordinates from a position string to their numeric values
	 * and constructs the object. Internally determines validity
	 *
	 * @param	position	The position string
	 */
	wordPosition(string position);

	/**
	 * Default constructor for the object. Initialises line and column as -1,
	 * the direction as null and as invalid.
	 */
	wordPosition();

	/**
	 * Determines whether the position is valid and inside of a board of
	 * specified dimension.
	 *
	 * @param	nLines		Number of lines the board has
	 * @param	nColumn		Number of columns the board has
	 * @return				The value of the afore mentioned predicate
	 */
	bool inBoard(int nLines, int nColumns) const;

	/**
	 * Returns the direction in which the word is laid out.
	 *
	 * @return		The direction in which the word is laid out
	 */
	char getDirection() const;

	/**
	 * Returns a position string corresponding to the position.
	 *
	 * @return	The corresponding position string
	 */
	string str() const;

protected:

	/**
	 * Sets the value of the direction character. Updates validity.
	 *
	 * @param	direction	The direction in which the word is laid out
	 */
	void setDirection(char direction);

	/**
	 * Sets the coordinates of the position. Updates validity.
	 *
	 * @param	line		The starting line
	 * @param	column		The starting column
	 * @param	direction	The direction in which the word is laid out
	 */
	void setCoords(int line, int column, char direction);

private:

	char direction;

	/**
	 * Updates the validity value, which obeys the following criteria:
	 * <p>
	 * - Positive integer between (and including) 0 and 701 for line and column
	 * <p>
	 * - Direction character 'V' (vertical) or 'H' (horizontal)
	 */
	void updateValidity();

};

/**
 * Board is a class that stores the atributes of a crosswords puzzle, including
 * its size, inserted words and an associated dictionary.
 * <p>
 * This class and its associated methods are guaranteed not to modify the
 * dictionary to which it points.
 *
 * @author	João N. Matos
 * @author	Pedro Baptista
 * @version 1.2
 * @see		Dictionary
 */
class Board
{
public:
	//Constructors

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
	Board(int lines, int columns); //DONE

	/**
	 * Constructs a Board object and associates a Dictionary to it.
	 *
	 * @param	lines		The number of lines the board will have
	 * @param	columns		The number of columns in the board will have
	 * @param	dictionary	Pointer to the Dictionary object
	 */
	Board(int lines, int columns, Dictionary* dictionary); //DONE

	/**
	 * Constructs a Board object by loading an unfinished board from a file.
	 * <p>
	 * Allocates and constructs internal dictionary with imported filename.
	 *
	 * @param	filename	Name of the file to import
	 * @param	control		Variable to store sucess state of the dictionary
	 */
	Board(string filename, bool& control); //DONE

	//DESTRUCTOR

	/**
	 * Destructs Board object
	 */
	~Board(); //DONE

	//PUBLIC MEMBER FUNCTION

	/**
	 * Associates a Dictionary object by its pointer to the Board object.
	 *
	 * @param	dictionary	Pointer to the Dictionary object
	 */
	void linkDic(Dictionary* dictionary, bool replace = false); //DONE

	/**
	 * Returns a copy of the dictionary pointer.
	 * @return	A copy of the dictionary pointer.
	 */
	Dictionary* getDicPointer() const;

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
	int insWord(string pos, string word); //DONE

	/**
	 * Removes existing word from the board. Returns -1 if no word in position,
	 * 0 if successful.
	 *
	 * @param	word	The position
	 * @return			The exit code of the procedure
	 */
	int remWord(string position);

	/**
	 * Returns whether a word of given length fits in a given position
	 *
	 * @param	position	Starting position of the word
	 * @param	length		Length of the word
	 * @return				Value of the predicate
	 */
	bool wordFits(wordPosition& position, int length) const; //DONE

	/**
	 * Saves the board to a file, returning 0 if sucessful and -1 if not.
	 *
	 * @param	filename	Name of the file to store the board in
	 * @param	finished	Determines whether to save board as finished
	 * @returns				Exit code
	 */
	int save(string filename, bool finished); //DONE

	/**
	 * Shows the board on screen.
	 */
	void show() const; //DONE

	/**
	 * Constructs a wilcard for the specified position taking into account
	 * possible overlaps. Can also return "0" if no wildcard can be constructed
	 * or "-1" if the position is invalid.
	 *
	 * @param	position	the position string where it should start generating
	 * @returns					wildcard string, or exit code string
	 */
	string generateWildcard(string position, int size) const; //DONE

	/*
	 * Returns the number of lines in the board
	 *
	 * @return	The number of lines in the board
	 */
	int getLines() const;

	/**
	 * Returns the number of columns in the board
	 *
	 * @return The number of column in the board
	 */
	int getColumns() const;

	/**
	 * Returns whether the board is has a character in all possible positions
	 * 
	 * @return		If the board is complete
	 */
	bool complete() const;

protected:

	//FIELDS

	//keeps dimensions of board
	struct boardDim {
		int lines;
		int columns;
	} number;

	//keeps a list of words and its position
	map<string,string> words;

	//keeps a list of the position of the characters already added
	map<string, char> addedChars;

	Dictionary* dictionary;

	bool internalDictionary;

	//MEMBER FUNCTIONS
	/**
	 * Fills all empty spaces with black spaces
	 */
	void blackout(); //DONE

	/**
	 * Re-does the addedChars map from the existing added words
	 */
	void refill(); //DONE

	/**
	 * Adds black spaces to the extremities of the words
	 */
	void addBlackSpaces(); //DONE

	/**
	 * Removes the black spaces from around a word.
	 *
	 * @param	position	The starting position of the word
	 * @param	length		The length of the word
	 */
	void removeBlackSpaces(const wordPosition& position, int length); //DONE

	/**
	 * Produces a map with the characters of the given word and their position
	 * strings.
	 *
	 * @param	position	The starting position of the word
	 * @param	word		The word
	 * @return				A map of the characters and their position strings
	 */
	map<string,char> tempMap(const wordPosition& position, string word) const;

};

/**
 * Returns a string "a" to "zz" correspoding to a number up to 26^2 - 1.
 *
 * @param	number	In range [0, 26^2 - 1]
 * @return			String from "a" to "zz"
 */
string cvtPosNr(int number); //DONE

/**
 * Returns a number up to 26^2 - 1 corresponding to a string
 * from "a" to "zz".
 *
 * @param	string	From "a" to "zz"
 * @return			Number in range [0, 26^2 - 1]
 */
int cvtPosStr(string str); //DONE

//#endif
//End of file
