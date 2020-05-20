#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include "../task_1_http_url/CCommandHandler.h"
#include "../task_1_http_url/CHttpUrl.h"
#include "../task_1_http_url/CUrlParsingError.h"
#include "../task_1_http_url/pch.h"
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestFuzzyCompare)

	BOOST_AUTO_TEST_CASE(Equal)
	{
		stringstream input, output;
		CCommandHandler ch(input, output);

		input << "http://www.example.com:80/path/to/myfile.html";

		BOOST_CHECK_NO_THROW(ch.HandleCommand());
	}

BOOST_AUTO_TEST_SUITE_END()