#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../../catch2/catch.hpp"
#include "../vector_task_6/RecordAndPrintVector.h"

TEST_CASE()
{
	REQUIRE(Add(3, 4) == 7);
}