#pragma once
#include <boost/noncopyable.hpp>

class CTVSet;

// Наследование от boost::noncopyable - явный способ запретить копирование и присваивание экземпляров класса
class CRemoteControl : boost::noncopyable
{
public:
	CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output);
	bool SetCommand();

private:
	bool TurnOn(std::istream& args);
	bool TurnOff(std::istream& args);
	bool Info(std::istream& args);
	bool SelectChannel(std::istream& args);
	bool PreviousChannel(std::istream& args);
	bool SetChannelName(std::istream& args);
	bool WhatChannelNumber(std::istream& args);
	bool WhatChannelName(std::istream& args);
	bool DeleteName(std::istream& args);

private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	CTVSet& m_tv;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;

	const std::string MOD = "Full";
};
