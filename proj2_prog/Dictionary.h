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
	void delSpaces();							// Deletes empty spaces in words from vector
	void printDictionary();						//Prints dictionary: [key]: [element1 of vector], [element2 of vector], [element3 of vector]

private:
	map <string, vector <string> > dictionary; // Contains Every Word And Synonyms. The string element is the key.
	string name;
};
