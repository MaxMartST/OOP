#include "CCommandHandler.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <boost/algorithm/string.hpp>

using namespace std;

CCommandHandler::CCommandHandler(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

bool CCommandHandler::HandleCommand()
{
	bool result = true;
	vector<string> argsUrl;
	string inputUrl;
	getline(m_input, inputUrl);

	inputUrl = RemoveExtraSpacesInLine(inputUrl);

	try
	{
		if (inputUrl.empty())
		{
			result = false;
			throw invalid_argument("ERROR: Empty input!\n");
		}

		argsUrl = ConvertStringToVector(inputUrl);

		if (argsUrl.size() == 1)
		{
			CHttpUrl url(argsUrl[0]);
			m_output << "URL: " << url.GetUrl() << endl;
		}

		if (argsUrl.size() == 3)
		{
			Protocol protocol = ConvertStringToProtocol(argsUrl[2]);
			CHttpUrl url(argsUrl[0], argsUrl[1], protocol);
			m_output << "URL: " << url.GetUrl() << endl;
		}

		if (argsUrl.size() == 4)
		{
			Protocol protocol = ConvertStringToProtocol(argsUrl[2]);
			int port = static_cast<int>(strtoul(argsUrl[3].c_str(), NULL, 10));
			CHttpUrl url(argsUrl[0], argsUrl[1], protocol, port);
			m_output << "URL: " << url.GetUrl() << endl;
		}
	}
	catch (invalid_argument const& ia)
	{
		result = false;
		m_output << ia.what();
	}

	return result;
}

string RemoveExtraSpacesInLine(string stringToTrim)
{
	if (stringToTrim.empty())
	{
		return stringToTrim;
	}

	boost::trim(stringToTrim);
	for (string::iterator it = stringToTrim.begin(); it != stringToTrim.end(); it++)
	{
		string::iterator begin = it;
		while (it != stringToTrim.end() && isspace(*it))
		{
			it++;
		}
		if (it - begin > 1)
		{
			it = stringToTrim.erase(begin + 1, it) - 1;
		}
	}

	return stringToTrim;
}

vector<string> ConvertStringToVector(string inputStr)
{
	vector<string> argsUrl;

	if (!inputStr.empty())
	{
		boost::split(argsUrl, inputStr, boost::is_any_of(" "));
	}
	
	return argsUrl;
}
