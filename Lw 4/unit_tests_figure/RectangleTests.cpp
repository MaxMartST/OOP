#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../task_1_figures/CRectangle.h"
#include "../task_1_figures/CPoint.h"

struct Rectangle_
{
	const double x = 240;
	const double y = 340;

	const double width = 160;
	const double height = 30;

	const uint32_t lineColor = 0;
	const uint32_t fillColor = 16569781;

	CPoint point;
	CRectangle rectangle;
	Rectangle_()
		: point(x, y)
		, rectangle(point, width, height, lineColor, fillColor)
	{}
};

BOOST_AUTO_TEST_SUITE(rectangle_initialization_check)

	BOOST_FIXTURE_TEST_SUITE(Rectangle, Rectangle_)

		BOOST_AUTO_TEST_CASE(is_a_ISolidShape)
		{
			BOOST_CHECK(static_cast<const ISolidShape*>(&rectangle));
		}

		BOOST_AUTO_TEST_CASE(is_a_IShape)
		{
			BOOST_CHECK(static_cast<const IShape*>(&rectangle));
		}

		BOOST_AUTO_TEST_CASE(is_a_ICanvasDrawable)
		{
			BOOST_CHECK(static_cast<const ICanvasDrawable*>(&rectangle));
		}

		BOOST_AUTO_TEST_CASE(correct_rectangle_coordinates_left_top_x_and_y)
		{
			BOOST_REQUIRE_EQUAL(rectangle.GetLeftTop().GetX(), x);
			BOOST_REQUIRE_EQUAL(rectangle.GetLeftTop().GetY(), y);
		}

		BOOST_AUTO_TEST_CASE(correct_rectangle_coordinates_right_bottom_x_and_y)
		{
			const double bottonX = rectangle.GetLeftTop().GetX() + width;
			const double bottonY = rectangle.GetLeftTop().GetY() - height;

			BOOST_REQUIRE_EQUAL(rectangle.GetRightBottom().GetX(), bottonX);
			BOOST_REQUIRE_EQUAL(rectangle.GetRightBottom().GetY(), bottonY);
		}

		BOOST_AUTO_TEST_CASE(correct_width_and_height)
		{
			BOOST_REQUIRE_EQUAL(rectangle.GetWidth(), width);
			BOOST_REQUIRE_EQUAL(rectangle.GetHeight(), height);
		}

		BOOST_AUTO_TEST_CASE(check_color_line_and_fill)
		{
			BOOST_REQUIRE_EQUAL(rectangle.GetOutlineColor(), lineColor);
			BOOST_REQUIRE_EQUAL(rectangle.GetFillColor(), fillColor);
		}

		BOOST_AUTO_TEST_CASE(check_area_and_perimeter)
		{
			BOOST_REQUIRE_EQUAL(rectangle.GetArea(), width * height);
			BOOST_REQUIRE_EQUAL(rectangle.GetPerimeter(), width * 2 + height * 2);
		}

		BOOST_AUTO_TEST_CASE(checking_figure_data_output)
		{
			std::stringstream out;
			const double perimetr = width * 2 + height * 2;
			const double area = width * height;

			out << "\n\tRectangle:\n"
				<< "\tleft top vertex = (" << std::to_string(x) << ", " << std::to_string(y) << ")"
				<< "\n\twidth = " << std::to_string(width) << "\n\theight = " << std::to_string(height) << "\n"
				<< "\tperimeter = " << std::to_string(perimetr) << "\n"
				<< "\tarea = " << std::to_string(area) << "\n"
				<< "\tline color = " << std::to_string(lineColor) << "\n"
				<< "\tfill color = " << std::to_string(fillColor) << "\n";

			BOOST_REQUIRE_EQUAL(rectangle.ToString(), out.str());
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()