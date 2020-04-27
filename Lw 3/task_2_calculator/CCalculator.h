#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

enum class Operator
{
	Plus,
	Minus,
	Multiplication,
	Division,
	None
};

struct SFunctionData
{
	SFunctionData()
		: operatorType(Operator::None)
	{
	}

	double value = std::numeric_limits<double>::quiet_NaN();
	std::string firstOperand;
	std::string secondOperand;
	Operator operatorType;
};

static const std::map<std::string, Operator> SYMBOLS_OPERATORS{
	{ "+", Operator::Plus },
	{ "-", Operator::Minus },
	{ "*", Operator::Multiplication },
	{ "/", Operator::Division }
};

class CCalculator
{
public:
	void SetVar(const std::string& variable);
	const std::map<std::string, double>& GetVars() const;
	double GetValue(const std::string& identifier) const;
	void LetVarValue(const std::string& lhs, const std::string& rhs);

	const std::map<std::string, SFunctionData>& GetFunctions();
	void SetFunction(const std::string& varFunction, const std::string& variable);
	void SetFunction(const std::string& varFunction, const std::string& firstIdentifier, Operator operatorFunction, const std::string& secondIdentifier);

	bool HasIdentifier(const std::string& id) const;
	bool IsNameCorrect(const std::string& id) const;

private:
	bool IsVarExist(const std::string& variable) const;
	bool IsFunctionExist(const std::string& nameFunction) const;
	bool CheckVariable(const std::string& variable);
	void CalculateFunctionValue(const std::string& function);
	void CalculateTwoOperandsFunction(SFunctionData& functionInfo);

	std::map<std::string, SFunctionData> m_functions;
	std::map<std::string, double> m_variables;
	std::map<std::string, std::vector<std::string>> m_usedFunctions;
	std::map<std::string, std::set<std::string>> m_usedVariables;
};
