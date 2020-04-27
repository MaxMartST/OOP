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
				//for (auto& command : validCommandNames)
				//{
				//	input << command;
				//	controlÑalculator.SetCommand();

				//	REQUIRE(output.str() != "Unknown command!\n");
				//	input.clear();
				//}
			}

			AND_WHEN("Invalid command name is used")
			{
				THEN("Error message is displayed")
				{
					input.clear();
					input << "begin";
					controlÑalculator.SetCommand();

					REQUIRE(output.str() == "Unknown command!\n");
				}
			}
		}
	}
}

TEST_CASE("Declaring Variables and Displaying")
{
	GIVEN("Class calculator and menu announced")
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
				controlÑalculator.SetCommand();

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
					controlÑalculator.SetCommand();
					REQUIRE(output.str() == "ERROR: Invalid name of varible!\n");
				}
			}

			AND_WHEN("Invalid variable name: forbidden character")
			{
				THEN("Error is displayed: invalid name")
				{
					input.clear();
					input << "var a$c";
					controlÑalculator.SetCommand();
					REQUIRE(output.str() == "ERROR: Invalid name of varible!\n");
				}
			}
		}
	}
}

TEST_CASE("Assignment to a variable")
{
	GIVEN("Class calculator, menu and initialize a new variable")
	{
		CCalculator calculator;
		stringstream input, output;
		CCalculatorMenu controlÑalculator(calculator, input, output);
		input << "var x";
		controlÑalculator.SetCommand();

		WHEN("Assign a numerical value to the variable")
		{
			THEN("The value of this given variable changes")
			{
				input.clear();
				input << "let x=3.14";
				controlÑalculator.SetCommand();

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
					controlÑalculator.SetCommand();

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
					controlÑalculator.SetCommand();

					input.clear();
					input << "let y=x";
					controlÑalculator.SetCommand();

					auto mapVar = calculator.GetVars();
					map<string, double>::iterator it;

					it = mapVar.find("y");

					REQUIRE(it != mapVar.end());
					REQUIRE(!isnan(mapVar["y"]));
					REQUIRE(mapVar["y"] == 3.14);
				}
			}

			AND_WHEN("Attempt to assign a value to an undeclared variable")
			{
				THEN("Error is displayed: Unrecognized variable")
				{
					input.clear();
					input << "let x=z";
					controlÑalculator.SetCommand();

					REQUIRE(output.str() == "ERROR: Unrecognized variable: z\n");
				}
			}

			AND_WHEN("Invalid expression assignment")
			{
				THEN("Error is displayed: Invalid name of varible")
				{
					input.clear();
					input << "let x= ";
					controlÑalculator.SetCommand();

					REQUIRE(output.str() == "ERROR: Invalid name of varible!\n");
				}
			}
		}
	}
}

TEST_CASE("Display of variables and their values")
{
	GIVEN("Calculator class, menu and variable initialization with value")
	{
		CCalculator calculator;
		stringstream input, output;
		CCalculatorMenu controlÑalculator(calculator, input, output);

		input << "var x";
		controlÑalculator.SetCommand();
		input.clear();

		input << "let y=2.2333";
		controlÑalculator.SetCommand();
		input.clear();

		WHEN("The printvars command will display all declared variables and their values")
		{
			THEN("Output of variables and their values")
			{
				input << "printvars";
				controlÑalculator.SetCommand();

				REQUIRE(output.str() == "x:nan\ny:2.23\n");
			}
		}

		AND_WHEN("enter the print <iterator> command")
		{
			THEN("The value of the variable or function specified by the print command is displayed")
			{
				input << "print y";
				controlÑalculator.SetCommand();

				REQUIRE(output.str() == "y:2.23\n");
				input.clear();
			}

			AND_THEN("The value of the variable or function specified by the print command is displayed")
			{
				input << "print x";
				controlÑalculator.SetCommand();

				REQUIRE(output.str() == "x:nan\n");
				input.clear();
			}
		}
	}
}
