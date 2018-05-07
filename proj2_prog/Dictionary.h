#pragma once

#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Dictionary
{
public:

	Dictionary();
	void printDictionary();//Prints dictionary: [key]: [element1 of vector], [element2 of vector], [element3 of vector]
	void removeSpaces(string &word); //Removes space at index 0 of a word if it exists
	string dictName();//Returns dictionary source file name
	bool checkWordDictionary(const string &keyWord);//Checks if a certain word is present in the dictionary map container
	vector <string> getSynonyms(const string &keyWord);//Returns the corresponding string vector of the keyWord

private:
	map <string, vector <string> > dictionary; // Contains Every Word And Synonyms. The string element is the key.
	string name;
};
