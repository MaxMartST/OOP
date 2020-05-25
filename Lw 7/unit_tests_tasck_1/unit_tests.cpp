#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "../tasck_1_findMax/find_max.h"
#include <boost/test/included/unit_test.hpp>
#include <vector>

using namespace std;

BOOST_AUTO_TEST_SUITE(tests_for_finding_the_maximum_element_in_an_array)
	BOOST_AUTO_TEST_CASE(empty_array)
	{
		vector<int> arr;
		int maxElem = 0;

		BOOST_CHECK_EQUAL(FindMax(arr, maxElem), false);
		BOOST_CHECK(maxElem == 0);
	}

	BOOST_AUTO_TEST_CASE(find_the_maximum_integer)
	{
		vector<int> arr{ 0, 3, 4, -6, -2, 1, 7, 9, 8 };
		int maxElem = 0;

		BOOST_CHECK_EQUAL(FindMax(arr, maxElem), true);
		BOOST_CHECK(maxElem == 9);
	}

	BOOST_AUTO_TEST_CASE(find_the_maximum_double)
	{
		vector<double> arr{ 0.6, 3.14, 4.4, -6.2, -2.27, 1.9, 7.7, 9.99, 8.01 };
		double maxElem = 0;

		BOOST_CHECK_EQUAL(FindMax(arr, maxElem), true);
		BOOST_CHECK(maxElem == 9.99);
	}

	BOOST_AUTO_TEST_CASE(find_earlier_word)
	{
		vector<string> arr{"orange", "apple", "banana", "orangeEEE"};
		string maxValue;

		BOOST_CHECK_EQUAL(FindMax(arr, maxValue), true);
		BOOST_CHECK_EQUAL(maxValue, "orangeEEE");
	}

	BOOST_AUTO_TEST_CASE(find_earlier_character_strings)
	{
		vector<const char*> arr{ "orange", "apple", "banana" };
		const char* maxValue;

		BOOST_CHECK_EQUAL(FindMax(arr, maxValue), true);
		BOOST_CHECK_EQUAL(maxValue, "orange");
	}
BOOST_AUTO_TEST_SUITE_END()