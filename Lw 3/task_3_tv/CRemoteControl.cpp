#include "pch.h"
#include "CRemoteControl.h"
#include "CErrorMessage.h"
#include "CTVSet.h"
#include "EditChannelName.h"

using namespace std;
using namespace boost::placeholders;

CRemoteControl::CRemoteControl(CTVSet& tv, istream& input, ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "TurnOn", [this](istream& strm) { return TurnOn(strm); } },
		  { "TurnOff", bind(&CRemoteControl::TurnOff, this, _1) },
		  { "Info", bind(&CRemoteControl::Info, this, _1) },
		  { "SelectChannel", bind(&CRemoteControl::SelectChannel, this, _1) },
		  { "PreviousChannel", bind(&CRemoteControl::PreviousChannel, this, _1) },
		  { "SetChannelName", bind(&CRemoteControl::SetChannelName, this, _1) },
		  { "WhatChannelNumber", bind(&CRemoteControl::WhatChannelNumber, this, _1) },
		  { "WhatChannelName", bind(&CRemoteControl::WhatChannelName, this, _1) },
		  { "DeleteChannelName", bind(&CRemoteControl::DeleteName, this, _1) },
	  })
{
}

bool CRemoteControl::SetCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);

	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CRemoteControl::TurnOn(istream& args)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << endl;
	args.clear();

	return true;
}

bool CRemoteControl::TurnOff(istream& args)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << endl;
	args.clear();

	return true;
}

bool CRemoteControl::Info(istream& args)
{
	string modification;

	getline(args, modification);
	modification = RemoveExtraSpacesInLine(modification);

	if (modification.empty())
	{
		string info = (m_tv.IsTurnedOn()) ? ("TV is turned on\nChannel is: " + to_string(m_tv.GetChannel()) + "\n") : "TV is turned off\n";
		m_output << info;
	
		return true;
	}

	if (modification == MOD && m_tv.IsTurnedOn())
	{
		string resultInfo;

		ChannelStructure channelList = m_tv.GetListChannels();
		auto myList = channelList.left;

		for (auto it = myList.begin(); it != myList.end(); ++it)
		{
			resultInfo += to_string(it->first) + " - " + it->second + "\n";
		}

		m_output << resultInfo;

		return true;
	}

	if (!m_tv.IsTurnedOn())
	{
		m_output << "TV is turned off\n";
		return true;
	}

	return false;
}

bool CRemoteControl::SelectChannel(istream& args)
{
	string queryString, channelName;
	int number;
	getline(args, queryString);

	try
	{
		number = stoi(queryString);
	}
	catch (const std::invalid_argument&)
	{
		channelName = RemoveExtraSpacesInLine(queryString);

		try
		{
			m_tv.SelectChannelByName(channelName);
			m_output << "Channel changed to " + to_string(m_tv.GetChannel()) + "\n";
		}
		catch (CErrorMessage const& e)
		{
			m_output << e.GetErrorMessage();
		}
		args.clear();

		return true;
	}

	try
	{
		m_tv.SelectChannelByNumber(number);
		m_output << "Channel changed to " + to_string(m_tv.GetChannel()) + "\n";
	}
	catch (CErrorMessage const& e)
	{
		m_output << e.GetErrorMessage();
	}
	args.clear();

	return true;
}

bool CRemoteControl::PreviousChannel(istream& args)
{
	try
	{
		m_tv.SelectPreviousChannel();
		m_output << "Channel changed to " + to_string(m_tv.GetChannel()) + "\n";
	}
	catch (CErrorMessage const& e)
	{
		m_output << e.GetErrorMessage();
	}
	args.clear();

	return true;
}

bool CRemoteControl::SetChannelName(istream& args)
{
	string channelName, number;
	int channelNumber;

	args >> number;

	getline(args, channelName);
	channelName = RemoveExtraSpacesInLine(channelName);

	try
	{
		channelNumber = stoi(number);
	}
	catch (const invalid_argument&)
	{
		return false;
	}

	try
	{
		m_tv.SetChannelName(channelNumber, channelName);
		m_output << "Channel saved: " + to_string(channelNumber) + " - " + channelName + "\n";
	}
	catch (CErrorMessage const& e)
	{
		m_output << e.GetErrorMessage();
	}
	args.clear();

	return true;
}

bool CRemoteControl::WhatChannelNumber(istream& args)
{
	string channelName, queryString;
	int channelNumber;

	getline(args, queryString);
	channelName = RemoveExtraSpacesInLine(queryString);

	try
	{
		channelNumber = m_tv.GetChannelByName(channelName);
		(channelNumber) ? m_output << to_string(channelNumber) + " - " + channelName + "\n" : m_output << to_string(channelNumber) + "\n";
	}
	catch (CErrorMessage const& e)
	{
		m_output << e.GetErrorMessage();
	}

	args.clear();

	return true;
}

bool CRemoteControl::WhatChannelName(istream& args)
{
	string queryString, nameChannel;
	int channelNumber;

	args >> queryString;

	try
	{
		channelNumber = stoi(queryString);
	}
	catch (const invalid_argument&)
	{
		return false;
	}

	try
	{
		nameChannel = m_tv.GetChannelName(channelNumber);
		(nameChannel.empty()) ? m_output << nameChannel + "\n" : m_output << to_string(channelNumber) + " - " + nameChannel + "\n";
	}
	catch (CErrorMessage e)
	{
		m_output << e.GetErrorMessage();
	}	
	args.clear();

	return true;
}

bool CRemoteControl::DeleteName(istream& args)
{
	string channelName, queryString;

	getline(args, queryString);
	channelName = RemoveExtraSpacesInLine(queryString);

	try
	{
		m_tv.DeleteChannelName(channelName);
	}
	catch (CErrorMessage const& e)
	{
		m_output << e.GetErrorMessage();
	}
	args.clear();

	return true;
}