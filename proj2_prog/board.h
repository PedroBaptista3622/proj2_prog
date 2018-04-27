//compiler directives
#IFNDEF BOARD_H
#DEFINE BOARD_H
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "dictionary.h"

//code

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
 * @see	Dictionary
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
		 * @param	lines	the number of lines the board will have
		 * @param	columns	the number of columns in the board will have
		 */
		Board(unsigned int lines, unsigned int columns);

		/**
		 * Constructs a Board object and associates a Dictionary to it.
		 * 
		 * @param	lines	the number of lines the board will have
		 * @param	columns	the number of columns in the board will have
		 * @param	*dictionary	pointer to the dictionary 
		 */
		Board(unsigned int lines, unsigned int columns, Dictionary* dictionary);

		//Methods

		/**
		 * Associates a Dictionary object by its pointer to the Board object.
		 * 
		 * @param	*dictionary	pointer to the dictionary
		 */
		void linkDictionary(Dictionary* dictionary);

		//TODO
		//TODO int insertWord(string position, string word);
	private:
		//keeps size
		struct size {
			unsigned int rows;
			unsigned int columns;
		} number;

		//keeps a list of words and its position
		