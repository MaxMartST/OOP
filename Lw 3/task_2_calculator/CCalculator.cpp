#include "pch.h"
#include "CCalculator.h"
#include "CErrorMessage.h"

using namespace std;

namespace
{
bool IsCharCorrect(char ch)
{
	return isalnum(ch) || ch == '_';
}

void UnionSets(set<string>& lhs, const set<string>& rhs)
{
	for (const auto value : rhs)
	{
		lhs.insert(value);
	}
}
}

bool CCalculator::CheckVariable(const string& variable)
{
	if (!IsNameCorrect(variable) || IsFunctionExist(variable) || IsVarExist(variable))
	{
		return false;
	}

	return true;
}

void CCalculator::SetVar(const string& variable)
{
	if (!CheckVariable(variable))
	{
		throw CErrorMessage("ERROR: Invalid name of varible!\n");
	}

	m_variables.insert({ variable, numeric_limits<double>::quiet_NaN() });
}

const map<string, double>& CCalculator::GetVars() const
{
	return m_variables;
}

double CCalculator::GetValue(const string& identifier) const
{
	if (IsVarExist(identifier))
	{
		return m_variables.at(identifier);
	}

	if (IsFunctionExist(identifier))
	{
		return m_functions.at(identifier).value;
	}

	return numeric_limits<double>::quiet_NaN();
}

void CCalculator::LetVarValue(const string& lhs, const string& rhs)
{
	if (rhs.empty() || IsFunctionExist(lhs))
	{
		throw CErrorMessage("ERROR: Invalid expression!\n");
	}

	if (!IsVarExist(lhs))
	{
		SetVar(lhs);
	}

	if (IsVarExist(rhs))
	{
		m_variables[lhs] = GetValue(rhs);
	}
	else if (!CheckVariable(rhs))
	{
		m_variables[lhs] = stod(rhs);
	}
	else
	{
		throw CErrorMessage("ERROR: Unrecognized variable [" + rhs + "]\n");
	}

	for (const auto& functionName : m_usedFunctions[lhs])
	{
		CalculateFunctionValue(functionName);
	}
}

bool CCalculator::IsNameCorrect(const string& id) const
{
	if (id.empty() || isdigit(*id.begin()) || !all_of(id.begin(), id.end(), IsCharCorrect))
	{
		return false;
	}

	return true;
}

bool CCalculator::IsVarExist(const string& id) const
{
	return m_variables.find(id) != m_variables.end();
}

bool CCalculator::IsFunctionExist(const string& id) const
{
	return m_functions.find(id) != m_functions.end();
}

bool CCalculator::HasIdentifier(const std::string & id) const
{
	return IsFunctionExist(id) || IsVarExist(id);
}

const map<string, SFunctionData>& CCalculator::GetFunctions()
{
	return m_functions;
}

void CCalculator::SetFunction(const string& varFunction, const string& variable)
{
	if (!HasIdentifier(variable))
	{
		throw CErrorMessage("ERROR: Identifier [" + variable + "] has not been advertised\n");
	}

	SFunctionData functionInfo;
	functionInfo.firstOperand = variable;
	m_functions.insert(make_pair(varFunction, functionInfo));
	CalculateFunctionValue(varFunction);

	if (IsVarExist(variable))
	{
		m_usedVariables[varFunction].insert(variable);
	}
	else
	{
		m_usedVariables[varFunction] = m_usedVariables[variable];
	}

	for (const auto& element : m_usedVariables[varFunction])
	{
		m_usedFunctions[element].push_back(varFunction);
	}
}

void CCalculator::SetFunction(const string& varFunction, const string& firstId, Operator operatorFunction, const string& secondId)
{
	if (operatorFunction == Operator::None)
	{
		throw CErrorMessage("ERROR: Incorrect operation\n");
	}

	if (!HasIdentifier(firstId))
	{
		throw CErrorMessage("ERROR: Identifier [" + firstId + "] has not been advertised\n");
	}

	if (!HasIdentifier(secondId))
	{
		throw CErrorMessage("ERROR: Identifier [" + secondId + "] has not been advertised\n");
	}

	SFunctionData functionInfo;
	functionInfo.firstOperand = firstId;
	functionInfo.secondOperand = secondId;
	functionInfo.operatorType = operatorFunction;

	m_functions.insert({ varFunction, functionInfo });
	CalculateFunctionValue(varFunction);

	if (IsVarExist(firstId))
	{
		m_usedVariables[varFunction].insert(firstId);
	}
	else
	{
		UnionSets(m_usedVariables[varFunction], m_usedVariables[firstId]);
	}

	if (IsVarExist(secondId))
	{
		m_usedVariables[varFunction].insert(secondId);
	}
	else
	{
		UnionSets(m_usedVariables[varFunction], m_usedVariables[secondId]);
	}

	for (const auto& element : m_usedVariables[varFunction])
	{
		m_usedFunctions[element].push_back(varFunction);
	}
}

void CCalculator::CalculateFunctionValue(const string & functionName)
{
	if (IsFunctionExist(functionName))
	{
		auto & function = m_functions.at(functionName);

		if (!(function.operatorType == Operator::None))
		{
			CalculateTwoOperandsFunction(function);
		}
		else
		{
			function.value = GetValue(function.firstOperand);
		}
	}
}

void CCalculator::CalculateTwoOperandsFunction(SFunctionData& functionInfo)
{
	double firstOperand = GetValue(functionInfo.firstOperand);
	double secondOperand = GetValue(functionInfo.secondOperand);

	if (!isnan(firstOperand) && !isnan(secondOperand))
	{
		double result = numeric_limits<double>::quiet_NaN();

		switch (functionInfo.operatorType)
		{
		case Operator::Plus:
			result = firstOperand + secondOperand;
			break;
		case Operator::Division:
			result = firstOperand / secondOperand;
			break;
		case Operator::Multiplication:
			result = firstOperand * secondOperand;
			break;
		case Operator::Minus:
			result = firstOperand - secondOperand;
			break;
		}

		functionInfo.value = result;
	}
}