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
		  { "fn", bind(&CCalculatorMenu::SetFunction, this, _1) },
		  { "print", bind(&CCalculatorMenu::PrintIdentifierValue, this, _1) },
		  { "printfns", bind(&CCalculatorMenu::PrintFunctions, this) } })
{
}

void CCalculatorMenu::SetCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);

	if (it != m_actionMap.end())
	{
		it->second(strm);
	}
	else
	{
		m_output << "Unknown command!\n";
	}
}

void CCalculatorMenu::SetVar(istream& args)
{
	string identifier;
	args >> identifier;

	try
	{
		m_calculator.SetVar(identifier);
	}
	catch (const CErrorMessage& em)
	{
		m_output << em.GetErrorMessage();
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
	catch (const CErrorMessage& em)
	{
		m_output << em.GetErrorMessage();
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

void CCalculatorMenu::SetFunction(istream& args)
{
	string expression;
	args >> expression;
	string firstValue, secondValue, operand, thirdValue;
	Operator expressionOperator;

	try
	{
		ParseStrToValue(expression, firstValue, secondValue);
		ParseStrToAriphOperation(secondValue, expression, expressionOperator, thirdValue);
		
		if (m_calculator.HasIdentifier(firstValue))
		{
			throw CErrorMessage("ERROR: An identifier named [" + firstValue + "] already exists\n");
		}

		if (!m_calculator.IsNameCorrect(firstValue))
		{
			throw CErrorMessage("ERROR: Invalid identifier name [" + firstValue + "]\n");
		}

		if (thirdValue.empty() && expressionOperator == Operator::None)
		{
			m_calculator.SetFunction(firstValue, secondValue);
		}
		else
		{
			m_calculator.SetFunction(firstValue, expression, expressionOperator, thirdValue);
		}
	}
	catch (const CErrorMessage& em)
	{
		m_output << em.GetErrorMessage();
	}
}

void CCalculatorMenu::ParseStrToAriphOperation(const string& str, string& firstValue, Operator& operand, string& secondValue)
{
	auto operandPos = string::npos;
	for (auto elem : SYMBOLS_OPERATORS)
	{
		operandPos = str.find(elem.first);
		if (operandPos != string::npos)
		{
			operand = elem.second;
			break;
		}
	}

	if (operandPos != string::npos)
	{
		firstValue = str.substr(0, operandPos);
		secondValue = str.substr(operandPos + 1, str.size());
	}
	else
	{
		operand = Operator::None;
	}
}

double CCalculatorMenu::FindIdentifierValue(const string& id) const
{
	if (m_calculator.HasIdentifier(id))
	{
		return m_calculator.GetValue(id);
	}
	else
	{
		throw CErrorMessage("ERROR: Identifier [" + id + "] does not exist!\n");
	}
}

void CCalculatorMenu::PrintIdentifierValue(istream& args)
{
	string identifier;
	args >> identifier;

	try
	{
		double value = FindIdentifierValue(identifier);
		ostringstream ost;

		ost << setprecision(2) << fixed << value;
		m_output << identifier + ":" + ost.str() + "\n";
	}
	catch (const CErrorMessage& em)
	{
		m_output << em.GetErrorMessage();
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
		ostringstream ost;
		ost << setprecision(2) << fixed << m_calculator.GetValue(it.first);
		m_output << it.first + ":" + ost.str() + "\n";
	}
}

void CCalculatorMenu::PrintFunctions()
{
	for (auto it : m_calculator.GetFunctions())
	{
		ostringstream ost;
		ost << setprecision(2) << fixed << m_calculator.GetValue(it.first);
		m_output << it.first + ":" + ost.str() + "\n";
	}
}