#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../vector_task_6/FunctionsOfVector.h"
#include "../vector_task_6/RecordAndPrintVector.h"

TEST_CASE("Unit tests: vector transformation")
{
	std::string str = "0 12 -97 7.5";
	std::string invalidStr = "0 12 -97 F 7.5";
	std::vector<double> numbers;
	std::vector<double> invalidVector = { 0, 12, 97, 7.5 };
	std::vector<double> numbersVector = { 0, 12, -97, 7.5 };
	std::vector<double> modifiedVector = { -0.000, -1.4845360825, 12.000, -0.9278350515 };

	SECTION("We read data from the stream and write to the vector")
	{
		std::istringstream receivedStream(str);
		numbers.clear();
		REQUIRE(ReadingDataFromStreamInVector(receivedStream, numbers));
	}

	SECTION("We read invalid data from the stream and cause an error")
	{
		std::istringstream receivedStream(invalidStr);
		numbers.clear();
		REQUIRE(!ReadingDataFromStreamInVector(receivedStream, numbers));
	}

	SECTION("Correctly written vector from the stream")
	{
		std::istringstream receivedStream(str);
		numbers.clear();
		ReadingDataFromStreamInVector(receivedStream, numbers);
		REQUIRE(numbers == numbersVector);
	}
	SECTION("An empty string will return an empty vector")
	{
		std::istringstream receivedStream("");
		numbers.clear();
		ReadingDataFromStreamInVector(receivedStream, numbers);
		REQUIRE(numbers.empty());
	}
	SECTION("The function MyltiByMaxDivMinAllElemVector will return a correctly processed vector")
	{
		numbers.clear();
		MyltiByMaxDivMinAllElemVector(numbers);
		REQUIRE(numbers.empty());
	}
	SECTION("A valid vector will return a correctly processed vector")
	{
		MyltiByMaxDivMinAllElemVector(numbersVector);
		CHECK(numbersVector == modifiedVector);
	}
}