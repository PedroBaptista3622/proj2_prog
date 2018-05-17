/** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
 *                             Utility Functions                               *
 *                              Implementation                                 *
 ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** */
// Author - João N. Matos

#include "stdafx.h"
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
	for (unsigned int i = 0; i < str.length(); i++)
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
	for (unsigned int i = 0; i < str.length(); i++)
		outp.push_back(tolower(str.at(i)));
	return outp;
}


//End of file
