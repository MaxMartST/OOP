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

void CCommandHandler::HandleCommand()
{
	vector<string> argsUrl;
	string inputUrl;
	getline(m_input, inputUrl);

	if (inputUrl.empty())
	{
		throw invalid_argument("ERROR: Empty input!\n");
	}

	boost::split(argsUrl, inputUrl, boost::is_any_of(" "));
	unique_ptr<CHttpUrl> lineSegment;

	if (argsUrl.size() == 1)
	{
		lineSegment = make_unique<CHttpUrl>(argsUrl[0]);
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

	m_output << lineSegment->GetUrl() << endl;
}
