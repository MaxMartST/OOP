#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "ConnectedFiles.h"

using namespace std;
using namespace sf;

TEST_CASE("Checking the operation of the CCommandHandler class")
{
	GIVEN("Command handler ready to accept a command from the input stream")
	{
		stringstream input, output, out;
		CCommandHandler ch(input, output);

		WHEN("Initialize rectangle")
		{
			REQUIRE(ch.GetNumberShapesOfList() == 0);

			input << "rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00";
			ch.HandleCommand();

			THEN("One record will be entered in the list of figures")
			{
				REQUIRE(ch.GetNumberShapesOfList() == 1);
			}
		}

		AND_WHEN("Initialization of a rectangle with invalid arguments")
		{
			THEN("Error message output if the number of arguments is incorrect")
			{
				input << "rectangle 20.15 30.7 40.4 ff0000 00ff00";
				ch.HandleCommand();

				REQUIRE(ch.GetNumberShapesOfList() == 0);
				REQUIRE(output.str() == "ERROR: Not all arguments of the [rectangle] are indicated!\n");
			}

			AND_THEN("Error message about invalid rectangle coordinate arguments")
			{
				input << "rectangle 10#3 20.15 30.7 40.4 ff0000 00ff00";
				ch.HandleCommand();

				REQUIRE(ch.GetNumberShapesOfList() == 0);
				REQUIRE(output.str() == "ERROR: Invalid coordinate argument encountered in [rectangle] command!\n");
			}

			AND_THEN("Error message about invalid rectangle color arguments")
			{
				input << "rectangle 10.3 20.15 30.7 40.4 f#0000 00ff00";
				ch.HandleCommand();

				REQUIRE(ch.GetNumberShapesOfList() == 0);
				REQUIRE(output.str() == "ERROR: Invalid color argument detected in [rectangle] command!\n");
			}

			AND_THEN("Error message about invalid rectangle color arguments")
			{
				input << "rectangle 10.3 20.15 30.7 40.4 ff0000000000000 00ff00";
				ch.HandleCommand();

				REQUIRE(ch.GetNumberShapesOfList() == 0);
				REQUIRE(output.str() == "ERROR: Invalid color argument detected in [rectangle] command!\n");
			}

			AND_THEN("Error message about invalid rectangle coordinate arguments: height or width less than zero")
			{
				input << "rectangle 10.3 20.15 -30.7 40.4 ff0000 00ff00";
				ch.HandleCommand();

				REQUIRE(ch.GetNumberShapesOfList() == 0);
				REQUIRE(output.str() == "ERROR: The height and width of the [rectangle] cannot be less than zero!\n");
			}
		}

		AND_WHEN("Trying to initialize a shape other than a triangle, circle, line, and rectangle")
		{
			THEN("Error message: Unknown command")
			{
				input << "cylinder 10.3 20.15 30 80 ff0000 00ff00";
				ch.HandleCommand();

				REQUIRE(ch.GetNumberShapesOfList() == 0);
				REQUIRE(output.str() == "ERROR: Unknown command!\n");
			}
		}

		AND_WHEN("Initialization of all valid shapes")
		{
			vector<string> shapes{
				"circle 650 550 100 fec821 ffff00",
				"rectangle 200 150 25 100 000000 4f81bd",
				"triangle 250 350 350 150 150 150 000000 00b0f0",
				"lineSegment 225 325 250 310 ff0000"
			};

			THEN("All shapes are initialized and listed")
			{
				for (size_t i = 0; i < shapes.size(); ++i)
				{
					input << shapes[i];
					ch.HandleCommand();
					input.clear();
				}

				REQUIRE(ch.GetNumberShapesOfList() == shapes.size());
			}
		}
	}
}

TEST_CASE("Check initialization and CLineSegment class methods")
{
	GIVEN("Command handler ready to accept a command from the input stream")
	{
		CPoint point1 = { 250, 350 };
		CPoint point2 = { 250, 340 };
		uint32_t lineColor = 10069432;

		WHEN("Initialize object CLineSegment")
		{
			CLineSegment lineSegment(point1, point2, lineColor);

			THEN("The following statements will be true")
			{
				CPoint startPoint = lineSegment.GetStartPoint();
				REQUIRE(startPoint.GetX() == 250);
				REQUIRE(startPoint.GetY() == 350);

				CPoint endPoint = lineSegment.GetEndPoint();
				REQUIRE(endPoint.GetX() == 250);
				REQUIRE(endPoint.GetY() == 340);

				REQUIRE(lineSegment.GetType() == "\n\tLine segment");

				REQUIRE(lineSegment.GetArea() == 0);
				REQUIRE(lineSegment.GetOutlineColor() == lineColor);
				REQUIRE(lineSegment.GetPerimeter() == 10);
				REQUIRE(lineSegment.ToString() == "\n\tLine segment:\n\tbegins = (250, 350)\n\tends = (250, 340)\n\tlength = 10\n\tcolor = 10069432\n");
			}
		}
	}
}

TEST_CASE("Check initialization and CTriangle class methods")
{
	GIVEN("Command handler ready to accept a command from the input stream")
	{
		CPoint point1 = { 250, 400 };
		CPoint point2 = { 280, 425 };
		CPoint point3 = { 280, 375 };
		uint32_t lineColor = 0;
		uint32_t fillColor = 16711680;

		WHEN("Initialize object CTriangle")
		{
			CTriangle triangle(point1, point2, point3, lineColor, fillColor);

			THEN("The following statements will be true")
			{
				REQUIRE(triangle.GetVertex1().GetX() == 250);
				REQUIRE(triangle.GetVertex1().GetY() == 400);
				REQUIRE(triangle.GetVertex2().GetX() == 280);
				REQUIRE(triangle.GetVertex2().GetY() == 425);
				REQUIRE(triangle.GetVertex3().GetX() == 280);
				REQUIRE(triangle.GetVertex3().GetY() == 375);

				REQUIRE(triangle.GetType() == "\n\tTriangle");

				REQUIRE(triangle.GetArea() == Approx(750).epsilon(0.001));
				REQUIRE(triangle.GetPerimeter() == Approx(128.1).epsilon(0.001));

				REQUIRE(triangle.GetOutlineColor() == 0);
				REQUIRE(triangle.GetFillColor() == 16711680);

				REQUIRE(triangle.ToString() == "\n\tTriangle:\n\tfirst vertex = (250, 400)\n\tsecond vertex = (280, 425)\n\tthird vertex = (280, 375)\n\tperimeter = 128.1\n\tarea = 750\n\tline color = 0\n\tfill color = 16711680\n");
			}
		}
	}
}

TEST_CASE("Check initialization and CRectangle class methods")
{
	GIVEN("Command handler ready to accept a command from the input stream")
	{
		CPoint point = { 200, 150 };
		double width = 25;
		double height = 100;
		uint32_t lineColor = 0;
		uint32_t fillColor = 5210557;

		WHEN("Initialize object CTriangle")
		{
			CRectangle rectangle(point, width, height, lineColor, fillColor);

			THEN("The following statements will be true")
			{
				REQUIRE(rectangle.GetLeftTop().GetX() == 200);
				REQUIRE(rectangle.GetLeftTop().GetY() == 150);

				REQUIRE(rectangle.GetRightBottom().GetX() == 225);
				REQUIRE(rectangle.GetRightBottom().GetY() == 50);

				REQUIRE(rectangle.GetType() == "\n\tRectangle");

				REQUIRE(rectangle.GetArea() == Approx(2500).epsilon(0.001));
				REQUIRE(rectangle.GetPerimeter() == Approx(250).epsilon(0.001));

				REQUIRE(rectangle.GetOutlineColor() == 0);
				REQUIRE(rectangle.GetFillColor() == 5210557);

				REQUIRE(rectangle.ToString() == "\n\tRectangle:\n\tleft top vertex = (200, 150)\n\twidth = 25\n\theight = 100\n\tperimeter = 250\n\tarea = 2500\n\tline color = 0\n\tfill color = 5210557\n");
			}
		}
	}
}

TEST_CASE("Check initialization and CCircle class methods")
{
	GIVEN("Command handler ready to accept a command from the input stream")
	{
		CPoint point = { 650, 550 };
		double radius = 10;
		uint32_t lineColor = 16697377;
		uint32_t fillColor = 16776960;

		WHEN("Initialize object CCircle")
		{
			CCircle circle(point, radius, lineColor, fillColor);

			THEN("The following statements will be true")
			{
				REQUIRE(circle.GetCenter().GetX() == 650);
				REQUIRE(circle.GetCenter().GetY() == 550);

				REQUIRE(circle.GetType() == "\n\tCircle");

				REQUIRE(circle.GetRadius() == Approx(10).epsilon(0.001));
				REQUIRE(circle.GetArea() == Approx(314).epsilon(0.001));
				REQUIRE(circle.GetPerimeter() == Approx(62.83).epsilon(0.001));

				REQUIRE(circle.GetOutlineColor() == 16697377);
				REQUIRE(circle.GetFillColor() == 16776960);

				REQUIRE(circle.ToString() == "\n\tCircle:\n\tcenter = (650, 550)\n\tradius = 10\n\tperimeter = 62.83\n\tarea = 314.2\n\tline color = 16697377\n\tfill color = 16776960\n");
			}
		}
	}
}

TEST_CASE("Checking the sequence of drawing shape elements")
{
	GIVEN("Initialized figures")
	{
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		sf::RenderWindow window(sf::VideoMode(800, 700), "Shapes", sf::Style::Default, settings);

		CCanvas canvas(window);

		WHEN("Each shape has a drawing method called")
		{

			CPoint point1 = { 250, 400 };
			CPoint point2 = { 280, 425 };
			CPoint point3 = { 280, 375 };
			double radius = 10;
			double width = 25;
			double height = 100;
			uint32_t lineColor = 0;
			uint32_t fillColor = 16711680;

			CRectangle rectangle(point1, width, height, lineColor, fillColor);
			CTriangle triangle(point1, point2, point3, lineColor, fillColor);
			CCircle circle(point3, radius, lineColor, fillColor);
			CLineSegment line(point1, point3, lineColor);

			vector<string> correctHistory = { "FillPolygon",
				"DrawLine",
				"DrawLine",
				"DrawLine",
				"DrawLine",
				"FillPolygon",
				"DrawLine",
				"DrawLine",
				"DrawLine",
				"DrawCircle",
				"FillCircle",
				"DrawLine"
			};

			THEN("The name of the drawn part of the figure is added to the drawing history")
			{
				rectangle.Draw(canvas);
				triangle.Draw(canvas);
				circle.Draw(canvas);
				line.Draw(canvas);

				REQUIRE(canvas.GetDrawingHistory().size() == 12);
				REQUIRE(canvas.GetDrawingHistory() == correctHistory);
			}
		}
	}
}