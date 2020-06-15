#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../task_1_figures/CCommandHandler.h"
#include "CMockedCanvas.h"
#include <boost/noncopyable.hpp>

struct CommandHandler_
{
	std::stringstream input, output;
	CCommandHandler ch;

	CommandHandler_()
		: ch(input, output)
	{
	}
};

BOOST_AUTO_TEST_SUITE(checking_the_operation_of_the_CommandHandler)
	BOOST_FIXTURE_TEST_SUITE(CommandHandler, CommandHandler_)

		BOOST_AUTO_TEST_CASE(correctly_add_a_figure)
		{
			BOOST_REQUIRE_EQUAL(ch.GetNumberShapesOfList(), 0);

			input << "rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00";
			BOOST_CHECK(ch.HandleCommand());
			BOOST_REQUIRE_EQUAL(ch.GetNumberShapesOfList(), 1);
		}

		BOOST_AUTO_TEST_CASE(invalid_add_a_figure)
		{
			input << "rectangle 20.15 30.7 40.4 ff0000 00ff00";

			BOOST_CHECK(!ch.HandleCommand());
			BOOST_REQUIRE_EQUAL(ch.GetNumberShapesOfList(), 0);
			BOOST_REQUIRE_EQUAL(output.str(), "ERROR: Not all arguments of the [rectangle] are indicated!\n");
		}

		BOOST_AUTO_TEST_CASE(invalid_coordinate_argument)
		{
			input << "rectangle 10#3 20.15 30.7 40.4 ff0000 00ff00";

			BOOST_CHECK(!ch.HandleCommand());
			BOOST_REQUIRE_EQUAL(ch.GetNumberShapesOfList(), 0);
			BOOST_REQUIRE_EQUAL(output.str(), "ERROR: Invalid coordinate argument encountered in [rectangle] command!\n");
		}

		BOOST_AUTO_TEST_CASE(invalid_color_argument)
		{
			input << "rectangle 10.3 20.15 30.7 40.4 f#0000 00ff00";

			BOOST_CHECK(!ch.HandleCommand());
			BOOST_REQUIRE_EQUAL(ch.GetNumberShapesOfList(), 0);
			BOOST_REQUIRE_EQUAL(output.str(), "ERROR: Invalid color argument detected in [rectangle] command!\n");
		}

		BOOST_AUTO_TEST_CASE(invalid_color_argument_out_of_range)
		{
			input << "rectangle 10.3 20.15 30.7 40.4 ff0000000000000 00ff00";

			BOOST_CHECK(!ch.HandleCommand());
			BOOST_REQUIRE_EQUAL(ch.GetNumberShapesOfList(), 0);
			BOOST_REQUIRE_EQUAL(output.str(), "ERROR: Invalid color argument detected in [rectangle] command!\n");
		}

		BOOST_AUTO_TEST_CASE(invalid_triangle_height_or_width_below_zero)
		{
			input << "rectangle 10.3 20.15 -30.7 40.4 ff0000 00ff00";

			BOOST_CHECK(!ch.HandleCommand());
			BOOST_REQUIRE_EQUAL(ch.GetNumberShapesOfList(), 0);
			BOOST_REQUIRE_EQUAL(output.str(), "ERROR: The height and width of the [rectangle] cannot be less than zero!\n");
		}

		BOOST_AUTO_TEST_CASE(unknown_command)
		{
			input << "cylinder 10.3 20.15 30 80 ff0000 00ff00";

			BOOST_CHECK(ch.HandleCommand());
			BOOST_REQUIRE_EQUAL(ch.GetNumberShapesOfList(), 0);
			BOOST_REQUIRE_EQUAL(output.str(), "ERROR: Unknown command!\n");
		}

		BOOST_AUTO_TEST_CASE(initialization_of_all_valid_shapes)
		{
			std::vector<std::string> shapes{
					"circle 650 550 100 fec821 ffff00",
					"rectangle 200 150 25 100 000000 4f81bd",
					"triangle 250 350 350 150 150 150 000000 00b0f0",
					"lineSegment 225 325 250 310 ff0000"
			};

			for (size_t i = 0; i < shapes.size(); ++i)
			{
				input << shapes[i];
				BOOST_CHECK(ch.HandleCommand());
				input.clear();
			}

			BOOST_REQUIRE_EQUAL(ch.GetNumberShapesOfList(), shapes.size());
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
