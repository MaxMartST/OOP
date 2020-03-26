#include "RemoveExtraSpaces.h"

std::string RemoveExtraSpaces(std::string const& str)
{
	if (str.empty())
	{
		return str;
	}

	std::string newStr = str;

	newStr.erase(std::unique_copy(newStr.begin(), newStr.end(), newStr.begin(), [](char c1, char c2) { return c1 == ' ' && c2 == ' '; }), newStr.end());

	unsigned length = static_cast<unsigned>(newStr.length() - 1);

	if (newStr[length] == ' ')
	{
		newStr.erase(length, 1);
	}

	if (newStr[0] == ' ')
	{
		newStr.erase(0, 1);
	}

	return newStr;
}

void RemoveExtraSpacesFromStream(std::istream& input, std::ostream& output)
{
	std::string line;
	bool isFirstLine = true;
	while (!input.eof())
	{
		getline(input, line);

		if (!isFirstLine)
		{
			output << "\n";
		}

		output << RemoveExtraSpaces(line);
		isFirstLine = false;
	}
}