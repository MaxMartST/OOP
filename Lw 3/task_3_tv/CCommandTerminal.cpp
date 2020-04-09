#include "pch.h"
#include "edit_channel_name.h"
#include "CErrorMessage.h"
#include "CCommandTerminal.h"
#include "CTVSet.h"

using namespace std;
using namespace boost::placeholders;

CCommandTerminal::CCommandTerminal(CTVSet& tv, istream& input, ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "TurnOn", [this](istream& strm) { return TurnOn(strm); } },
		  { "TurnOff", bind(&CCommandTerminal::TurnOff, this, _1) },
		  { "Info", bind(&CCommandTerminal::Info, this, _1) },
		  { "SelectChannel", bind(&CCommandTerminal::SelectChannel, this, _1) },
		  { "PreviousChannel", bind(&CCommandTerminal::PreviousChannel, this, _1) },
		  { "SetChannelName", bind(&CCommandTerminal::SetChannelName, this, _1) },
		  { "WhatChannelNumber", bind(&CCommandTerminal::WhatChannelNumber, this, _1) },
		  { "WhatChannelName", bind(&CCommandTerminal::WhatChannelName, this, _1) },
	  })
{
}

bool CCommandTerminal::SetCommand()
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

bool CCommandTerminal::TurnOn(istream&)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << endl;
	return true;
}

bool CCommandTerminal::TurnOff(istream&)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << endl;
	return true;
}

bool CCommandTerminal::Info(istream& args)
{
	string info = (m_tv.IsTurnedOn()) ? ("TV is turned on\nChannel is: " + to_string(m_tv.GetChannel()) + "\n") : "TV is turned off\n";

	m_output << info;

	return true;
}

bool CCommandTerminal::SelectChannel(istream& args)
{
	int channelNumber = *istream_iterator<int>(args);

	try
	{
		m_tv.SelectChannel(channelNumber);
		m_output << "Channel changed to " + to_string(m_tv.GetChannel()) + "\n";
	}
	catch (CErrorMessage e)
	{
		m_output << e.GetErrorMessage();
	}

	return true;
}

bool CCommandTerminal::PreviousChannel(istream& args)
{
	try
	{
		m_tv.SelectPreviousChannel();
		m_output << "Channel changed to " + to_string(m_tv.GetChannel()) + "\n";
	}
	catch (CErrorMessage e)
	{
		m_output << e.GetErrorMessage();
	}

	return true;
}

bool CCommandTerminal::SetChannelName(istream& args)
{
	int channelNumber = *istream_iterator<int>(args);
	string channelName;

	getline(args, channelName);
	RemoveExtraSpacesInLine(channelName);

	try
	{
		m_tv.SetChannelName(channelNumber, channelName);
		m_output << "Channel saved: " + to_string(channelNumber) + " - " + channelName + "\n";
	}
	catch (CErrorMessage e)
	{
		m_output << e.GetErrorMessage();
	}

	return true;
}

bool CCommandTerminal::WhatChannelNumber(istream& args)
{
	string channelName = *istream_iterator<string>(args);

	m_tv.GetChannelByName(channelName);

	m_output << to_string(m_tv.GetChannelByName(channelName)) + " - " + channelName << endl;

	return true;
}

bool CCommandTerminal::WhatChannelName(istream& args)
{
	int channelNumber = *istream_iterator<int>(args);

	m_tv.GetChannelName(channelNumber);

	m_output << to_string(channelNumber) + " - " + m_tv.GetChannelName(channelNumber) << endl;

	return true;
}