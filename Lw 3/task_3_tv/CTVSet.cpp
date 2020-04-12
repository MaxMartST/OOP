#include "pch.h"
#include "CTVSet.h"
#include "CErrorMessage.h"

using namespace std;

CTVSet::CTVSet()
{
}

bool CTVSet::IsTurnedOn() const
{
	return m_isOn;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

ChannelStructure CTVSet::GetListChannels()
{
	return m_channelList;
}

int CTVSet::GetChannel() const
{
	return m_isOn ? m_channel : 0;
}

void CTVSet::SelectChannelByName(const string& name)
{
	if (!m_isOn)
	{
		throw CErrorMessage("ERROR: Turned off TV can't switches channel\n");
	}

	ChannelStructure::right_const_iterator rightIter = m_channelList.right.find(name);

	if (rightIter != m_channelList.right.end())
	{
		m_previousChannel = m_channel;
		m_channel = m_channelList.right.at(name);
	}
	else
	{
		throw CErrorMessage("ERROR: Channel named [" + name + "] not found\n");
	}
}

void CTVSet::SelectChannelByNumber(const int& channel)
{
	if (!m_isOn)
	{
		throw CErrorMessage("ERROR: Turned off TV can't switches channel\n");
	}

	if (channel < MIN_CHANNEL || channel > MAX_CHANNEL)
	{
		throw CErrorMessage("ERROR: Channel is out of range\n");
	}

	m_previousChannel = m_channel;
	m_channel = channel;
}

void CTVSet::SelectPreviousChannel()
{
	if (!m_isOn)
	{
		throw CErrorMessage("ERROR: Turned off TV can't switches channel\n");
	}

	swap(m_channel, m_previousChannel);
}

void CTVSet::SetChannelName(const int channelNumber, const string& channelName)
{
	if (!m_isOn)
	{
		throw CErrorMessage("ERROR: Turned off TV can't switches channel\n");
	}

	if (channelNumber < MIN_CHANNEL || channelNumber > MAX_CHANNEL)
	{
		throw CErrorMessage("ERROR: Channel is out of range\n");
	}

	if (channelName.empty())
	{
		throw CErrorMessage("ERROR: Channel name not specified\n");
	}

	m_channelList.insert(ChannelAndName(channelNumber, channelName));
}

string CTVSet::GetChannelName(const int channelNumber) const
{
	ChannelStructure::left_const_iterator leftIter = m_channelList.left.find(channelNumber);
	string channelName;

	if (channelNumber < MIN_CHANNEL || channelNumber > MAX_CHANNEL)
	{
		throw CErrorMessage("ERROR: Channel is out of range\n");
	}

	if (leftIter != m_channelList.left.end())
	{
		channelName = m_channelList.left.at(channelNumber);
	}
	else
	{
		throw CErrorMessage("ERROR: Channel [" + to_string(channelNumber) + "] has no name\n");
	}

	return channelName;
}

int CTVSet::GetChannelByName(const string& channelName) const
{
	ChannelStructure::right_const_iterator rightIter = m_channelList.right.find(channelName);

	if (rightIter != m_channelList.right.end())
	{
		return m_channelList.right.at(channelName);
	}
	else
	{
		throw CErrorMessage("ERROR: Channel named [" + channelName + "] not found\n");
	}
}

void CTVSet::DeleteChannelName(const string& channelName)
{
	ChannelStructure::right_const_iterator rightIter = m_channelList.right.find(channelName);

	if (rightIter != m_channelList.right.end())
	{
		m_channelList.right.erase(channelName);
	}
	else
	{
		throw CErrorMessage("ERROR: Channel named [" + channelName + "] not found\n");
	}
}