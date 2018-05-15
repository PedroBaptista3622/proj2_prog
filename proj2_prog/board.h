//Compiler directives
//#ifndef BOARD_H
//#define BOARD_H
#pragma once

//#include "stdafx.h"
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "Dictionary.h"
#include "utilities.h"
#include "colour_linux.h"
using namespace std;

//Definitions

/**
 * Board is a class that stores the atributes of a crosswords puzzle, including
 * its size, inserted words and an associated dictionary.
 * <p>
 * This class and its associated methods are guaranteed not to modify the
 * dictionary to which it points.
 *
 * @author	João N. Matos
 * @author	Pedro Baptista
 * @version 1.1
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
		Board(unsigned int lines, unsigned int columns); //DONE

		/**
		 * Constructs a Board object and associates a Dictionary to it.
		 *
		 * @param	lines		The number of lines the board will have
		 * @param	columns		The number of columns in the board will have
		 * @param	dictionary	Pointer to the Dictionary object
		 */
		Board(unsigned int lines, unsigned int columns, Dictionary* dictionary); //DONE

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
		void show(); //DONE

		/**
		 * Constructs a wilcard for the specified position taking into account
		 * possible overlaps. Can also return "0" if no wildcard can be constructed
		 * or "-1" if the position is invalid.
		 *
		 * @param	position	the position string where it should start generating
		 * @returns					wildcard string, or exit code string
		 */
		 string generateWildcard(string position, unsigned int size); //DONE

	protected:

		//FIELDS

		//keeps size
		struct size {
			unsigned int lines;
			unsigned int columns;
		} number;

		//keeps a list of words and its position
		map<string,string> words;

		//keeps a list of the position of the characters already added
		map<string, char> addedChars;

		Dictionary* dictionary;

		bool internalDictionary;

		//MEMBER FUNCTIONS

		/**
		 * Returns a string "a" to "zz" correspoding to a number up to 26^2 - 1.
		 *
		 * @param	number	In range [0, 26^2 - 1]
		 * @return			String from "a" to "zz"
		 */
		string cvtPosNr(unsigned int number); //DONE

		/**
		 * Returns a number up to 26^2 - 1 corresponding to a string
		 * from "a" to "zz".
		 *
		 * @param	string	From "a" to "zz"
		 * @return			Number in range [0, 26^2 - 1]
		 */
		unsigned int cvtPosStr(string str); //DONE


		/**
		 * Fills all empty spaces with black spaces
		 */
		void blackout(); //DONE

		/**
		 * Re-does the addedChars map from the existing added words
		 */
		void refill(); //DONE


};

//#endif
//End of file
