//Compiler Directives
//#ifndef UTILITY_H
//#define UTILITY_H
#pragma once

#include <string>
#include <iostream>
using namespace std;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *                           Utilities Library                                 *
 *       Defines some useful functions to be used throughout the project       *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Capitalises entire string of alphabetic characters
 *
 * @param	str		String of alphabetic characters
 * @return			Capitalised version of string
 */
string stringToUpper(string str);

/**
 * Decapitalises entire string of alphabetic characters
 *
 * @param	str		String of alphabetic characters
 * @return			Capitalised version of string
 */
string stringToLower(string str);

/**
 * Checks if a string can be used as a valid position on a board.
 * <p>
 * Criteria are having one or two alphabetic characters and consistent
 * capitalisation
 * 
 * @param	str		Position string
 * @return			Its validity
 */
bool validPosStr(string str);

/**
 * Base class for the position on a board. Implements simple constructors,
 * numeric getters, and setters, as well as internal validity checkers
 * 
 * @author	João N. Matos
 * @version	1.0
 */
class Position
{
public:

	/**
	 * Constructor for a position with coordinates. Checks validity internaly.
	 *
	 * @param	line	The number of the line, starting in 0
	 * @param	column	The number of the column, starting in 0
	 */
	Position(int line, int column);

	/**
	 * Returns the line currently stored
	 * 
	 * @return		The currently stored line
	 */
	int getLine() const;

	/**
	 * Returns the column currently stored
	 * 
	 * @return		The currently stored column
	 */
	int getColumn() const;

	/**
	 * Returns the current validity state
	 * 
	 * @return	whether the position is deemed valid
	 */
	bool isValid() const;

protected:

	/**
	 * Default constructor for a position. Sets line and column as -1.
	 */
	Position();

	/**
	 * Setter for the line. Checks validity and updates its value
	 * 
	 * @param	line	The new value to set the line at
	 */
	void setLine(int line);

	/**
	 * Setter for the column. Checks validity and updates its value
	 * 
	 * @param	column	The new value to set the column at
	 */
	void setColumn(int column);

	/**
	 * Setter for both coordinates. Checks validity and updates its value
	 * 
	 * @param	line	The new value to set the line at
	 * @param	column	The new value to set the column at
	 */
	void setCoords(int line, int column);

	/**
	 * Setter for the validity state.
	 * 
	 * @param	valid	New validity state
	 */
  	void setValidity(bool valid);

private:

	/**
	 * Updates validity of the position from the stores coordinates.
	 * <p>
	 * A valid position are integer coordinates between 0 and 702,
	 * including these values.
	 */
	void updateValidity();

	
	int line, column;

	bool valid;

};

/**
 * Reads an input from an input stream and checks if it represents a valid
 * base 10 integer.
 * <p>
 * If it is not, outputs to the output stream an error message and repeats
 * the procedure until the input is valid. Then returns the corresponding number.
 * 
 * @param	errormsg	The message to display in case of an invalid input.
 * @param	instream	The input stream. Default is std::cin.
 * @param	outstream	The stream to which the error messages are sent. Default is std::cout.
 * @return				A valid integer
 */
int readInt(string errormsg, istream& instream = cin, ostream& outstream = cout);

/**
 * Reads an input from an input stream and checks if it represents a single character.
 * <p>
 * If it is not, outputs to the output stream an error message and repeats
 * the procedure until the input is valid. Then returns the corresponding character.
 * 
 * @param	errormsg	The message to display in case of an invalid input.
 * @param	instream	The input stream. Default is std::cin.
 * @param	outstream	The stream to which the error messages are sent. Default is std::cout.
 * @return				A character
 */
char readChar(string errormsg, istream& instream = cin, ostream& outstream = cout);

/**
 * Reads an input from an input stream and checks if it represents a non-empty
 * string.
 * <p>
 * If it is not, outputs to the output stream an error message and repeats
 * the procedure until the input is valid. Then returns the corresponding string.
 * 
 * @param	errormsg	The message to display in case of an invalid input.
 * @param	instream	The input stream. Default is std::cin.
 * @param	outstream	The stream to which the error messages are sent. Default is std::cout.
 * @return				A non-empty string.
 */
string readString(string errormsg, istream& instream = cin, ostream& outstream = cout);



//#endif
//End of file
