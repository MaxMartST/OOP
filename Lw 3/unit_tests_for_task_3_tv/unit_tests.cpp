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
		tv.SelectChannelByNumber(2);

		input << "PreviousChannel";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(tv.GetChannel() == 1);
		REQUIRE(output.str() == "Channel changed to 1\n");
	}
}

TEST_CASE("Ability to give a name, number to a channel and search for it by name and number")
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
		REQUIRE(tv.GetChannel() == 1);
		REQUIRE(output.str() == "ERROR: Channel [9] has no name\n");
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
		REQUIRE(output.str() == "ERROR: Channel named [vesty NET] not found\n");
	}
}