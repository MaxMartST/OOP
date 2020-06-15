#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../task_1_figures/CPoint.h"
#include "../task_1_figures/CTriangle.h"
#include "CMockedCanvas.h"

struct Triangle_
{
	const double x1 = 320;
	const double y1 = 380;
	const double x2 = 250;
	const double y2 = 200;
	const double x3 = 390;
	const double y3 = 200;

	const uint32_t lineColor = 0;
	const uint32_t fillColor = 45296;

	CPoint point1;
	CPoint point2;
	CPoint point3;
	CTriangle triangle;

	Triangle_()
		: point1(x1, y1)
		, point2(x2, y2)
		, point3(x3, y3)
		, triangle(point1, point2, point3, lineColor, fillColor)
	{}
};

BOOST_AUTO_TEST_SUITE(triangle_initialization_check)
	BOOST_FIXTURE_TEST_SUITE(Triangle, Triangle_)

		BOOST_AUTO_TEST_CASE(is_a_ISolidShape)
		{
			BOOST_CHECK(static_cast<const ISolidShape*>(&triangle));
		}

		BOOST_AUTO_TEST_CASE(is_a_IShape)
		{
			BOOST_CHECK(static_cast<const IShape*>(&triangle));
		}

		BOOST_AUTO_TEST_CASE(is_a_ICanvasDrawable)
		{
			BOOST_CHECK(static_cast<const ICanvasDrawable*>(&triangle));
		}

		BOOST_AUTO_TEST_CASE(correct_triangle_coordinates_vertex1)
		{
			BOOST_REQUIRE_EQUAL(triangle.GetVertex1().GetX(), x1);
			BOOST_REQUIRE_EQUAL(triangle.GetVertex1().GetY(), y1);
		}

		BOOST_AUTO_TEST_CASE(correct_triangle_coordinates_vertex2)
		{
			BOOST_REQUIRE_EQUAL(triangle.GetVertex2().GetX(), x2);
			BOOST_REQUIRE_EQUAL(triangle.GetVertex2().GetY(), y2);
		}

		BOOST_AUTO_TEST_CASE(correct_triangle_coordinates_vertex3)
		{
			BOOST_REQUIRE_EQUAL(triangle.GetVertex3().GetX(), x3);
			BOOST_REQUIRE_EQUAL(triangle.GetVertex3().GetY(), y3);
		}

		BOOST_AUTO_TEST_CASE(check_color_line_and_fill)
		{
			BOOST_REQUIRE_EQUAL(triangle.GetOutlineColor(), lineColor);
			BOOST_REQUIRE_EQUAL(triangle.GetFillColor(), fillColor);
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()