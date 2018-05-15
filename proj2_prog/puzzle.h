//COMPILER DIRECTIVES
//#ifndef PUZZLE_H
//#define PUZZLE_H
#pragma once
#include "board.h"
#include <ctime>
#include <cstdlib>
using namespace std;
/**
 * Puzzle modifies the board class in order to make it better suited for use
 * with the cwplayer app.
 *
 * @author	João N. Matos
 * @author	J. Pedro Baptista
 * @version	0.1
 * @see		Board
 * @see		Dictionary
 */
class Puzzle : Board
{
	public:

		//CONSTRUCTOR
		Puzzle(string filename, bool& control); //DONE

		//MEMBER FUNCTIONS

		/**
		 * New interface for the Board linkDic function
		 */
		void provideBackupDictionary(Dictionary* dictionary, bool replace = false); //DONE

		/**
		 * Shows the puzzle
		 */
		void showPuzzle(); //DONE

		/**
		 * Shows a synonym for each position
		 */
		void showSynonyms(); //DONE

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
		int insGuess(string position, string word); //DONE

		/**
		 * Removes existing word from the board. Returns -1 if no word in position,
		 * 0 if successful.
		 *
		 * @param	word	The position
		 * @return			The exit code of the procedure
		 */
		int remGuess(string position); //DONE

		/**
		 * Returns a different synonym of the word in the given position, or the
		 * same if there is only one
		 *
		 * @param	position	position of the word whose synonym is returned
		 * @return				a different synonym or the same if unique
		 */
		string anotherHint(string position); //DONE

		/**
		 * Returns whether the user's guesses are correct
		 *
		 * @return		Are the words input by the user the correct ones?
		 */
		bool correct(); //DONE


	private:

		//FIELDS

		//keeps the player's guesses
		map<string, string> guessedWords;

		//keeps a hint for each player
		map<string, string> hints;

		//MEMBER FUNCTIONS

		/**
		 * Populates the hint map
		 */
		void getHints(); //DONE
};

//#endif
