#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../task_1_figures/CCircle.h"
#include "../task_1_figures/CPoint.h"
#include "CMockedCanvas.h"

struct Circle_
{
	const double x = 650;
	const double y = 600;
	const double radius = 100;

	const uint32_t lineColor = 16697377;
	const uint32_t fillColor = 16776960;

	CPoint center;
	CCircle circle;

	Circle_()
		: center(x, y)
		, circle(center, radius, lineColor, fillColor)
	{
	}
};

BOOST_AUTO_TEST_SUITE(circle_initialization_check)
	BOOST_FIXTURE_TEST_SUITE(Circle, Circle_)

		BOOST_AUTO_TEST_CASE(is_a_ISolidShape)
		{
			BOOST_CHECK(static_cast<const ISolidShape*>(&circle));
		}

		BOOST_AUTO_TEST_CASE(is_a_IShape)
		{
			BOOST_CHECK(static_cast<const IShape*>(&circle));
		}

		BOOST_AUTO_TEST_CASE(is_a_ICanvasDrawable)
		{
			BOOST_CHECK(static_cast<const ICanvasDrawable*>(&circle));
		}

		BOOST_AUTO_TEST_CASE(correct_circle_coordinates_cente)
		{
			BOOST_REQUIRE_EQUAL(circle.GetCenter().GetX(), x);
			BOOST_REQUIRE_EQUAL(circle.GetCenter().GetY(), y);
		}

		BOOST_AUTO_TEST_CASE(correct_circle_radius)
		{
			BOOST_REQUIRE_EQUAL(circle.GetRadius(), radius);
		}

		BOOST_AUTO_TEST_CASE(check_color_line_and_fill)
		{
			BOOST_REQUIRE_EQUAL(circle.GetOutlineColor(), lineColor);
			BOOST_REQUIRE_EQUAL(circle.GetFillColor(), fillColor);
		}

		BOOST_AUTO_TEST_CASE(check_perimeter)
		{
			double perimeter = 2 * M_PI * radius;
			BOOST_REQUIRE_EQUAL(circle.GetPerimeter(), perimeter);
		}

		BOOST_AUTO_TEST_CASE(check_area)
		{
			double area = M_PI * pow(radius, 2);
			BOOST_REQUIRE_EQUAL(circle.GetArea(), area);
		}

		BOOST_AUTO_TEST_CASE(checking_figure_data_output)
		{
			std::stringstream out;
			double perimeter = 2 * M_PI * radius;
			double area = M_PI * pow(radius, 2);

			out << "\n\tCircle:\n"
				<< "\tcenter = (" << std::to_string(center.GetX()) << ", " << std::to_string(center.GetY())
				<< ")\n\tradius = " << std::to_string(radius) << "\n"
				<< "\tperimeter = " << std::to_string(perimeter) << "\n"
				<< "\tarea = " << std::to_string(area) << "\n"
				<< "\tline color = " << std::to_string(lineColor) << "\n"
				<< "\tfill color = " << std::to_string(fillColor) << "\n";

			BOOST_REQUIRE_EQUAL(circle.ToString(), out.str());
		}

		BOOST_AUTO_TEST_CASE(figure_drawing)
		{
			CMockedCanvas canvas;
			circle.Draw(canvas);

			std::vector<std::string> result = canvas.GetFigureElements();
			BOOST_REQUIRE_EQUAL(result.size(), 2);
			BOOST_REQUIRE_EQUAL(result.at(0), "DrawCircle");
			BOOST_REQUIRE_EQUAL(result.at(1), "FillCircle");
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()