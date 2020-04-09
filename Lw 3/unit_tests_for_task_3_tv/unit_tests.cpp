#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include "../../catch2/catch.hpp"
#include "../task_3_tv/CErrorMessage.h"
#include "../task_3_tv/CCommandTerminal.h"
#include "../task_3_tv/CTVSet.h"
#include "../task_3_tv/edit_channel_name.h"
#include "../task_3_tv/pch.h"

using namespace std;
using namespace std::placeholders;

TEST_CASE("Check the TV interface when the state is on and off")
{
	CTVSet tv;
	stringstream input, output;
	CCommandTerminal commandTerminal(tv, input, output);

	SECTION("Channel number on first start is 1")
	{
		REQUIRE(!tv.IsTurnedOn());

		input << "TurnOn";
		REQUIRE(commandTerminal.SetCommand());
		REQUIRE(tv.IsTurnedOn());
		REQUIRE(tv.GetChannel() == 1);

		REQUIRE(output.str() == "TV is turned on\n");
	}

	SECTION("TV status is changing, turned off")
	{
		input << "TurnOff";
		commandTerminal.SetCommand();

		REQUIRE(!tv.IsTurnedOn());
		REQUIRE(output.str() == "TV is turned off\n");
	}

	SECTION("Display the channel number after the first start of the TV. Channel number is 1")
	{
		tv.TurnOn();

		input << "Info";
		commandTerminal.SetCommand();
		REQUIRE(output.str() == "TV is turned on\nChannel is: 1\n");
	}
}