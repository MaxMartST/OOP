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

	BOOST_AUTO_TEST_CASE(parsing_correct_url_with_a_min_range_1)
	{
		CHttpUrl url("http://www.example.com:1/path/to/myfile.html");
		string protocol = (ConvertProtocolToString(url.GetProtocol()));
		unsigned short port = 1;

		BOOST_CHECK_EQUAL(protocol, "http");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.example.com");
		BOOST_CHECK_EQUAL(url.GetPort(), port);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/path/to/myfile.html");
	}

	BOOST_AUTO_TEST_CASE(parsing_correct_url_with_a_max_range_65535)
	{
		CHttpUrl url("http://www.example.com:65535/path/to/myfile.html");
		string protocol = (ConvertProtocolToString(url.GetProtocol()));
		unsigned short port = 65535;

		BOOST_CHECK_EQUAL(protocol, "http");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.example.com");
		BOOST_CHECK_EQUAL(url.GetPort(), port);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/path/to/myfile.html");
	}

	BOOST_AUTO_TEST_CASE(catch_exceptions_with_incorrect_parsing_url)
	{
		BOOST_CHECK_THROW(CHttpUrl url("htTtp://www.example.com:80/path/to/myfile.html"), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl url("http://:80/path/to/myfile.html"), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl url("http:///path/to/myfile.html"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(correct_url_initialization_three_arguments)
	{
		string inputUrl = RemoveExtraSpacesInLine("   www.example.com   path/to/myfile.html    http");
		BOOST_CHECK_EQUAL(inputUrl, "www.example.com path/to/myfile.html http");

		vector<string> argsUrl = ConvertStringToVector(inputUrl);
		BOOST_CHECK(argsUrl.size() == 3);
		BOOST_CHECK_EQUAL(argsUrl[0], "www.example.com");
		BOOST_CHECK_EQUAL(argsUrl[1], "path/to/myfile.html");
		BOOST_CHECK_EQUAL(argsUrl[2], "http");

		Protocol protocol = ConvertStringToProtocol(argsUrl[2]);
		BOOST_CHECK(protocol == Protocol::HTTP);

		CHttpUrl url(argsUrl[0], argsUrl[1], protocol);
		string protStr = (ConvertProtocolToString(url.GetProtocol()));
		unsigned short port = 80;

		BOOST_CHECK_EQUAL(protStr, "http");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.example.com");
		BOOST_CHECK_EQUAL(url.GetPort(), port);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/path/to/myfile.html");
	}

	BOOST_AUTO_TEST_CASE(correct_url_initialization_four_arguments)
	{
		string inputUrl = RemoveExtraSpacesInLine("   www.example.com   path/to/myfile.html    https   443");
		BOOST_CHECK_EQUAL(inputUrl, "www.example.com path/to/myfile.html https 443");

		vector<string> argsUrl = ConvertStringToVector(inputUrl);
		BOOST_CHECK(argsUrl.size() == 4);
		BOOST_CHECK_EQUAL(argsUrl[0], "www.example.com");
		BOOST_CHECK_EQUAL(argsUrl[1], "path/to/myfile.html");
		BOOST_CHECK_EQUAL(argsUrl[2], "https");
		BOOST_CHECK_EQUAL(argsUrl[3], "443");

		Protocol protocol = ConvertStringToProtocol(argsUrl[2]);
		BOOST_CHECK(protocol == Protocol::HTTPS);

		CHttpUrl url(argsUrl[0], argsUrl[1], protocol);
		string protStr = (ConvertProtocolToString(url.GetProtocol()));
		unsigned short port = 443;

		BOOST_CHECK_EQUAL(protStr, "https");
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.example.com");
		BOOST_CHECK_EQUAL(url.GetPort(), port);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/path/to/myfile.html");
	}

	BOOST_AUTO_TEST_CASE(catch_exceptions_url_initialization)
	{
		Protocol protocol = Protocol::HTTP;
		BOOST_CHECK_THROW(CHttpUrl url("", "", protocol), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl url("www.example.com", "path/to/myfile.html", protocol, 65536), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl url("www.example.com", "path/to/myfile.html", protocol, 0), CUrlParsingError);
	}

BOOST_AUTO_TEST_SUITE_END()