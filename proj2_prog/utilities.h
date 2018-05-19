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
// Author - João N. Matos

/*
 * Returns whether the first string should be ordered before the second
 * string, alphabetically
 *
 * @param	lhs	the first string to compare
 * @param	rhs	the second string to compare
 * @return		the truth value of the predicate
 */
//bool first(const string& lhs, const string& rhs);

/**
 * Compares two position strings and returns whether the first is before
 * the second, using first the line and then the column as criteria.
 *
 * @param	pos1	First position string
 * @param	pos2	Second position string
 * @return			Truth value of predicate
 */
//bool prevPos(const string& pos1, const string& pos2);

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

bool validPosStr(string str);


class Position
{
public:

	Position(int line, int column);

	int getLine() const;

	int getColumn() const;

	bool isValid() const;

protected:

	Position();

	void setLine(int line);

	void setColumn(int column);

	void setCoords(int line, int column);

  void setValidity(bool valid);

private:

	void updateValidity();

	int line, column;

	bool valid;

};

int readInt(string errormsg, istream& instream = cin, ostream& outstream = cout);

char readChar(string errormsg, istream& instream = cin, ostream& outstream = cout);

string readString(string errormsg, istream& instream = cin, ostream& outstream = cout);



//#endif
//End of file
