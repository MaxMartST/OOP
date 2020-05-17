#include "CheckArguments.h"

using namespace std;

bool IsCharCorrect(char ch)
{
	return isdigit(ch) || ch == '.';
}

bool CheckCoordinate(string& coordinate)
{
	string::iterator it = coordinate.begin();

	if (isdigit(*it) || *it == '-')
	{
		it++;
	}

	if (all_of(it, coordinate.end(), [](char ch) { return IsCharCorrect(ch); }))
	{
		return true;
	}

	return false;
}

bool CheckColor(string& color)
{
	if (all_of(color.begin(), color.end(), [](char ch) { return isalnum(ch); }) && color.size() == 6)
	{
		return true;
	}

	return false;
}