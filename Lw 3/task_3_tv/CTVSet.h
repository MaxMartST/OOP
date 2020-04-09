#pragma once

#include <boost/bimap.hpp>

typedef boost::bimap<int, std::string> ChannelStructure;
typedef ChannelStructure::value_type ChannelAndName;

class CTVSet
{
public:
	CTVSet();
	bool IsTurnedOn() const;
	void TurnOn();
	void TurnOff();
	int GetChannel() const;
	void SelectChannel(int channel);
	void SelectPreviousChannel();
	void SetChannelName(const int channelNumber, const std::string& channelName);
	std::string GetChannelName(const int channel) const;
	int GetChannelByName(const std::string& channel) const;

private:
	bool m_isOn = false;
	int m_channel = 1;			
	int m_previousChannel = 1;	
	ChannelStructure m_channelList;	

	static constexpr int MIN_CHANNEL = 1;
	static constexpr int MAX_CHANNEL = 99;
};
