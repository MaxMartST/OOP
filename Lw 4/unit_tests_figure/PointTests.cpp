#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../task_1_figures/CPoint.h"

struct Point_
{
	const double x = 27.2;
	const double y = 10.5;

	CPoint point;
	Point_()
		: point(x, y)
	{
	}
};
BOOST_AUTO_TEST_SUITE(point_initialization_check)

	BOOST_FIXTURE_TEST_SUITE(Point, Point_)
		BOOST_AUTO_TEST_CASE(correct_point_coordinates_x_and_y)
		{
			BOOST_REQUIRE_EQUAL(point.GetX(), x);
			BOOST_REQUIRE_EQUAL(point.GetY(), y);
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()