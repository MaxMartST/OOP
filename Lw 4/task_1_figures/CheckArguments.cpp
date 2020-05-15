#include "CheckArguments.h"

bool CheckCoordinate(std::string& coordinate)
{
	if (all_of(coordinate.begin(), coordinate.end(), [](char ch){return isdigit(ch);}))
	{
		return false;
	}

	return true;
}

bool CheckColor(std::string& color)
{
	if (all_of(color.begin(), color.end(), [](char ch) { return isalnum(ch); }))
	{
		return false;
	}

	return true;
}