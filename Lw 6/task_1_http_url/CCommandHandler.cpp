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

		boost::split(argsUrl, inputUrl, boost::is_any_of(" "));
		unique_ptr<CHttpUrl> lineSegment;

		if (argsUrl.size() == 1)
		{
			lineSegment = make_unique<CHttpUrl>(argsUrl[0]);
			m_output << "URL: " << lineSegment->GetUrl() << endl;
		}

		//if (argsUrl.size() == 2)
		//{
		//}

		//if (argsUrl.size() == 3)
		//{
		//}

		//if (argsUrl.size() == 4)
		//{
		//}
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
