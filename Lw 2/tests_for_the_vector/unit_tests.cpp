#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../vector_task_6/FunctionsOfVector.h"
#include "../vector_task_6/RecordAndPrintVector.h"

TEST_CASE("Vector conversion check")
{
	std::vector<double> numbersVector{ 4, 4.4, 8, 10, -2 };

	SECTION("Function does not change empty vector")
	{
		numbersVector.clear();
		ChangeVector(numbersVector);
		REQUIRE(numbersVector.empty());
	}

	SECTION("Multiplies each element of non empty vector by maximum element and divides by minimum element")
	{
		std::vector<double> resultVector{ -20, -22, -40, -50, 10 };
		ChangeVector(numbersVector);
		REQUIRE(numbersVector == resultVector);
	}

	SECTION("Multiplies each element of non empty vector by maxiumum element if minimum is zero")
	{
		std::vector<double> minZeroVector{ 4, 4.4, 8, 10, 0 };
		std::vector<double> resultVector{ 40, 44, 80, 100, 0 };
		ChangeVector(minZeroVector);
		REQUIRE(minZeroVector == resultVector);
	}
}