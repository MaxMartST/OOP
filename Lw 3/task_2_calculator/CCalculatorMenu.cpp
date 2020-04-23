#include "pch.h"
#include "CCalculatorMenu.h"
#include "CErrorMessage.h"

using namespace std;
using namespace std::placeholders;

CCalculatorMenu::CCalculatorMenu(CCalculator& calculator, istream& input, ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "var", bind(&CCalculatorMenu::SetVar, this, _1) },
		  { "let", bind(&CCalculatorMenu::LetVarValue, this, _1) },
		  { "printvars", bind(&CCalculatorMenu::PrintVariables, this) },
		  { "exit", bind(&CCalculatorMenu::Exit, this) } })
{
}

void CCalculatorMenu::Exit()
{
	m_stausMenu = Status::EXIT;
}

Status CCalculatorMenu::SetCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);

	if (it != m_actionMap.end())
	{
		m_stausMenu = Status::EXECUTE;
		it->second(strm);
	}
	else
	{
		m_stausMenu = Status::ERORR;
	}

	return m_stausMenu;
}

void CCalculatorMenu::SetVar(istream& args)
{
	string identifier;
	args >> identifier;

	//if (!m_calculator.SetVar(identifier))
	//{
	//	cout << "Invalid name of varible!" << endl;
	//}
	try
	{
		m_calculator.SetVar(identifier);
	}
	catch (const CErrorMessage& e)
	{
		m_output << e.GetErrorMessage();
	}
}

void CCalculatorMenu::LetVarValue(istream& args)
{
	string expression;
	args >> expression;

	string firstValue;
	string secondValue;

	try
	{
		ParseStrToValue(expression, firstValue, secondValue);
		m_calculator.LetVarValue(firstValue, secondValue);
	}
	catch (const CErrorMessage& e)
	{
		m_output << e.GetErrorMessage();
	}
	catch (const std::invalid_argument& ia)
	{
		m_output << "Invalid argument: " << ia.what() << '\n';
	}
	catch (const std::out_of_range& oor)
	{
		m_output << "Out of Range error: " << oor.what() << '\n';
	}
}

void CCalculatorMenu::ParseStrToValue(const string& str, string& firstValue, string& secondValue)
{
	auto parsePosition = str.find("=");

	if ((parsePosition == string::npos) || (parsePosition + 1 == str.size()))
	{
		throw CErrorMessage("ERROR: Invalid name of varible!\n");
	}

	firstValue = str.substr(0, parsePosition);
	secondValue = str.substr(parsePosition + 1, str.size());
}

void CCalculatorMenu::PrintVariables()
{
	for (auto it : m_calculator.GetVars())
	{
		cout << it.first << ":" << setprecision(2) << fixed << it.second << endl;
	}
}