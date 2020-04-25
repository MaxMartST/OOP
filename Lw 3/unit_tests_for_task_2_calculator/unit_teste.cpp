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
		vector<string> validCommandNames{ "var", "lat", "printvars", "fn", "print", "printfns" };

		WHEN("Calculator and menu classes created")
		{
			CCalculator calculator;
			CCalculatorMenu control—alculator(calculator, cin, cout);
			stringstream input, output;

			THEN("The list of valid commands is initialized")
			{
				for (auto& command : validCommandNames)
				{
					input << command;
					REQUIRE(!control—alculator.SetCommand());
					input.clear();
				}
			}
		}
	}
}