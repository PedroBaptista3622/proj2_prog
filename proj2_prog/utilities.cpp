/** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
 *                              Utility Library                                *
 *                              Implementation                                 *
 ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** */
// Author - João N. Matos

#include "utilities.h"
#include <cctype>
#include "board.h"

using namespace std;
/**
 * Compares two position strings and returns whether the first is before
 * the second, using first the line and then the column as criteria.
 *
 * @param	pos1	First position string
 * @param	pos2	Second position string
 * @return			Truth value of predicate
 */
/*
bool prevPos(const string& pos1, const string& pos2)
{
	struct coords {
		string line;
		string column;
	} coords1, coords2;

	for (int i = 0; i < pos1.length(); i++)
	{
		if (isupper(pos1[i]))
			coords1.line.push_back(pos1[i]);
		else
			coords1.column.push_back(pos1[i]);
	}

	for (int i = 0; i < pos2.length(); i++)
	{
		if (isupper(pos2[i]))
			coords2.line.push_back(pos2[i]);
		else
			coords2.column.push_back(pos2[i]);
	}

	if (cvtPosStr(coords1.line) < cvtPosStr(coords2.line))
		 return true;
	else if (cvtPosStr(coords1.line) == cvtPosStr(coords2.line))
	{
		if (cvtPosStr(coords1.column) < cvtPosStr(coords2.column))
			return true;
		else
			return false;
	}
	else
		return false;

}
*/
/**
 * Returns whether the first string should be ordered before the second
 * string, alphabetically
 *
 * @param	lhs	the first string to compare
 * @param	rhs	the second string to compare
 * @return		the truth value of the predicate
 */
/*
bool first(const string& lhs, const string& rhs)
{
	bool smaller = (lhs.size() < rhs.size());
	int maxcompare;
	if (smaller)
		maxcompare = lhs.size();
	else
		maxcompare = rhs.size();
	for (int i = 0; i < maxcompare; i++)
	{
		if (lhs.at(i) != rhs.at(i))
			return lhs.at(i) < rhs.at(i);
	}
	return smaller;
}
*/

/**
 * Capitalises entire string of alphabetic characters
 *
 * @param	str		String of alphabetic characters
 * @return			Capitalised version of string
 */
string stringToUpper(string str)
{
	string outp;
	for (int i = 0; i < str.length(); i++)
		outp.push_back(toupper(str.at(i)));
	return outp;
}

/**
 * Decapitalises entire string of alphabetic characters
 *
 * @param	str		String of alphabetic characters
 * @return			Capitalised version of string
 */
string stringToLower(string str)
{
	string outp;
	for (int i = 0; i < str.length(); i++)
		outp.push_back(tolower(str.at(i)));
	return outp;
}

/**
 * Checks if a string can be used as a valid position on a board.
 * <p>
 * Criteria are having one or two alphabetic characters and consistent
 * capitalisation
 * 
 * @param	str		Position string
 * @return			Its validity
 */
bool validPosStr(string str)
{
	if (str.length() > 2 || str.length() < 1)
		return false;

	for (int i = 0; i < str.length(); i++)
	{
		if (!isalpha(str.at(i)))
			return false;
	}

	if (str.length() == 2)
		if ( isupper(str.at(0)) != isupper(str.at(1)) )
			return false;

	return true;
}

/**
 * Default constructor for a position. Sets line and column as -1.
 */
Position::Position()
{
  line = -1;
  column = -1;
  valid = false;
}

/**
 * Updates validity of the position from the stores coordinates.
 * <p>
 * A valid position are integer coordinates between 0 and 702,
 * including these values.
 */
void Position::updateValidity()
{
  valid = (line >= 0) && (line < 702) && (column >= 0) && (column < 702);
}

/**
 * Returns the current validity state
 * 
 * @return	whether the position is deemed valid
 */
bool Position::isValid() const
{
  return valid;
}

/**
 * Constructor for a position with coordinates. Checks validity internaly.
 *
 * @param	line	The number of the line, starting in 0
 * @param	column	The number of the column, starting in 0
 */
Position::Position(int line, int column)
{
  this->line = line;
  this->column = column;
  updateValidity();
}

/**
 * Returns the line currently stored
 * 
 * @return		The currently stored line
 */
int Position::getLine() const
{
  return line;
}

/**
 * Returns the column currently stored
 * 
 * @return		The currently stored column
 */
int Position::getColumn() const
{
  return column;
}

/**
 * Setter for the line. Checks validity and updates its value
 * 
 * @param	line	The new value to set the line at
 */
void Position::setLine(int line)
{
  this->line = line;
  updateValidity();
}

/**
 * Setter for the column. Checks validity and updates its value
 * 
 * @param	column	The new value to set the column at
 */
void Position::setColumn(int column)
{
  this->column = column;
  updateValidity();
}

/**
 * Setter for both coordinates. Checks validity and updates its value
 * 
 * @param	line	The new value to set the line at
 * @param	column	The new value to set the column at
 */
void Position::setCoords(int line, int column)
{
  this->line = line;
  this->column = column;
  updateValidity();
}

/**
 * Setter for the validity state.
 * 
 * @param	valid	New validity state
 */
void Position::setValidity(bool valid)
{
  this->valid = valid;
}

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
int readInt(string errormsg, istream& instream, ostream& outstream)
{
	string input;
	bool valid;

	do
	{
		valid = true;
		getline(instream, input);
		instream.clear();
		if (input.length() == 0)
		{
			valid = false;
			outstream << errormsg;
		}
		else if (input.length() == 1)
		{
			if (!isdigit(input.at(0)))
			{
				valid = false;
				outstream << errormsg;
			}
		}
		else
		{
			if (!isdigit(input.at(0)) && input.at(0) != '-')
				valid = false;

			for (int i = 1; i < input.length(); i++)
				if (!isdigit(input.at(i)))
					valid = false;

			if (!valid)
				outstream << errormsg;
		}
	} while (!valid);

	return stoi(input);
}

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
char readChar(string errormsg, istream& instream, ostream& outstream)
{
	string input;
	bool valid;

	do {
		valid = true;
		getline(instream, input);
		instream.clear();
		if (input.length() != 1)
		{
			valid = false;
			outstream << errormsg;
		}
	} while (!valid);

	return input.at(0);
}

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
string readString(string errormsg, istream& instream, ostream& outstream)
{
	string input;

	bool valid;
	do {
		valid = true;
		getline(instream, input);
		instream.clear();
		if (input.length() == 0)
		{
			valid = false;
			outstream << errormsg;
		}
	} while (!valid);

	return input;
}
//End of file
