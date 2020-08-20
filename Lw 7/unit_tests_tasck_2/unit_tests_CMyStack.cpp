#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "../tasck_2_myList/CMyStack.h"
#include <boost/test/included/unit_test.hpp>
#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(testing_class_muStask)

	struct StackOfInt
	{
		CMyStack<int> stackOfInt;
	};

	BOOST_FIXTURE_TEST_SUITE(myStack_of_integer, StackOfInt)

		BOOST_AUTO_TEST_CASE(is_empty_by_default)
		{
			BOOST_CHECK(stackOfInt.IsEmpty());
			BOOST_REQUIRE_EQUAL(stackOfInt.GetSize(), 0);
		}

		BOOST_AUTO_TEST_CASE(pushing_items_get_size)
		{
			stackOfInt.Push(1);
			stackOfInt.Push(2);

			BOOST_REQUIRE_EQUAL(stackOfInt.GetSize(), 2);
		}

		BOOST_AUTO_TEST_CASE(get_lost_item)
		{
			stackOfInt.Push(1);
			stackOfInt.Push(2);

			BOOST_REQUIRE_EQUAL(stackOfInt.GetElement(), 2);
		}

		BOOST_AUTO_TEST_CASE(delete_lost_item)
		{
			stackOfInt.Push(1);
			stackOfInt.Push(2);
			stackOfInt.Pop();

			BOOST_REQUIRE_EQUAL(stackOfInt.GetSize(), 1);
			BOOST_REQUIRE_EQUAL(stackOfInt.GetElement(), 1);
		}

		BOOST_AUTO_TEST_CASE(clear_myStack)
		{
			stackOfInt.Push(1);
			stackOfInt.Push(2);
			stackOfInt.Push(3);
			stackOfInt.Push(4);
			stackOfInt.Clear();

			BOOST_CHECK(stackOfInt.IsEmpty());
			BOOST_REQUIRE_EQUAL(stackOfInt.GetSize(), 0);
		}

		BOOST_AUTO_TEST_CASE(catch_the_exception_when_deleting_last_item)
		{
			BOOST_CHECK_THROW(stackOfInt.Pop(), logic_error);
		}

		BOOST_AUTO_TEST_CASE(catch_the_exception_when_get_item)
		{
			BOOST_CHECK_THROW(stackOfInt.GetElement(), logic_error);
		}

		BOOST_AUTO_TEST_CASE(assigning_data_from_stack1_to_stack2)
		{
			stackOfInt.Push(1);
			stackOfInt.Push(2);

			CMyStack<int> stackOfInt_2;
			stackOfInt_2 = stackOfInt;

			BOOST_REQUIRE_EQUAL(stackOfInt_2.GetSize(), stackOfInt.GetSize());
			BOOST_REQUIRE_EQUAL(stackOfInt_2.GetElement(), 2);

			stackOfInt.Clear();

			BOOST_CHECK(stackOfInt_2.GetSize() != stackOfInt.GetSize());
			BOOST_REQUIRE_EQUAL(stackOfInt_2.GetElement(), 2);
		}

		BOOST_AUTO_TEST_CASE(copy_between_nonEmpty_stack)
		{
			stackOfInt.Push(1);
			stackOfInt.Push(2);
			stackOfInt.Push(3);
			stackOfInt.Push(4);

			CMyStack<int> stackOfInt_2;
			stackOfInt_2.Push(5);

			stackOfInt = stackOfInt_2;
			BOOST_REQUIRE_EQUAL(stackOfInt.GetSize(), 1);
			BOOST_REQUIRE_EQUAL(stackOfInt.GetElement(), 5);
		}

		BOOST_AUTO_TEST_CASE(copy_empty_stack)
		{
			stackOfInt.Push(1);
			stackOfInt.Push(2);

			CMyStack<int> stackOfInt_2;
			stackOfInt = stackOfInt_2;

			BOOST_REQUIRE_EQUAL(stackOfInt_2.GetSize(), 0);
			BOOST_REQUIRE_EQUAL(stackOfInt_2.IsEmpty(), true);

			BOOST_REQUIRE_EQUAL(stackOfInt.GetSize(), 0);
			BOOST_REQUIRE_EQUAL(stackOfInt.IsEmpty(), true);
		}

		BOOST_AUTO_TEST_CASE(independent_copying)
		{
			stackOfInt.Push(1);
			stackOfInt.Push(2);
			stackOfInt.Push(3);
			stackOfInt.Push(4);

			CMyStack<int> stackOfInt_2(stackOfInt);

			BOOST_REQUIRE_EQUAL(stackOfInt.GetSize(), 4);
			BOOST_REQUIRE_EQUAL(stackOfInt_2.GetSize(), 4);

			stackOfInt.Pop();
			BOOST_TEST(stackOfInt.GetSize() < stackOfInt_2.GetSize(), "after deleting the last element in stack1, the number of elements in stack 2 will not change");

			BOOST_REQUIRE_EQUAL(stackOfInt.GetElement(), 3);
			BOOST_REQUIRE_EQUAL(stackOfInt_2.GetElement(), 4);
		}

		BOOST_AUTO_TEST_CASE(independent_copying_empty_stack)
		{
			CMyStack<int> stackOfInt_2(stackOfInt);

			BOOST_CHECK(stackOfInt.IsEmpty());
			BOOST_CHECK(stackOfInt_2.IsEmpty());

			BOOST_REQUIRE_EQUAL(stackOfInt.GetSize(), 0);
			BOOST_REQUIRE_EQUAL(stackOfInt_2.GetSize(), 0);
		}

		BOOST_AUTO_TEST_CASE(move_constructor)
		{
			stackOfInt.Push(1);
			stackOfInt.Push(2);

			CMyStack<int> stackOfInt_2 = move(stackOfInt);

			BOOST_CHECK(stackOfInt.IsEmpty());
			BOOST_REQUIRE_EQUAL(stackOfInt.GetSize(), 0);

			BOOST_REQUIRE_EQUAL(stackOfInt_2.GetSize(), 2);
			BOOST_REQUIRE_EQUAL(stackOfInt_2.GetElement(), 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct StackOfString
	{
		CMyStack<std::string> stackOfString;
	};

	BOOST_FIXTURE_TEST_SUITE(myStack_of_string, StackOfString)

		BOOST_AUTO_TEST_CASE(is_empty_by_default)
		{
			BOOST_CHECK(stackOfString.IsEmpty());
			BOOST_CHECK_EQUAL(stackOfString.GetSize(), 0);
		}

		BOOST_AUTO_TEST_CASE(get_and_delete_last_item)
		{
			stackOfString.Push("qwe");
			stackOfString.Push("asd");

			stackOfString.Pop();
			BOOST_CHECK_EQUAL(stackOfString.GetSize(), 1);
			BOOST_CHECK_EQUAL(stackOfString.GetElement(), "qwe");
		}

		BOOST_AUTO_TEST_CASE(clear_myStack)
		{
			stackOfString.Push("qwe");
			stackOfString.Push("asd");
			stackOfString.Push("zxc");

			stackOfString.Clear();

			BOOST_CHECK_EQUAL(stackOfString.GetSize(), 0);
			BOOST_CHECK(stackOfString.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(catch_the_exception_when_deleting_last_item)
		{
			BOOST_CHECK_THROW(stackOfString.Pop(), logic_error);
		}

		BOOST_AUTO_TEST_CASE(catch_the_exception_when_get_item)
		{
			BOOST_CHECK_THROW(stackOfString.GetElement(), logic_error);
		}

		BOOST_AUTO_TEST_CASE(independent_copying)
		{
			stackOfString.Push("qwe");
			stackOfString.Push("asd");

			CMyStack<std::string> stackOfString_2(stackOfString);

			BOOST_CHECK_EQUAL(stackOfString_2.GetElement(), stackOfString.GetElement());
			BOOST_REQUIRE_EQUAL(stackOfString.GetElement(), "asd");
		}

		BOOST_AUTO_TEST_CASE(assigning_data_from_stack1_to_stack2)
		{
			stackOfString.Push("qwe");
			stackOfString.Push("asd");

			CMyStack<std::string> stackOfString_2;

			BOOST_CHECK(stackOfString_2.IsEmpty());
			BOOST_CHECK_EQUAL(stackOfString_2.GetSize(), 0);

			stackOfString_2 = stackOfString;
			stackOfString.Clear();

			BOOST_CHECK_EQUAL(stackOfString_2.GetSize(), 2);
			BOOST_CHECK_EQUAL(stackOfString_2.IsEmpty(), false);
			BOOST_REQUIRE_EQUAL(stackOfString_2.GetElement(), "asd");
		}

		BOOST_AUTO_TEST_CASE(move_constructor)
		{
			stackOfString.Push("qwe");
			stackOfString.Push("asd");

			CMyStack<std::string> stackOfString_2 = move(stackOfString);

			BOOST_CHECK_EQUAL(stackOfString.GetSize(), 0);
			BOOST_CHECK(stackOfString.IsEmpty());

			BOOST_CHECK_EQUAL(stackOfString_2.GetSize(), 2);
			BOOST_CHECK_EQUAL(stackOfString_2.IsEmpty(), false);
			BOOST_CHECK_EQUAL(stackOfString_2.GetElement(), "asd");
		}

		BOOST_AUTO_TEST_CASE(independent_copying_empty_stack)
		{
			stackOfString.Push("qwe");
			stackOfString.Push("asd");

			CMyStack<std::string> stackOfString_2;
			stackOfString_2 = move(stackOfString);

			BOOST_CHECK_EQUAL(stackOfString_2.GetSize(), 2);
			BOOST_CHECK_EQUAL(stackOfString_2.IsEmpty(), false);
			BOOST_CHECK_EQUAL(stackOfString_2.GetElement(), "asd");

			BOOST_CHECK_EQUAL(stackOfString.GetSize(), 0);
			BOOST_CHECK(stackOfString.IsEmpty());
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()