#include <iostream>
#include <sstream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../string_remove_extra_spaces/RemoveExtraSpaces.h"

TEST_CASE("Removing extra spaces from lines")
{
	SECTION("Does not change the empty string")
	{
		std::string str;
		REQUIRE(RemoveExtraSpaces("") == str);
	}

	SECTION("Removes extra spaces in one line")
	{
		std::string resultString = "Hello 3 world!3 5";
		REQUIRE(RemoveExtraSpaces("  Hello   3   world!3   5     ") == resultString);
	}
}

TEST_CASE("Removing extra spaces from the input stream")
{
	SECTION("Remove extra spaces without going to the next line")
	{
		std::istringstream input("  2Hello   3   world!   3   \n   2 line");
		std::stringstream output;
		RemoveExtraSpacesFromStream(input, output);
		REQUIRE(output.str() == "2Hello 3 world! 3\n2 line");
		REQUIRE(input.eof());
	}

	SECTION("Remove extra spaces when switching to the next line")
	{
		std::istringstream input("  2Hello   3   world!   3   \n   2 line \n");
		std::stringstream output;
		RemoveExtraSpacesFromStream(input, output);
		REQUIRE(output.str() == "2Hello 3 world! 3\n2 line\n");
		REQUIRE(input.eof());
	}
}