//compiler directives
//#IFNDEF BOARD_H
//#DEFINE BOARD_H
#pragma once

#include "stdafx.h"
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "dictionary.h"
using namespace std;

//code

/**
 * Overloads the "less than" two strings, returning whether the first string 
 * should be ordered before the second string
 * 
 * @param	s1	the first string to compare
 * @param	s2	the second string to compare
 * @return		the truth value of the predicate
 */
bool operator<(string s1, string s2);


/**
 * Board is a class that stores the atributes of a crosswords puzzle, including
 * its size, inserted words and an associated dictionary.
 * <p>
 * This class and its associated methods are guaranteed not to modify the
 * dictionary to which it points.
 * 
 * @author	João N. Matos
 * @author	Pedro Baptista
 * @version 0.1
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
		Board(unsigned int lines, unsigned int columns);

		/**
		 * Constructs a Board object and associates a Dictionary to it.
		 * 
		 * @param	lines		The number of lines the board will have
		 * @param	columns		The number of columns in the board will have
		 * @param	*dictionary	Pointer to the Dictionary object
		 */
		Board(unsigned int lines, unsigned int columns, Dictionary* dictionary);

		/**
		 * Constructs a Board object by loading an unfinished board from a file.
		 * The dictionary pointer is initialised as NULL.
		 * <p>
		 * Requires a Dictionary to be later associated.
		 * 
		 * @param	filename	Name of the file to import
		 */
		Board(string filename);

		/**
		 * Constructs a Board object by loading an unfinished board from a file
		 * and associates a Dictionary object to it.
		 * 
		 * @param	filename	Name of the file to import
		 * @param	*dictionary	Pointer to the Dictionary object
		 */
		Board(string filename, Dictionary* dictionary);

		//Methods

		/**
		 * Associates a Dictionary object by its pointer to the Board object.
		 * 
		 * @param	*dictionary	Pointer to the Dictionary object
		 */
		void linkDictionary(Dictionary* dictionary);

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
		 * -4: repeated words.
		 * 
		 * @param	position	The position string to insert the word in
		 * @param	word		The word to insert
		 * @return				The exit code of the procedure
		 */
		int insertWord(string position, string word);

		/**
		 * Saves the board to a file, returning 0 if sucessful and -1 if not.
		 * 
		 * @param	filename	Name of the file to store the board in
		 * @param	mode		Determines whether to save board as finished
		 * @returns				Exit code
		 */
		int save(string filename, unsigned int mode);
		
	private:
		//keeps size
		struct size {
			unsigned int rows;
			unsigned int columns;
		} number;

		//keeps a list of words and its position
		map<string,string> words;

		//keeps a list of the position of the black spaces
		set<string> blackSpaces;

		//keeps a map of the occupied spaces and respective characters
		map<string, char> chars;

		/**
		 * Returns a string "a" to "zz" correspoding to a number up to 26^2 - 1.
		 * 
		 * @param	number	In range [0, 26^2 - 1]
		 * @return			String from "a" to "zz"
		 */
		string convertPosNumber(unsigned int number);

		/**
		 * Returns a number up to 26^2 - 1 corresponding to a string
		 * from "a" to "zz".
		 * 
		 * @param	string	From "a" to "zz"
		 * @return			Number in range [0, 26^2 - 1]
		 */
		unsigned int convertPosString(string string);
};