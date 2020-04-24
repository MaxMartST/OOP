#pragma once

#include "CCalculator.h"
#include <functional>
#include <sstream>

class CCalculatorMenu
{
public:
	CCalculatorMenu(CCalculator& calculator, std::istream& input, std::ostream& output);
	bool SetCommand();
	
private:
	void SetVar(std::istream& args);
	void LetVarValue(std::istream& args);
	void SetFunction(std::istream& args);

	void PrintIdentifierValue(std::istream& args);

	void PrintVariables();
	void PrintFunctions();

	void ParseStrToValue(const std::string& str, std::string& firstValue, std::string& secondValue);
	
	typedef std::map<std::string, std::function<void(std::istream& args)>> ActionMap;
	std::istream& m_input;
	std::ostream& m_output;

	CCalculator& m_calculator;

	const ActionMap m_actionMap;
};