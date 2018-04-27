#include "stdafx.h"
#include "board.h"
using namespace std;

bool operator<(string s1, string s2)
{
	bool smaller = (s1.size() < s2.size());
	int maxcompare;
	if (smaller)
		maxcompare = s1.size();
	else
		maxcompare = s2.size();
	for (int i = 0; i < maxcompare; i++)
	{
		if (s1.at(i) != s2.at(i))
			return s1.at(i) < s2.at(i);
	}
	return smaller;
}