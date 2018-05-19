/** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
 *                             Utility Functions                               *
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


bool validPosStr(string str)
{
	if (str.length() > 2 || str.length() < 1)
		return false;

	for (int i = 0; i < str.length(); i++)
	{
		if (!isalpha(str.at(i)))
			return false;
	}

	return true;
}


Position::Position()
{
  line = -1;
  column = -1;
  valid = false;
}

void Position::updateValidity()
{
  valid = (line >= 0) && (line < 703) && (column >= 0) && (column < 703);
}

bool Position::isValid() const
{
  return valid;
}

Position::Position(int line, int column)
{
  this->line = line;
  this->column = column;
  updateValidity();
}

int Position::getLine() const
{
  return line;
}

int Position::getColumn() const
{
  return column;
}

void Position::setLine(int line)
{
  this->line = line;
  updateValidity();
}

void Position::setColumn(int column)
{
  this->column = column;
  updateValidity();
}

void Position::setCoords(int line, int column)
{
  this->line = line;
  this->column = column;
  updateValidity();
}

void Position::setValidity(bool valid)
{
  this->valid = valid;
}

int readInt(string errormsg, istream& instream, ostream& outstream)
{
	string input;
	bool valid;

	do
	{
		valid = true;
		getline(instream, input);

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

char readChar(string errormsg, istream& instream, ostream& outstream)
{
	string input;
	bool valid;

	do {
		valid = true;
		getline(instream, input);
		if (input.length() != 1)
		{
			valid = false;
			outstream << errormsg;
		}
	} while (!valid);

	return input.at(0);
}

string readString(string errormsg, istream& instream, ostream& outstream)
{
	string input;

	bool valid;
	do {
		valid = true;
		getline(instream, input);
		if (input.length() == 0)
		{
			valid = false;
			outstream << errormsg;
		}
	} while (!valid);

	return input;
}
//End of file
