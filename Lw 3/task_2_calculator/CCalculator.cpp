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
} // namespace

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
		throw CErrorMessage("ERROR: Invalid expression\n");
	}

	// провер€ем, была ли объ€вленна lhs раннее
	// если нет, то инициализинуем
	if (!IsVarExist(lhs))
	{
		SetVar(lhs);
	}

	// если rhs переменна€, объ€вленна€ раннее, то ищем еЄ значение и присваеваем к lhs
	if (IsVarExist(rhs))
	{
		m_variables[lhs] = GetValue(rhs);
	}
	// если rhs не переменна€, то число с плавающей зап€той
	else if (!CheckVariable(rhs))
	{
		m_variables[lhs] = stod(rhs);
	}
	// иначе необъ€вленна€ ранее переменна€(выводим ошибку)
	else
	{
		throw CErrorMessage("ERROR: Unrecognized variable: " + rhs + "\n");
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