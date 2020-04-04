#include "RemoveExtraSpaces.h"

std::string RemoveExtraSpaces(std::string const& str)
{
	if (str.empty())
	{
		return str;
	}

	std::istringstream ist(str);
	std::ostringstream ost;

	std::copy(std::istream_iterator<std::string>(ist), std::istream_iterator<std::string>(), std::ostream_iterator<std::string>(ost, " "));
	std::string resultStr = ost.str();

	size_t size = resultStr.size();

	if (size > 1 && resultStr[size - 1] == ' ')
	{
		resultStr.erase(size - 1, 1); 
	}

	return resultStr;
}

void RemoveExtraSpacesFromStream(std::istream& input, std::ostream& output)
{
	std::string line;
	while (getline(input, line))
	{
		output << RemoveExtraSpaces(line);

		if (!input.eof())
		{
			output << "\n";
		}
	}
}