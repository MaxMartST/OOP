#include <iostream>
#include <sstream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../string_remove_extra_spaces/RemoveExtraSpaces.h"

TEST_CASE("Unit tests: string transformation")
{
	SECTION("Empty string")
	{
		std::string str = "";
		REQUIRE(RemoveExtraSpaces("") == str);
	}

	SECTION("Get modifited string")
	{
		std::string str = "Hello 3 world!3 5";
		REQUIRE(RemoveExtraSpaces("  Hello   3   world!3   5     ") == str);
	}

	SECTION("Get multiple rows")
	{
		std::istringstream input("  2Hello   3   world!   3   \n   2 line");
		std::stringstream output;
		RemoveExtraSpacesFromStream(input, output);
		REQUIRE(output.str() == "2Hello 3 world! 3\n2 line");
		REQUIRE(input.eof());
	}

	
	SECTION("Get multiple rows")
	{
		std::istringstream input("  2Hello   3   world!   3   \n   2 line \n");
		std::stringstream output;
		RemoveExtraSpacesFromStream(input, output);
		REQUIRE(output.str() == "2Hello 3 world! 3\n2 line");
		REQUIRE(input.eof());
	}
}