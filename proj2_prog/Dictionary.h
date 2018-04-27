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
	void printDictionary();
	
private:
	map <string, vector <string> > dictionary; // Contains Every Word And Synonyms. The string element is the key.
	string name;
};
