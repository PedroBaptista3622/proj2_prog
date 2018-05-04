#include "stdafx.h"
#include "Dictionary.h"
#include "utilities.h"

string Dictionary::dictName()
{
	return this->name;
}

void Dictionary::removeSpaces(string &word)
{
	if (word.length() >= 1)
		if (word.at(0) == ' ')
		{
			word = word.substr(1);
		}
}

Dictionary::Dictionary()
{
	bool fileOpened = false;
	string currentLine;
	cout << "Please insert dictionary name" << endl;
	cin >> name;


	ifstream dict;
	dict.open(name);

	if (!dict.fail())
	{
		fileOpened = true;
		cout << "File Opened!" << endl;
	}
	else
	{
		cerr << "Error opening file" << endl;
	}

	if (fileOpened)
	{
		while (getline(dict, currentLine))
		{
			string keyWord;
			string currentWord; //1st synonym in the line
			vector <string> synonyms;//Contains every synonym of each keyword
			bool end = false;
			int c = currentLine.find(':'); //c Contains the index of ':'

			keyWord = stringToUpper(currentLine.substr(0, c));
			currentLine = currentLine.substr(c + 2);

			do
			{
				c = currentLine.find(',');

				if (c == string::npos)
				{
					c = currentLine.find((char)13);
					end = true;
					//c Contains de index if ',' if it exists, otherwise, contains de index of CR
				}

				currentWord = currentLine.substr(0, c);
				removeSpaces(currentWord);//Removes the empty space at the start of the word
				synonyms.push_back(stringToUpper(currentWord));//Adds word to the synonyms vector


				if (!end) //If it's the last element this won't be executed
				{
					currentLine = currentLine.substr(c + 1);
				}



			} while (!end);

			dictionary[keyWord] = synonyms; //Adds to the dictionary map the first and second elements 

		}

		dict.close(); //Closes file
	}
	else
	{
		cerr << "Error opening file" << endl;
	}

}


void Dictionary::printDictionary()
{
	for (auto elem : dictionary) // Goes through every pair of the dictionary map 
	{
		cout << elem.first << ": ";

		for (int i = 0; i < elem.second.size(); i++) // Goes through every word of the vector in the second element of the dictionary map
		{

			if (i == elem.second.size() - 1)
			{
				cout << elem.second.at(i) << endl;
			}
			else
			{
				cout << elem.second.at(i) << ", ";
			}

		}
	}
}
