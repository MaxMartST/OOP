#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../task_1_figures/CPoint.h"
#include "../task_1_figures/CTriangle.h"
#include "../task_1_figures/SegmentLength.h"
#include "CMockedCanvas.h"

struct Triangle_
{
	const double x1 = 0;
	const double y1 = 0;
	const double x2 = 4;
	const double y2 = 0;
	const double x3 = 0;
	const double y3 = 3;

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

		BOOST_AUTO_TEST_CASE(check_perimeter)
		{
			double edge1 = GetSegmentLength(point1, point2);
			double edge2 = GetSegmentLength(point2, point3);
			double edge3 = GetSegmentLength(point3, point1);

			BOOST_REQUIRE_EQUAL(edge1, 4);
			BOOST_REQUIRE_EQUAL(edge2, 5);
			BOOST_REQUIRE_EQUAL(edge3, 3);

			double perimeter = edge1 + edge2 + edge3;

			BOOST_REQUIRE_EQUAL(perimeter, 12);
			BOOST_REQUIRE_EQUAL(triangle.GetPerimeter(), perimeter);
		}

		BOOST_AUTO_TEST_CASE(check_area)
		{
			double edge1 = GetSegmentLength(point1, point2);
			double edge2 = GetSegmentLength(point2, point3);
			double edge3 = GetSegmentLength(point3, point1);

			double perimeter = edge1 + edge2 + edge3;
			double p = perimeter / 2;
			BOOST_REQUIRE_EQUAL(p, 6);

			double area = sqrt(p * (p - edge1) * (p - edge2) * (p - edge3));
			BOOST_REQUIRE_EQUAL(area, 6);
			BOOST_REQUIRE_EQUAL(triangle.GetArea(), area);
		}

		BOOST_AUTO_TEST_CASE(checking_figure_data_output)
		{
			std::stringstream out;
			double edge1 = GetSegmentLength(point1, point2);
			double edge2 = GetSegmentLength(point2, point3);
			double edge3 = GetSegmentLength(point3, point1);

			double perimeter = edge1 + edge2 + edge3;
			double p = perimeter / 2;
			double area = sqrt(p * (p - edge1) * (p - edge2) * (p - edge3));

			out << "\n\tTriangle:\n"
				<< "\tfirst vertex = (" << std::to_string(triangle.GetVertex1().GetX()) << ", " << std::to_string(triangle.GetVertex1().GetY())
				<< ")\n\tsecond vertex = (" << std::to_string(triangle.GetVertex2().GetX()) << ", " << std::to_string(triangle.GetVertex2().GetY())
				<< ")\n\tthird vertex = (" << std::to_string(triangle.GetVertex3().GetX()) << ", " << std::to_string(triangle.GetVertex3().GetY()) << ")\n"
				<< "\tperimeter = " << std::to_string(perimeter) << "\n"
				<< "\tarea = " << std::to_string(area) << "\n"
				<< "\tline color = " << std::to_string(lineColor) << "\n"
				<< "\tfill color = " << std::to_string(fillColor) << "\n";

			BOOST_REQUIRE_EQUAL(triangle.ToString(), out.str());
		}

		BOOST_AUTO_TEST_CASE(figure_drawing)
		{
			CMockedCanvas canvas;
			triangle.Draw(canvas);

			std::vector<std::string> result = canvas.GetFigureElements();
			BOOST_REQUIRE_EQUAL(result.size(), 4);
			BOOST_REQUIRE_EQUAL(result.at(0), "FillPolygon");
			BOOST_REQUIRE_EQUAL(result.at(1), "DrawLine");
			BOOST_REQUIRE_EQUAL(result.at(2), "DrawLine");
			BOOST_REQUIRE_EQUAL(result.at(3), "DrawLine");
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()