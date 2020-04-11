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

	//проверить, есть ли канал с именем name
	//если нет, выкинуть исключение: ƒанный канал не найден

	//auto it = m_channelList.right;

	//ChannelStructure::const_iterator iter = m_channelList.begin();

	ChannelStructure::right_const_iterator rightIter = m_channelList.right.find(name);

	if (rightIter != m_channelList.right.end())
	{
		m_previousChannel = m_channel;
		m_channel = m_channelList.right.at(name);
	}
	else
	{
		throw CErrorMessage("ERROR: Channel named \"" + name + "\" not found\n");
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