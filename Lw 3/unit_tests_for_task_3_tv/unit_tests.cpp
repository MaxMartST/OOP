#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include "../../catch2/catch.hpp"
#include "../task_3_tv/CErrorMessage.h"
#include "../task_3_tv/CRemoteControl.h"
#include "../task_3_tv/CTVSet.h"
#include "../task_3_tv/edit_channel_name.h"
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

	SECTION("Switch to channel number 2, TV on")
	{
		tv.TurnOn();
		REQUIRE(tv.IsTurnedOn());

		input << "SelectChannel 2";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(tv.GetChannel() == 2);
		REQUIRE(output.str() == "Channel changed to 2\n");
	}

	SECTION("Switch to channel number 2, TV off")
	{
		REQUIRE(!tv.IsTurnedOn());

		input << "SelectChannel 2";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(output.str() == "ERROR: Turned off TV can't switches channel\n");
	}

	SECTION("Channel number out of range. Channel > MAX_CHANNEL")
	{
		tv.TurnOn();
		REQUIRE(tv.IsTurnedOn());

		input << "SelectChannel 100";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(output.str() == "ERROR: Channel is out of range\n");
	}

	SECTION("Channel number out of range. Channel < MIN_CHANNEL")
	{
		tv.TurnOn();
		REQUIRE(tv.IsTurnedOn());

		input << "SelectChannel 0";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(output.str() == "ERROR: Channel is out of range\n");
	}

	SECTION("Invalid command")
	{
		tv.TurnOn();
		REQUIRE(tv.IsTurnedOn());

		input << "Channel";
		REQUIRE(!remoteControl.SetCommand());
	}

	SECTION("Select Previous Channel")
	{
		tv.TurnOn();
		REQUIRE(tv.IsTurnedOn());

		tv.SelectChannel(2);

		input << "PreviousChannel";
		REQUIRE(remoteControl.SetCommand());

		REQUIRE(tv.GetChannel() == 1);
		REQUIRE(output.str() == "Channel changed to 1\n");
	}
}

TEST_CASE("The ability to give a name to the channel and search for the channel by name and number")
{
	CTVSet tv;
	stringstream input, output;
	CRemoteControl remoteControl(tv, input, output);

	SECTION("Give channel 2 the name sport and find the channel by number and name")
	{
		tv.TurnOn();
		input << "SetChannelName 2 sport";

		REQUIRE(remoteControl.SetCommand());
		REQUIRE(output.str() == "Channel saved: 2 - sport\n");

		int numberChannel = tv.GetChannelByName("sport");

		REQUIRE(numberChannel == 2);

		string nameChannel = tv.GetChannelName(2);

		REQUIRE(nameChannel == "sport");
	}
}