#pragma once
#include <string>

class CErrorMessage
{
public:
	CErrorMessage(const std::string& msg)
		: m_message(msg)
	{
	}

	std::string GetErrorMessage() const;
	virtual ~CErrorMessage() = default;

private:
	std::string m_message;
};