#pragma once

#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

class CCommandHandler
{
public:
	CCommandHandler(std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	std::istream& m_input;
	std::ostream& m_output;
};

std::string RemoveExtraSpacesInLine(std::string stringToTrim);
