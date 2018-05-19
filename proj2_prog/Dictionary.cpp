#include "Dictionary.h"

/**
 * Compares the compatibility of a wildcard with another C string
 * 
 * @param	str		Pointer to the beginning of the normal string
 * @param	strWild	Pointer to the beginning of the wildcard
 * @return			Whether the string and the wildcard match
 */
bool wildcardMatch(const char *str, const char *strWild)
{

	while (*strWild)
	{

		if (*strWild == '?')
		{

			if (!*str)
				return false;

			++str;
			++strWild;
		}
		else if (*strWild == '*')
		{

			if (wildcardMatch(str, strWild + 1))

				return true;

			if (*str && wildcardMatch(str + 1, strWild))
				return true;

			return false;
		}
		else
		{

			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}

	return !*str && !*strWild;
}

/**
 * Returns a vector with all the possible matches to a given wildcard in the
 * dictionary keys.
 * 
 * @param	searchParam The wildcard to be used as a search parameter
 * @return				All matches to the search parameter
 */
vector <string> Dictionary::getPossibleWords(string searchParam) const
{
	vector <string> matches;

	for (auto elem : dictionary)
	{
		if (wildcardMatch(elem.first.c_str(), searchParam.c_str()))
		{
			matches.push_back(elem.first);
		}
	}

	return matches;
}

/**
 * Returns a string with the name of the dictionary file.
 * 
 * @return	Filename
 */
string Dictionary::dictName() const
{
	return this->name;
}

/**
 * Removes the space at the index 0 of a string, if existent.
 * 
 * @param	word	The string to process
 */
void removeSpaces(string& word)
{
	if (word.length() >= 1)
		if (word.at(0) == ' ')
		{
			word = word.substr(1);
		}
}

/**
 * Reads a synonym dictionary file and constructs a structured representation of it.
 * <p>
 * Outputs sucess state to a control variable (true if an error ocurrs).
	 * 
 * @param	filename	The name of the file
 * @param	control		The adress of a control variable
 */
Dictionary::Dictionary(string filename, bool& control)
{
	this->name = filename;
	ifstream dict;
	dict.open(filename);
	string currentLine;

	if (dict.is_open())
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

			this->dictionary[keyWord] = synonyms; //Adds to the dictionary map the first and second elements

		}
		dict.close(); //Closes file
		control = false;
	}
	else
	{
		//cerr << "Error opening file" << endl;
		control = true;
	}
}

/**
 * Prints the dictionary to std::cout
 */
void Dictionary::printDictionary() const
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

/**
 * Is true when the word is a key in the dictionary
 * 
 * @param	keyWord		The word to search
 * @return				Whether it exists in the dictionary
 */
bool Dictionary::checkWordDictionary(const string& keyWord) const
{
	string word = stringToUpper(keyWord);
	return this->dictionary.find(word) != dictionary.end();
}

/**
 * Returns a vector with the synonyms of the word searched
 * 
 * @param	keyWord		The word to search
 * @return				Its synonyms
 */
vector<string> Dictionary::getSynonyms(const string& keyWord) const
{
	if (this->dictionary.find(keyWord) == this->dictionary.end())
		return vector<string>();
	else
		return this->dictionary.find(keyWord)->second;
}
