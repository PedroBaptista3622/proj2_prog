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


private:
	map <string, vector <string> > dictionary; // Contains Every Word And Synonyms. The string element is the key.
	string name;
};
