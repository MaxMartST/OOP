#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../task_1_figures/CLineSegment.h"
#include "../task_1_figures/CPoint.h"
#include "../task_1_figures/SegmentLength.h"
#include "CMockedCanvas.h"

struct LineSegment_
{
	const double x1 = 0;
	const double y1 = 4;
	const double x2 = 3;
	const double y2 = 0;

	const uint32_t lineColor = 0;

	CPoint point1;
	CPoint point2;
	CLineSegment line;

	LineSegment_()
		: point1(x1, y1)
		, point2(x2, y2)
		, line(point1, point2, lineColor)
	{}
};

BOOST_AUTO_TEST_SUITE(line_initialization_check)
	BOOST_FIXTURE_TEST_SUITE(LineSegment, LineSegment_)

		BOOST_AUTO_TEST_CASE(is_a_IShape)
		{
			BOOST_CHECK(static_cast<const IShape*>(&line));
		}

		BOOST_AUTO_TEST_CASE(is_a_ICanvasDrawable)
		{
			BOOST_CHECK(static_cast<const ICanvasDrawable*>(&line));
		}

		BOOST_AUTO_TEST_CASE(correct_line_coordinates_start_point)
		{
			BOOST_REQUIRE_EQUAL(line.GetStartPoint().GetX(), x1);
			BOOST_REQUIRE_EQUAL(line.GetStartPoint().GetY(), y1);
		}

		BOOST_AUTO_TEST_CASE(correct_line_coordinates_end_point)
		{
			BOOST_REQUIRE_EQUAL(line.GetStartPoint().GetX(), x1);
			BOOST_REQUIRE_EQUAL(line.GetStartPoint().GetY(), y1);
		}

		BOOST_AUTO_TEST_CASE(check_color_line_and_fill)
		{
			BOOST_REQUIRE_EQUAL(line.GetOutlineColor(), lineColor);
		}

		BOOST_AUTO_TEST_CASE(check_perimeter)
		{
			double segmentLine = GetSegmentLength(point1, point2);
			BOOST_REQUIRE_EQUAL(segmentLine, 5);
			BOOST_REQUIRE_EQUAL(line.GetPerimeter(), segmentLine);
		}

		BOOST_AUTO_TEST_CASE(check_area)
		{
			BOOST_REQUIRE_EQUAL(line.GetArea(), 0);
		}

		BOOST_AUTO_TEST_CASE(checking_figure_data_output)
		{
			std::stringstream out;
			double segmentLine = GetSegmentLength(point1, point2);
			double area = 0;

			out << "\n\tLine segment:\n"
				<< "\tbegins = (" << std::to_string(point1.GetX()) << ", " << std::to_string(point1.GetY())
				<< ")\n\tends = (" << std::to_string(point2.GetX()) << ", " << std::to_string(point2.GetY()) << ")\n"
				<< "\tlength = " << std::to_string(segmentLine) << "\n"
				<< "\tcolor = " << std::to_string(lineColor) << "\n";

			BOOST_REQUIRE_EQUAL(line.ToString(), out.str());
		}

		BOOST_AUTO_TEST_CASE(figure_drawing)
		{
			CMockedCanvas canvas;
			line.Draw(canvas);

			std::vector<std::string> result = canvas.GetFigureElements();
			BOOST_REQUIRE_EQUAL(result.size(), 1);
			BOOST_REQUIRE_EQUAL(result.at(0), "DrawLine");
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()