#include "board.h"
using namespace std;


/**
 * Overloads the "less than" two strings, returning whether the first string
 * should be ordered before the second string
 *
 * @param	s1	the first string to compare
 * @param	s2	the second string to compare
 * @return		the truth value of the predicate
 */
bool operator<(const string& lhs, const string& rhs)
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
	number.lines = lines;
	number.columns = columns;
	dictionary = NULL;
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
	number.lines = lines;
	number.columns = columns;
	this->dictionary = dictionary;
}

/**
 * Associates a Dictionary object by its pointer to the Board object.
 *
 * @param	dictionary	Pointer to the Dictionary object
 */
void Board::linkDic(Dictionary* dictionary)
{
	this->dictionary = dictionary;
}

/** TODO
 * Compares two position strings and returns whether the first is before
 * the second, using first the line and then the column as criteria.
 *
 * @param	pos1	First position string
 * @param	pos2	Second position string
 * @return			Truth value of predicate
 */
/*
 bool prevPos(string pos1, string pos2)
{
	struct coords {
		string line;
		string column;
	} coords1, coords2;
}
*/
