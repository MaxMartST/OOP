#include "pch.h"
#include "CRemoteControl.h"
#include "CErrorMessage.h"
#include "CTVSet.h"
#include "edit_channel_name.h"

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
		  { "InfoAll", bind(&CRemoteControl::InfoAll, this, _1) },
		  { "SelectChannel", bind(&CRemoteControl::SelectChannel, this, _1) },
		  { "PreviousChannel", bind(&CRemoteControl::PreviousChannel, this, _1) },
		  { "SetChannelName", bind(&CRemoteControl::SetChannelName, this, _1) },
		  { "WhatChannelNumber", bind(&CRemoteControl::WhatChannelNumber, this, _1) },
		  { "WhatChannelName", bind(&CRemoteControl::WhatChannelName, this, _1) },
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

bool CRemoteControl::TurnOn(istream&)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << endl;
	return true;
}

bool CRemoteControl::TurnOff(istream&)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << endl;
	return true;
}

bool CRemoteControl::Info(istream& args)
{
	string info = (m_tv.IsTurnedOn()) ? ("TV is turned on\nChannel is: " + to_string(m_tv.GetChannel()) + "\n") : "TV is turned off\n";

	m_output << info;

	return true;
}

bool CRemoteControl::InfoAll(istream& args)
{
	ChannelStructure channelList = m_tv.GetListChannels();

	auto myList = channelList.left;

	for (auto it = myList.begin(); it != myList.end(); ++it)
	{
		m_output << it->first << " - " << it->second << "\n";
	}

	return true;
}

bool CRemoteControl::SelectChannel(istream& args)
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

bool CRemoteControl::PreviousChannel(istream& args)
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

bool CRemoteControl::SetChannelName(istream& args)
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

bool CRemoteControl::WhatChannelNumber(istream& args)
{
	string channelName = *istream_iterator<string>(args);

	m_output << to_string(m_tv.GetChannelByName(channelName)) + " - " + channelName << endl;

	return true;
}

bool CRemoteControl::WhatChannelName(istream& args)
{
	int channelNumber = *istream_iterator<int>(args);

	m_tv.GetChannelName(channelNumber);

	m_output << to_string(channelNumber) + " - " + m_tv.GetChannelName(channelNumber) << endl;

	return true;
}