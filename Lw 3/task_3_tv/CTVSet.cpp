#include "pch.h"
#include "CErrorMessage.h"
#include "CTVSet.h"

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

int CTVSet::GetChannel() const
{
	return m_isOn ? m_channel : 0;
}

void CTVSet::SelectChannel(const int channel)
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

	m_channel = m_previousChannel;
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
	m_channelList.insert(ChannelAndName(channelNumber, channelName));
}

string CTVSet::GetChannelName(const int channelNumber) const
{
	return m_channelList.left.at(channelNumber);
}

int CTVSet::GetChannelByName(const string& channelName) const
{
	return m_channelList.right.at(channelName);
}