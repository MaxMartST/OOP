#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "../task_1_http_url/CCommandHandler.h"
#include "../task_1_http_url/CHttpUrl.h"
#include "../task_1_http_url/CUrlParsingError.h"
#include "../task_1_http_url/pch.h"
#include <boost/test/included/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(test_validity_of_url_requests)

	BOOST_AUTO_TEST_CASE(valid_url_entered)
	{
		stringstream input, output;
		CCommandHandler ch(input, output);

		input << "http://www.example.com:80/path/to/myfile.html";
		BOOST_CHECK_EQUAL(ch.HandleCommand(), true);
	}

	BOOST_AUTO_TEST_CASE(catch_the_exception_empty_string)
	{
		stringstream input, output;
		CCommandHandler ch(input, output);

		input << "";
		BOOST_CHECK_EQUAL(ch.HandleCommand(), false);
		BOOST_CHECK_EQUAL("ERROR: Empty input!\n", output.str());
	}

	BOOST_AUTO_TEST_CASE(catch_the_exception_only_one_space)
	{
		stringstream input, output;
		CCommandHandler ch(input, output);

		input << " ";
		BOOST_CHECK_EQUAL(ch.HandleCommand(), false);
		BOOST_CHECK_EQUAL("ERROR: Empty input!\n", output.str());
	}

	BOOST_AUTO_TEST_CASE(parsing_correct_url)
	{
		CHttpUrl url("http://www.example.com:80/path/to/myfile.html");
		string protocol = (ConvertProtocolToString(url.GetProtocol()));
		unsigned short port = 80;

		BOOST_CHECK_EQUAL(protocol, "http");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.example.com");
		BOOST_CHECK_EQUAL(url.GetPort(), port);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/path/to/myfile.html");
	}

	BOOST_AUTO_TEST_CASE(catch_exceptions_with_incorrect_parsing_url)
	{
		BOOST_CHECK_THROW(CHttpUrl url("htTtp://www.example.com:80/path/to/myfile.html"), invalid_argument);
		BOOST_CHECK_THROW(CHttpUrl url("http://:80/path/to/myfile.html"), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl url("http:///path/to/myfile.html"), CUrlParsingError);
	}

BOOST_AUTO_TEST_SUITE_END()