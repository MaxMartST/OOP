#include "pch.h"
#include "CTVSet.h"
#include "CErrorMessage.h"

using namespace std;

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

ChannelStructure CTVSet::GetListChannels() const
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
		m_channel = rightIter->second;
	}
	else
	{
		throw CErrorMessage("ERROR: Channel named [" + name + "] not found\n");
	}
}

void CTVSet::SelectChannelByNumber(int& channel)
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
		throw CErrorMessage("ERROR: Turned off TV can't switch channel\n");
	}

	swap(m_channel, m_previousChannel);
}

void CTVSet::SetChannelName(int channelNumber, const string& channelName)
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

string CTVSet::GetChannelName(int channelNumber) const
{
	if (channelNumber < MIN_CHANNEL || channelNumber > MAX_CHANNEL)
	{
		throw CErrorMessage("ERROR: Channel is out of range\n");
	}

	ChannelStructure::left_const_iterator leftIter = m_channelList.left.find(channelNumber);
	string channelName;

	if (leftIter != m_channelList.left.end())
	{
		channelName = leftIter->second;
	}

	return channelName;
}

int CTVSet::GetChannelByName(const string& channelName) const
{
	ChannelStructure::right_const_iterator rightIter = m_channelList.right.find(channelName);
	int channelNumber = 0;

	if (rightIter != m_channelList.right.end())
	{
		channelNumber = rightIter->second;
	}

	return channelNumber;
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