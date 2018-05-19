#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include "utilities.h"

using namespace std;

/**
 * Represents a synonyms dictionary, complete with functions to check the existence
 * of certain words, as well as the extraction of synonyms and wildcard searching.
 * 
 * @author	José Pedro Baptista
 * @version 1.0
 */
class Dictionary
{
public:

	/**
	 * Reads a synonym dictionary file and constructs a structured representation of it.
	 * <p>
	 * Outputs sucess state to a control variable (true if an error ocurrs).
	 * 
	 * @param	filename	The name of the file
	 * @param	control		The adress of a control variable
	 */
	Dictionary(string filename, bool& control);

	/**
	 * Prints the dictionary to std::cout
	 */
	void printDictionary();

	/**
	 * Returns a string with the name of the dictionary file.
	 * 
	 * @return	Filename
	 */
	string dictName();

	/**
	 * Is true when the word is a key in the dictionary
	 * 
	 * @param	keyWord		The word to search
	 * @return				Whether it exists in the dictionary
	 */
	bool checkWordDictionary(const string& keyWord);//Checks if a certain word is present in the dictionary map container

	/**
	 * Returns a vector with the synonyms of the word searched
	 * 
	 * @param	keyWord		The word to search
	 * @return				Its synonyms
	 */
	vector <string> getSynonyms(const string& keyWord);//Returns the corresponding string vector of the keyWord

	/**
	 * Returns a vector with all the possible matches to a given wildcard in the
	 * dictionary keys.
	 * 
	 * @param	searchParam The wildcard to be used as a search parameter
	 * @return				All matches to the search parameter
	 */
	vector <string> getPossibleWords(string searchParam);

private:
	map <string, vector <string> > dictionary; // Contains Every Word And Synonyms. The string element is the key.
	string name;
};

/**
 * Removes the space at the index 0 of a string, if existent.
 * 
 * @param	word	The string to process
 */
void removeSpaces(string& word);

/**
 * Compares the compatibility of a wildcard with another C string
 * 
 * @param	str		Pointer to the beginning of the normal string
 * @param	strWild	Pointer to the beginning of the wildcard
 * @return			Whether the string and the wildcard match
 */
bool wildcardMatch(const char *str, const char *strWild);