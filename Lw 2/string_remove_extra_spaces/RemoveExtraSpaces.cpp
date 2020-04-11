#include "RemoveExtraSpaces.h"

using namespace std;

string RemoveExtraSpaces(string const& str)
{
	if (str.empty())
	{
		return str;
	}

	istringstream ist(str);
	ostringstream ost;

	copy(istream_iterator<std::string>(ist), istream_iterator<std::string>(), ostream_iterator<string>(ost, " "));
	string resultStr = ost.str();

	size_t size = resultStr.size();

	if (size > 1 && resultStr[size - 1] == ' ')
	{
		resultStr.erase(size - 1, 1); 
	}

	return resultStr;
}

void RemoveExtraSpacesFromStream(istream& input, ostream& output)
{
	string line;
	while (getline(input, line))
	{
		output << RemoveExtraSpaces(line);

		if (!input.eof())
		{
			output << "\n";
		}
	}
}