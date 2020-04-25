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
			CCalculatorMenu controlÑalculator(calculator, input, output);

			THEN("The list of valid commands is initialized")
			{
				for (auto& command : validCommandNames)
				{
					input << command;
					controlÑalculator.SetCommand();
					REQUIRE(output.str() != "Unknown command!\n");
					input.clear();
				}
			}

			AND_WHEN("Invalid command name is used")
			{
				THEN("Error message is displayed")
				{
					input << "begin";
					controlÑalculator.SetCommand();
					REQUIRE(output.str() == "Unknown command!\n");
					input.clear();
				}
			}
		}
	}
}

TEST_CASE("Declaring Variables and Displaying")
{
	GIVEN("class calculator and menu announced")
	{
		CCalculator calculator;
		stringstream input, output;
		CCalculatorMenu controlÑalculator(calculator, input, output);

		WHEN("When we initialize a new variable with the correct name")
		{
			THEN("Added variable with initial nan value")
			{
				input << "var x";
				controlÑalculator.SetCommand();
				auto it = calculator.GetVars();

				REQUIRE(it["x"] != numeric_limits<double>::quiet_NaN());
			}

			AND_WHEN("")
			{
				input << "var x";
				controlÑalculator.SetCommand();
				auto it = calculator.GetVars();
				map<string, double>::iterator it_2;

				it_2 = it.find("x");
				REQUIRE(it_2 != it.end());
			}
		}
	}
}