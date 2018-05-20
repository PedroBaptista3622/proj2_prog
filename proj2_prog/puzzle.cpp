//COMPILER DIRECTIVES
#include "puzzle.h"
using namespace std;

//CONSTRUCTOR
Puzzle::Puzzle(string filename, bool& control)
	: Board(filename, control)
{
	vector<map<string,char>::iterator> toRemove;

	for (map<string,char>::iterator it = addedChars.begin(); it != addedChars.end(); it++)
	{
		if (it->second != '#')
			toRemove.push_back(it);
	}

	for (int i = 0; i < toRemove.size(); i++)
		addedChars.erase(toRemove.at(i));

	if (!control)
		getHints();
}

//PUBLIC MEMBER FUNCTIONS

/**
 * New interface for the Board linkDic function
 */
void Puzzle::provideBackupDictionary(Dictionary* dictionary, bool replace) //DONE
{
	linkDic(dictionary, replace);

	getHints();
}

/**
 * Shows a synonym for each position
 */
void Puzzle::showSynonyms()
{
	//Prints horizontal synonyms
	setcolor(BLACK, WHITE_B);
	cout << "HORIZONTAL WORDS:";
	setcolor(DEFAULT_TEXT, DEFAULT_BG);
	cout << endl;
	for (map<string,string>::iterator it = words.begin(); it != words.end(); it++)
	{
		if (it->first.at(it->first.length() - 1) == 'H')
		{
			cout << it->first << ": " << hints.find(it->second)->second << endl;
		}
	}
	cout << endl;

	//Prints vertical synonyms
	setcolor(BLACK, WHITE_B);
	cout << "VERTICAL WORDS:";
	setcolor(DEFAULT_TEXT, DEFAULT_BG);
	cout << endl;
	for (map<string,string>::iterator it = words.begin(); it != words.end(); it++)
	{
		if (it->first.at(it->first.length() - 1) == 'V')
		{
			cout << it->first << ": " << hints.find(it->second)->second << endl;
		}
	}
	cout << endl;
}

/**
 * Tries to insert a word from the dictionary into the board, checking
 * for any ilegal overlap, inexistent words, repeated words, and lack of
 * space. Then updates the black space list.
 * <p>
 * Returns the following exit codes:
 * <p>
 *  0: success;
 * <p>
 * -1: excessive length
 * <p>
 * -2: ilegal overlap
 * <p>
 * -3: too small
 * <p>
 * -4: repeated words;
 * <p>
 * -5: invalid position;
 * <p>
 * -6: repeated position;
 *
 * @param	position	The position string to insert the word in
 * @param	word		The word to insert
 * @return				The exit code of the procedure
 */
int Puzzle::insWord(string position, string word)
{
	word = stringToUpper(word);
	wordPosition pos(position);

	//invalid position
	if (!pos.inBoard(getLines(),getColumns()))
		return -5;

	//repeated word
	if (guessedWords.find(position) != guessedWords.end())
		return -6;

	//excessive length
	if (word.length() > words.find(position)->second.length())
		return -1;
	//excessively small
	if (word.length() < words.find(position)->second.length())
		return -3;

	//repeated words
	for (map<string,string>::iterator it = guessedWords.begin(); it != guessedWords.end(); it++)
	{
		if (it->second == word)
			return -4;
	}

	map<string, char> charMap = tempMap(pos, word); //provisional store of the characters

	//checks for illegal overlaps and redundant characters
	for (map<string, char>::iterator it = charMap.begin(); it != charMap.end(); it++)
	{
		if (addedChars.find(it->first) != addedChars.end())
		{
			if (addedChars.at(it->first) != it->second)
				return -2;
			else
				charMap.erase(it);
		}
	}

	for (map<string, char>::iterator it = charMap.begin(); it != charMap.end(); it++)
		addedChars.emplace( it->first, it->second );

	guessedWords.emplace(position, stringToUpper(word));

	return 0;
}

/**
 * Removes existing word from the board. Returns -1 if no word in position,
 * 0 if successful.
 *
 * @param	word	The position
 * @return			The exit code of the procedure
 */
int Puzzle::remWord(string position)
{
	if (guessedWords.find(position) == guessedWords.end())
		return -1;
	else
		guessedWords.erase(guessedWords.find(position));

	refill();

	return 0;
}

/**
 * Refills the board with the existing black characters and the characters
 * corresponding to the existing guesses
 */
void Puzzle::refill()
{
	map<string, char> newMap;

	for (map<string, char>::iterator it = addedChars.begin(); it != addedChars.end(); it++)
	{
		if (it->second == '#')
			newMap.emplace(it->first, '#');
	}

	//iterates through all position-word pairs
	for (map<string, string>::iterator par = guessedWords.begin(); par != guessedWords.end(); par++)
	{
		wordPosition position(par->first);
		string word = par->second;


		map<string, char> wordChars = tempMap(position, word); //provisional store of the characters

		//deletes redundant characters
		for (map<string, char>::iterator it = wordChars.begin(); it != wordChars.end(); it++)
		{
			if (newMap.find(it->first) != newMap.end())
			{
				wordChars.erase(it);
			}
		}

		//adds the characters from temporary storage to the new character map
		for (map<string, char>::iterator it = wordChars.begin(); it != wordChars.end(); it++)
			newMap.emplace( it->first, it->second );
	}

	addedChars = newMap;

}
/**
 * Returns a different synonym of the word in the given position, or the
 * same if there is only one
 *
 * @param	position	position of the word whose synonym is returned
 * @return					a different synonym or the same if unique
 */
string Puzzle::anotherHint(string position)
{
	string currentSynonym = hints.find(words.find(position)->second)->second;
	vector<string> moreHints = dictionary->getSynonyms(words.find(position)->second);

	if (moreHints.size() == 1)
		return currentSynonym;
	else
	{
		string another = currentSynonym;

		while (currentSynonym == another)
		{
			srand(time(NULL));
			another = moreHints.at(rand() % moreHints.size());
		}

		return another;
	}
}

/**
 * Returns whether the user's guesses are correct
 *
 * @return		Are the words input by the user the correct ones?
 */
bool Puzzle::correct()
{
	return words == guessedWords;
}

//PRIVATE MEMBER FUNCTIONS

/**
 * Populates the hint map
 */
void Puzzle::getHints()
{
	for (map<string,string>::iterator it = words.begin(); it != words.end(); it++)
	{
		string word = it->second;
		vector<string> synonyms = dictionary->getSynonyms(word);

		srand(time(NULL));
		string synonym = synonyms.at(rand() % synonyms.size());

		hints.emplace(word, synonym);
	}
}
