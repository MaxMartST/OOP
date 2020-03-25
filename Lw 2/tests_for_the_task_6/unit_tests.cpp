#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../vector_task_6/FunctionsOfVector.h"
#include "../vector_task_6/RecordAndPrintVector.h"

TEST_CASE("Unit tests: vector transformation")
{
	std::vector<double> numbersVector{ 4, 4.4, 8, 10, -2 };
	std::stringstream buffer;

	SECTION("We read data from the stream and write to the vector")
	{
		std::istringstream str(" 4 4.4 8 10 -2 ");
		REQUIRE(*(GetVectorFromStream(str)) == numbersVector);
	}

	SECTION("We read invalid data from the stream and cause an error")
	{
		std::istringstream str("0 12 -97 F 7.5");
		REQUIRE(GetVectorFromStream(str) == std::nullopt);
	}

	SECTION("An empty string will return an empty vector")
	{
		std::istringstream str(" ");
		numbersVector.clear();
		REQUIRE(*(GetVectorFromStream(str)) == numbersVector);
	}

	SECTION("An empty vector will return an empty vector")
	{
		numbersVector.clear();
		REQUIRE(*(ChangeVector(numbersVector)) == numbersVector);
	}

	SECTION("Invalid vector with a minimum element equal to zero")
	{
		std::vector<double> invalVector{ 4, 4.4, 8, 10, 0 };
		REQUIRE(ChangeVector(invalVector) == std::nullopt);
	}

	SECTION("Get modified vector")
	{
		std::vector<double> resultVector{ -20, -22, -40, -50, 10 };
		REQUIRE(*(ChangeVector(numbersVector)) == resultVector);
	}

	SECTION("Output modified vector")
	{
		std::vector<double> numbers = { 2.5, 3.14, 7, 8, -19, 15 };
		std::string outStr;
		PrintSortVector(buffer, numbers);
		std::getline(buffer, outStr);
		REQUIRE(outStr == "-19.000 2.500 3.140 7.000 8.000 15.000 ");
	}
	SECTION("Output empty vector")
	{
		numbersVector.clear();
		std::string outStr;
		PrintSortVector(buffer, numbersVector);
		std::getline(buffer, outStr);
		REQUIRE(outStr == "");
	}
}