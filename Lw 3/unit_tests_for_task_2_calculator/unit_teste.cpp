#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../task_2_calculator/CCalculator.h"
#include "../task_2_calculator/CCalculatorMenu.h"
#include "../task_2_calculator/CErrorMessage.h"
#include "../task_2_calculator/pch.h"

using namespace std;

TEST_CASE("Initialization of a list of valid commands in the CCalculatorMenu class")
{
	GIVEN("Correct command names given")
	{
		vector<string> validCommandNames{ "var", "let", "printvars", "fn", "print", "printfns" };

		WHEN("Calculator and menu classes created")
		{
			CCalculator calculator;
			stringstream input, output;
			CCalculatorMenu control—alculator(calculator, input, output);

			THEN("The list of valid commands is initialized")
			{
				for (auto& command : validCommandNames)
				{
					input << command;
					control—alculator.SetCommand();
					REQUIRE(output.str() != "Unknown command!\n");
					input.clear();
				}
			}

			AND_WHEN("Invalid command name is used")
			{
				THEN("Error message is displayed")
				{
					input << "begin";
					control—alculator.SetCommand();
					REQUIRE(output.str() == "Unknown command!\n");
					input.clear();
				}
			}
		}
	}
}