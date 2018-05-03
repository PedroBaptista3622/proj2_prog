#include "stdafx.h"
#include "Dictionary.h"


Dictionary::Dictionary()
{
	bool fileOpened = false;
	cout << "Please insert dictionary name" << endl;
	cin >> name;

	ifstream dict;
	dict.open(name);


	if (dict.fail())
	{
		cerr << "Error opening dictionary file" << endl;
	}
	else
	{
		fileOpened = true;
		cout << "Dictionary file successfully opened" << endl;
	}

	if (fileOpened)
	{
		cout << "Importing words from dictionary" << endl;

		string word;
		vector <string> synonyms;
		string currentWord;
		string currentLine = "Testeeee";

		while (getline(dict, currentLine))
		{
			cout << currentLine << endl;

			size_t c = currentLine.find(':');
			bool end = false;

			if (c != std::string::npos)
			{
				word = currentLine.substr(0, c);
				currentLine = currentLine.substr(c + 1);

				/*Example:

				Aback: backwards, rearwards, aft, abaft, astern, behind, back

				word = "Aback"
				currentLine = "backwards, rearwards, aft, abaft, astern, behind, back" + CR and LF
				*/

				c = currentLine.find(',');

				if (c == std::string::npos)
				{
					c = currentLine.find((char)13); // Checks if it's the end of the line (newline char)
					if (!c > 2)
					{
						end = true;
					}
				}

				while (!end)
				{
					if (c == std::string::npos)
					{
						c = currentLine.find((char)13); // Checks if it's the end of the line (newline char)
						end = true;
					}

					currentWord = currentLine.substr(0, c);
					synonyms.push_back(currentWord);


					/*

					1st time executing: (from the previous example)
					currentWord = "backwards"
					currentLine = "rearwards, aft, abaft, astern, behind, back" + CR and LF
					...
					last time executing:
					currentWord = "back"
					currentLine = CR and LF

					*/


					if (!end)
					{
						currentLine = currentLine.substr(c + 1);
						c = currentLine.find(',');
					}


				}

				dictionary[word] = synonyms;
				synonyms.clear();

			}
			else
			{
				cerr << "Error importing words" << endl;
			}


		}

		dict.close();
		cout << "Words successfully imported" << endl;

	}


}

void Dictionary::delSpaces()
{
	for (auto elem : dictionary)
	{
		for (int i = 0; i < elem.second.size(); i++)
		{
			if (elem.second.at(i).at(0) == ' ')
			{
				elem.second.at(i) = elem.second.at(i).substr(1);
			}
		}
	}
}

void Dictionary::printDictionary()
{
	for (auto elem : dictionary)
	{
		cout << elem.first << ": ";

		for (int i = 0; i < elem.second.size(); i++)
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