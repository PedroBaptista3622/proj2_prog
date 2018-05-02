//Compiler Directives
//#IFNDEF UTILITY_H
//#DEFINE UTILITY_H
#pragma once
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                             *
 *                           Utilities Library                                 *
 *       Defines some useful functions to be used throughout the project       *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * Returns whether the first string should be ordered before the second
 * string, alphabetically
 *
 * @param	lhs	the first string to compare
 * @param	rhs	the second string to compare
 * @return		the truth value of the predicate
 */
bool first(const string& lhs, const string& rhs);

/**
 * Compares two position strings and returns whether the first is before
 * the second, using first the line and then the column as criteria.
 *
 * @param	pos1	First position string
 * @param	pos2	Second position string
 * @return			Truth value of predicate
 */
bool prevPos(const string& pos1, const string& pos2);

//#ENDIF