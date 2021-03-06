#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include "../../catch2/catch.hpp"
#include "../task_3_tv/CErrorMessage.h"
#include "../task_3_tv/CRemoteControl.h"
#include "../task_3_tv/CTVSet.h"
#include "../task_3_tv/EditChannelName.h"
#include "../task_3_tv/pch.h"

using namespace std;
using namespace std::placeholders;

TEST_CASE("Check the TV interface when the state is on and off")
{
	CTVSet tv;
	stringstream input, output;
	CRemoteControl remoteControl(tv, input, output);

	SECTION("Channel number on first start is 1")
	{
		REQUIRE(!tv.IsTurnedOn());

		input << "TurnOn";
		REQUIRE(remoteControl.SetCommand());
		REQUIRE(tv.IsTurnedOn());
		REQUIRE(tv.GetChannel() == 1);

		REQUIRE(output.str() == "TV is turned on\n");
	}

	SECTION("TV status is changing, turned off")
	{
		input << "TurnOff";
		remoteControl.SetCommand();

		REQUIRE(!tv.IsTurnedOn());
		REQUIRE(output.str() == "TV is turned off\n");
	}

	SECTION("Display the channel number after the first start of the TV. Channel number is 1")
	{
		tv.TurnOn();

		input << "Info";
		remoteControl.SetCommand();
		REQUIRE(output.str() == "TV is turned on\nChannel is: 1\n");
	}

	SECTION("Find out the channel number when the TV is off")
	{
		REQUIRE(!tv.IsTurnedOn());

		input << "Info";
		remoteControl.SetCommand();

		REQUIRE(output.str() == "TV is turned off\n");
	}
}

TEST_CASE("Get channel information or complete channel information with associated names, sorted in ascending order of channel number")
{
	CTVSet tv;
	stringstream input, output;
	CRemoteControl remoteControl(tv, input, output);

	tv.TurnOn();
	REQUIRE(tv.IsTurnedOn());

	tv.SetChannelName(2, "my sport");
	tv.SetChannelName(24, "vesty");
	tv.SetChannelName(3, "culture");

	SECTION("Find out which channel is on")
	{
		input << "Info";
		REQUIRE(remoteControl.SetCommand());
		REQUIRE(tv.GetChannel() == 1);

		REQUIRE(output.str() == "TV is turned on\nChannel is: 1\n");
	}

	SECTION("A list of channels associated with the names was displayed")
	{
		input << "Info     Full     ";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(RemoveExtraSpacesInLine("     Full     ") == "Full");
		REQUIRE(tv.GetChannel() == 1);

		REQUIRE(output.str() == "2 - my sport\n3 - culture\n24 - vesty\n");
	}

	SECTION("Invalid command")
	{
		input << "Info Fulllll";
		REQUIRE(!remoteControl.SetCommand());
	}

	SECTION("Turned off TV when requested: Info Full")
	{
		tv.TurnOff();

		input << "Info Full";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(output.str() == "TV is turned off\n");
	}
}

TEST_CASE("TV channel switching")
{
	CTVSet tv;
	stringstream input, output;
	CRemoteControl remoteControl(tv, input, output);

	tv.TurnOn();
	REQUIRE(tv.IsTurnedOn());

	tv.SetChannelName(2, "my sport");
	tv.SetChannelName(24, "vesty");
	tv.SetChannelName(3, "culture");

	SECTION("Switch to channel number 2, TV on")
	{
		input << "SelectChannel 2";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(tv.GetChannel() == 2);
		REQUIRE(output.str() == "Channel changed to 2\n");
	}

	SECTION("Switch to a channel named my sports, TV on")
	{
		input << "SelectChannel my sport";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(tv.GetChannel() == 2);
		REQUIRE(output.str() == "Channel changed to 2\n");
	}

	SECTION("Switch to a channel with a nonexistent name vesty NET, TV on")
	{
		input << "SelectChannel vesty NET";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(tv.GetChannel() == 1);
		REQUIRE(output.str() == "ERROR: Channel named [vesty NET] not found\n");
	}

	SECTION("Switch to channel number 2, TV off")
	{
		tv.TurnOff();
		REQUIRE(!tv.IsTurnedOn());

		input << "SelectChannel 2";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(output.str() == "ERROR: Turned off TV can't switches channel\n");
	}

	SECTION("Channel number out of range. Channel > MAX_CHANNEL")
	{
		input << "SelectChannel 100";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(output.str() == "ERROR: Channel is out of range\n");
	}

	SECTION("Channel number out of range. Channel < MIN_CHANNEL")
	{
		input << "SelectChannel 0";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(output.str() == "ERROR: Channel is out of range\n");
	}

	SECTION("Invalid command")
	{
		input << "Channel";
		REQUIRE(!remoteControl.SetCommand());
	}

	SECTION("Select Previous Channel")
	{
		int number = 2;
		tv.SelectChannelByNumber(number);

		input << "PreviousChannel";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(tv.GetChannel() == 1);
		REQUIRE(output.str() == "Channel changed to 1\n");
	}
}

TEST_CASE("Ability to give a name, number to a channel")
{
	CTVSet tv;
	stringstream input, output;
	CRemoteControl remoteControl(tv, input, output);

	tv.TurnOn();
	REQUIRE(tv.IsTurnedOn());

	tv.SetChannelName(2, "my sport");
	tv.SetChannelName(24, "vesty");
	tv.SetChannelName(3, "culture");

	SECTION("Give channel 27 the name vesty NET and find the channel by number and name")
	{
		input << "SetChannelName 27 vesty NET";

		REQUIRE(remoteControl.SetCommand());
		REQUIRE(output.str() == "Channel saved: 27 - vesty NET\n");

		int numberChannel = tv.GetChannelByName("vesty NET");

		REQUIRE(numberChannel == 27);

		string nameChannel = tv.GetChannelName(27);

		REQUIRE(nameChannel == "vesty NET");
	}

	SECTION("Channel name not specified")
	{
		input << "SetChannelName 24";

		REQUIRE(remoteControl.SetCommand());
		REQUIRE(output.str() == "ERROR: Channel name not specified\n");
	}

	SECTION("Channel name consists of spaces only")
	{
		input << "SetChannelName 24   ";

		REQUIRE(RemoveExtraSpacesInLine("   ").empty());

		REQUIRE(remoteControl.SetCommand());
		REQUIRE(output.str() == "ERROR: Channel name not specified\n");
	}
}

TEST_CASE("Search channel by number or by name")
{
	CTVSet tv;
	stringstream input, output;
	CRemoteControl remoteControl(tv, input, output);

	tv.TurnOn();
	REQUIRE(tv.IsTurnedOn());

	tv.SetChannelName(2, "my sport");
	tv.SetChannelName(24, "vesty");
	tv.SetChannelName(3, "culture");

	SECTION("Find channel name at number 24")
	{
		input << "WhatChannelName 24";

		REQUIRE(remoteControl.SetCommand());
		REQUIRE(tv.GetChannelName(24) == "vesty");
	}

	SECTION("Find channel name at name space")
	{
		input << "WhatChannelNumber my        sport";

		REQUIRE(remoteControl.SetCommand());
		REQUIRE(RemoveExtraSpacesInLine(" my        sport") == "my sport");
		REQUIRE(tv.GetChannelByName("my sport") == 2);
		REQUIRE(output.str() == "2 - my sport\n");
	}

	SECTION("Find the name of the unnamed channel at number 9")
	{
		input << "WhatChannelName      9";

		REQUIRE(remoteControl.SetCommand());
		REQUIRE(RemoveExtraSpacesInLine("      9") == "9");
		REQUIRE(tv.GetChannelName(9) == "");
		REQUIRE(tv.GetChannel() == 1);
		REQUIRE(output.str() == "\n");
	}

	SECTION("Find channel name out of range")
	{
		input << "WhatChannelName 101";

		REQUIRE(remoteControl.SetCommand());
		REQUIRE(tv.GetChannel() == 1);
		REQUIRE(output.str() == "ERROR: Channel is out of range\n");
	}

	SECTION("Find a channel number that does not exist")
	{
		input << "WhatChannelNumber vesty NET";

		REQUIRE(remoteControl.SetCommand());
		REQUIRE(tv.GetChannel() == 1);
		REQUIRE(output.str() == "0\n");
	}
}

TEST_CASE("Delete channel name")
{
	CTVSet tv;
	stringstream input, output;
	CRemoteControl remoteControl(tv, input, output);

	tv.TurnOn();
	REQUIRE(tv.IsTurnedOn());

	tv.SetChannelName(2, "my sport");
	tv.SetChannelName(24, "vesty");
	tv.SetChannelName(3, "culture");

	SECTION("Delete channel name vesty")
	{
		input << "DeleteChannelName       vesty";

		REQUIRE(remoteControl.SetCommand());
		REQUIRE(RemoveExtraSpacesInLine(" vesty") == "vesty");

		ChannelStructure channelList = tv.GetListChannels();

		auto myList = channelList.left;

		for (auto it = myList.begin(); it != myList.end(); ++it)
		{
			output << it->first << " - " << it->second << "\n";
		}

		REQUIRE(output.str() == "2 - my sport\n3 - culture\n");
	}

	SECTION("Delete channel name vesty NET . Channel with this name does not exist")
	{
		input << "DeleteChannelName vesty NET ";

		REQUIRE(remoteControl.SetCommand());
		REQUIRE(RemoveExtraSpacesInLine(" vesty NET ") == "vesty NET");

		REQUIRE(output.str() == "ERROR: Channel named [vesty NET] not found\n");
	}
}