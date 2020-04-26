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
			CCalculatorMenu control�alculator(calculator, input, output);

			THEN("The list of valid commands is initialized")
			{
				for (auto& command : validCommandNames)
				{
					input << command;
					control�alculator.SetCommand();
					REQUIRE(output.str() != "Unknown command!\n");
					input.clear();
				}
			}

			AND_WHEN("Invalid command name is used")
			{
				THEN("Error message is displayed")
				{
					input << "begin";
					control�alculator.SetCommand();
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
		CCalculatorMenu control�alculator(calculator, input, output);

		WHEN("When we initialize a new variable with the correct name")
		{
			THEN("Added variable with initial nan value")
			{
				input << "var x";
				control�alculator.SetCommand();

				auto mapVar = calculator.GetVars();
				map<string, double>::iterator it;

				it = mapVar.find("x");
				REQUIRE(it != mapVar.end());
				REQUIRE(isnan(mapVar["x"]));
			}

			AND_THEN("Underscore in variable name")
			{
				input.clear();
				input << "var x_abs";
				control�alculator.SetCommand();

				auto mapVar = calculator.GetVars();
				map<string, double>::iterator it;

				it = mapVar.find("x_abs");
				REQUIRE(it != mapVar.end());
				REQUIRE(isnan(mapVar["x_abs"]));
			}

			AND_WHEN("Invalid variable name: first character is a digit")
			{
				THEN("Error is displayed: invalid name")
				{
					input.clear();
					input << "var 7abc";
					control�alculator.SetCommand();
					REQUIRE(output.str() == "ERROR: Invalid name of varible!\n");
				}
			}

			AND_WHEN("Invalid variable name: forbidden character")
			{
				THEN("Error is displayed: invalid name")
				{
					input.clear();
					input << "var a$c";
					control�alculator.SetCommand();
					REQUIRE(output.str() == "ERROR: Invalid name of varible!\n");
				}
			}
		}
	}
}

TEST_CASE("Assignment to a variable")
{
	GIVEN("class calculator, menu announced and initialize a new variable")
	{
		CCalculator calculator;
		stringstream input, output;
		CCalculatorMenu control�alculator(calculator, input, output);
		input << "var x";
		control�alculator.SetCommand();

		WHEN("Assign a numerical value to the variable")
		{
			THEN("The value of this given variable changes")
			{
				input.clear();
				input << "let x=3.14";
				control�alculator.SetCommand();

				auto mapVar = calculator.GetVars();
				map<string, double>::iterator it;

				it = mapVar.find("x");

				REQUIRE(it != mapVar.end());
				REQUIRE(!isnan(mapVar["x"]));
				REQUIRE(mapVar["x"] == 3.14);
			}

			AND_WHEN("Assign a numeric value to an undeclared variable")
			{
				THEN("The value of this given variable changes")
				{
					input.clear();
					input << "let y=2.277";
					control�alculator.SetCommand();

					auto mapVar = calculator.GetVars();
					map<string, double>::iterator it;

					it = mapVar.find("y");

					REQUIRE(it != mapVar.end());
					REQUIRE(!isnan(mapVar["y"]));
					REQUIRE(mapVar["y"] == 2.277);
				}
			}

			AND_WHEN("Reassigning a variable to another variable")
			{
				THEN("The value of this given variable changes")
				{
					input.clear();
					input << "let x=3.14";
					control�alculator.SetCommand();

					input.clear();
					input << "let y=x";
					control�alculator.SetCommand();

					auto mapVar = calculator.GetVars();
					map<string, double>::iterator it;

					it = mapVar.find("y");

					REQUIRE(it != mapVar.end());
					REQUIRE(!isnan(mapVar["y"]));
					REQUIRE(mapVar["y"] == 3.14);
				}
			}
		}
	}
}