#pragma once
#include "pch.h"

class CTVSet
{
public:
	bool IsTurnedOn() const;
	void TurnOn();
	void TurnOff();
	ChannelStructure GetListChannels() const;
	int GetChannel() const;
	void SelectChannelByName(const std::string& name);
	void SelectChannelByNumber(int& channel);
	void SelectPreviousChannel();
	void SetChannelName(int channelNumber, const std::string& channelName);
	std::string GetChannelName(int channel) const;
	int GetChannelByName(const std::string& channel) const;
	void DeleteChannelName(const std::string& channelName);

private:
	bool m_isOn = false;
	int m_channel = 1;
	int m_previousChannel = 1;
	ChannelStructure m_channelList;

	static constexpr int MIN_CHANNEL = 1;
	static constexpr int MAX_CHANNEL = 99;
};
