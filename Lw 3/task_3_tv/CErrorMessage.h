#pragma once
class CErrorMessage
{
public:
	CErrorMessage(const std::string& msg)
		: m_message(msg)
	{
	}
	std::string GetErrorMessage() const;
	virtual void PrintErrorMessage() const;
	virtual ~CErrorMessage() = default;

private:
	std::string m_message;
};
