#pragma once

#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <iostream>
#include <memory>
#include <vector>

class CCommandHandler
{
public:
	CCommandHandler(std::istream& input, std::ostream& output);
	void HandleCommand();

private:
	std::istream& m_input;
	std::ostream& m_output;
};
