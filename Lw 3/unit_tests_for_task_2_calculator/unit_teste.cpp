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

			WHEN("Invalid command name is used")
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

					REQUIRE(output.str() == "ERROR: Unrecognized variable [z]\n");
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
		vector<string> startingCommand{ "var x", "let y=2.2333" };

		for (auto& command : startingCommand)
		{
			input << command;
			controlÑalculator.SetCommand();
			input.clear();
		}

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

				REQUIRE(output.str() == "2.23\n");
				input.clear();
			}

			AND_THEN("The value of the variable or function specified by the print command is displayed")
			{
				input << "print x";
				controlÑalculator.SetCommand();

				REQUIRE(output.str() == "nan\n");
				input.clear();
			}
		}
	}
}

TEST_CASE("Function declaration")
{
	GIVEN("Calculator class, menu and variables")
	{
		CCalculator calculator;
		stringstream input, output;
		CCalculatorMenu controlÑalculator(calculator, input, output);
		vector<string> startingCommand{ "var x", "var y" };

		for (auto& command : startingCommand)
		{
			input << command;
			controlÑalculator.SetCommand();
			input.clear();
		}

		WHEN("Declare a function and assign it the result of applying one of the following binary operations")
		{
			THEN("The value of the function will be nan")
			{
				input << "fn XplusY=x+y";
				controlÑalculator.SetCommand();
				input.clear();

				REQUIRE(isnan(calculator.GetValue("XplusY")));

				input << "print XplusY";
				controlÑalculator.SetCommand();

				REQUIRE(output.str() == "nan\n");
			}

			AND_WHEN("Variables are initialized")
			{
				vector<string> commandLine{ "let x=3", "let y=4", "fn XplusY=x+y", "print XplusY" };

				THEN("In the function, the result of applying binary operations is written.")
				{
					for (auto& command : commandLine)
					{
						input << command;
						controlÑalculator.SetCommand();
						input.clear();
					}

					REQUIRE(!isnan(calculator.GetValue("XplusY")));
					REQUIRE(output.str() == "7.00\n");
				}
			}

			AND_WHEN("Assign a value to a function")
			{
				vector<string> commandLine{ "let x=3.1415", "fn funX=x", "print funX" };

				THEN("The value of the function is equal to the value of the variable")
				{
					for (auto& command : commandLine)
					{
						input << command;
						controlÑalculator.SetCommand();
						input.clear();
					}

					REQUIRE(output.str() == "3.14\n");
					REQUIRE(calculator.GetValue("funX") == calculator.GetValue("x"));
				}
			}

			AND_WHEN("Variable was not declared")
			{
				THEN("Error message is displayed")
				{
					input << "fn XplusY=x+Z";
					controlÑalculator.SetCommand();
					input.clear();

					REQUIRE(isnan(calculator.GetValue("XplusY")));
					REQUIRE(output.str() == "ERROR: Identifier [Z] has not been advertised\n");
				}
			}

			AND_WHEN("Function name is a variable")
			{
				THEN("Error message is displayed")
				{
					input << "fn x=y";
					controlÑalculator.SetCommand();
					input.clear();

					REQUIRE(output.str() == "ERROR: An identifier named [x] already exists\n");
				}
			}

			AND_WHEN("Invalid character encountered in assignment iterator")
			{
				THEN("Error message is displayed")
				{
					input << "fn XplusY=x%y";
					controlÑalculator.SetCommand();
					input.clear();

					REQUIRE(output.str() == "ERROR: Identifier [x%y] has not been advertised\n");
				}
			}
		}
	}
}

TEST_CASE("Circle area calculation")
{
	GIVEN("Calculator class, menu, and list of commands")
	{
		CCalculator calculator;
		stringstream input, output;
		CCalculatorMenu controlÑalculator(calculator, input, output);
		vector<string> commandLine{ "var radius",
			"let pi=3.14159265",
			"fn radiusSquared=radius*radius",
			"fn circleArea=pi*radiusSquared",
			"let radius=10",
			"let circle10Area=circleArea",
			"let radius=20",
			"let circle20Area=circleArea" };

		WHEN("Stepwise calculation of the area of a circle")
		{
			for (size_t i = 0; i < commandLine.size(); ++i)
			{
				input << commandLine[i];
				controlÑalculator.SetCommand();
				input.clear();
			}

			THEN("The following statements will be true")
			{
				REQUIRE(calculator.GetValue("pi") == 3.14159265);
				REQUIRE(calculator.GetValue("radius") == 20);
				REQUIRE(calculator.GetValue("radiusSquared") == 400);
				REQUIRE(calculator.GetValue("circleArea") == 1256.63706);
				REQUIRE(calculator.GetValue("circle10Area") == 314.159265);
				REQUIRE(calculator.GetValue("circle20Area") == calculator.GetValue("circleArea"));
			}

			AND_THEN("Print all functions")
			{
				input << "printfns";
				controlÑalculator.SetCommand();
				input.clear();

				REQUIRE(output.str() == "circleArea:1256.64\nradiusSquared:400.00\n");
			}
			
			AND_THEN("Print all variables")
			{
				input << "printvars";
				controlÑalculator.SetCommand();
				input.clear();

				REQUIRE(output.str() == "circle10Area:314.16\ncircle20Area:1256.64\npi:3.14\nradius:20.00\n");
			}
		}
	}
}