#include "pch.h"
#include "CCommandHandler.h"
#include "CCircle.h"
#include "CCanvas.h"
#include "CErrorMessage.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace sf;

CCommandHandler::CCommandHandler(istream& input, ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({ { "lineSegment", bind(&CCommandHandler::CreateLineSegment, this, placeholders::_1) },
		  { "triangle", bind(&CCommandHandler::CreateTriangle, this, placeholders::_1) },
		  { "rectangle", bind(&CCommandHandler::CreateRectangle, this, placeholders::_1) },
		  { "circle", bind(&CCommandHandler::CreateCircle, this, placeholders::_1) } })
{
}

void CCommandHandler::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
	}
	else
	{
		m_output << "ERROR: Unknown command!\n";
	}
}

void CCommandHandler::CreateLineSegment(istream& args)
{
	vector<double> coordinate;
	vector<string> shapeDescription;
	string description;
	getline(args, description);

	if (description.empty())
	{
		throw CErrorMessage("ERROR: No arguments!\n");
	}

	boost::split(shapeDescription, description, boost::is_any_of(" "));

	if (shapeDescription.size() != 6)
	{
		throw CErrorMessage("ERROR: Not all arguments of the [line] are indicated!\n");
	}

	try
	{
		for (size_t arg = 1; arg <= 4; ++arg)
		{
			coordinate.push_back(stod(shapeDescription[arg]));
		}
	}
	catch (const invalid_argument&)
	{
		throw invalid_argument("ERROR: Line coordinate conversion cannot be performed!\n");
	}
	catch (const out_of_range&)
	{
		throw out_of_range("ERROR: Line coordinate values go out of range!\n");
	}

	CPoint node1 = { coordinate[0], coordinate[1] };
	CPoint node2 = { coordinate[2], coordinate[3] };
	uint32_t lineColor;

	try
	{
		char* pEnd;
		lineColor = strtoul(shapeDescription[5].c_str(), &pEnd, 16);
	}
	catch (const invalid_argument&)
	{
		throw invalid_argument("ERROR: Wrong color format!\n");
	}

	auto lineSegment = make_unique<CLineSegment>(node1, node2, lineColor);
	m_shapeList.push_back(move(lineSegment));
	m_output << "Line segment is created\n";
}

void CCommandHandler::CreateTriangle(istream& args)
{
	vector<double> coordinate;
	vector<string> shapeDescription;
	string description;

	getline(args, description);

	if (description.empty())
	{
		throw CErrorMessage("ERROR: No arguments!\n");
	}

	boost::split(shapeDescription, description, boost::is_any_of(" "));

	if (shapeDescription.size() != 9)
	{
		throw CErrorMessage("ERROR: Not all arguments of the [triangle] are indicated!\n");
	}

	try
	{
		for (size_t arg = 1; arg <= 6; ++arg)
		{
			coordinate.push_back(stod(shapeDescription[arg]));
		}
	}
	catch (const invalid_argument&)
	{
		throw invalid_argument("ERROR: [triangle] coordinate conversion cannot be performed!\n");
	}
	catch (const out_of_range&)
	{
		throw out_of_range("ERROR: [triangle] coordinate values go out of range!\n");
	}

	CPoint node1 = { coordinate[0], coordinate[1] };
	CPoint node2 = { coordinate[2], coordinate[3] };
	CPoint node3 = { coordinate[4], coordinate[5] };

	uint32_t lineColor;
	uint32_t fillColor;

	try
	{
		char* pEnd;
		lineColor = strtoul(shapeDescription[7].c_str(), &pEnd, 16);
		fillColor = strtoul(shapeDescription[8].c_str(), &pEnd, 16);
	}
	catch (const invalid_argument&)
	{
		throw invalid_argument("Wrong color format!\n");
	}

	auto triangle = make_unique<CTriangle>(node1, node2, node3, lineColor, fillColor);
	m_shapeList.push_back(move(triangle));
	m_output << "Triangle is created\n";
}

void CCommandHandler::CreateRectangle(istream& args)
{
	double x1, y1, width, height;
	vector<string> shapeDescription;
	string description;

	getline(args, description);

	if (description.empty())
	{
		throw CErrorMessage("ERROR: No arguments!\n");
	}

	boost::split(shapeDescription, description, boost::is_any_of(" "));

	if (shapeDescription.size() != 7)
	{
		throw CErrorMessage("ERROR: Not all arguments of the [rectangle] are indicated!\n");
	}

	try
	{
		x1 = stod(shapeDescription[1]);
		y1 = stod(shapeDescription[2]);
		width = stod(shapeDescription[3]);
		height = stod(shapeDescription[4]);
	}
	catch (const invalid_argument&)
	{
		throw invalid_argument("ERROR: [rectangle] coordinate conversion cannot be performed!\n");
	}
	catch (const out_of_range&)
	{
		throw out_of_range("ERROR: [rectangle] coordinate values go out of range!\n");
	}

	CPoint leftTopVertex = { x1, y1 };
	uint32_t lineColor;
	uint32_t fillColor;

	try
	{
		char* pEnd;
		lineColor = strtoul(shapeDescription[5].c_str(), &pEnd, 16);
		fillColor = strtoul(shapeDescription[6].c_str(), &pEnd, 16);
	}
	catch (const invalid_argument&)
	{
		throw invalid_argument("Wrong color format!\n");
	}

	auto rectangle = make_unique<CRectangle>(leftTopVertex, width, height, lineColor, fillColor);
	m_shapeList.push_back(move(rectangle));
	m_output << "Rectangle is created\n";
}

void CCommandHandler::CreateCircle(istream& args)
{
	double x1, y1, radius;
	vector<string> shapeDescription;
	string description;

	getline(args, description);

	if (description.empty())
	{
		throw CErrorMessage("ERROR: No arguments!\n");
	}

	boost::split(shapeDescription, description, boost::is_any_of(" "));

	if (shapeDescription.size() != 6)
	{
		throw CErrorMessage("ERROR: Not all arguments of the [circle] are indicated!\n");
	}

	try
	{
		x1 = stod(shapeDescription[1]);
		y1 = stod(shapeDescription[2]);
		radius = stod(shapeDescription[3]);
	}
	catch (const invalid_argument&)
	{
		throw invalid_argument("ERROR: [circle] coordinate conversion cannot be performed!\n");
	}
	catch (const out_of_range&)
	{
		throw out_of_range("ERROR: [circle] coordinate values go out of range!\n");
	}

	CPoint center = { x1, y1 };
	uint32_t lineColor;
	uint32_t fillColor;

	try
	{
		char* pEnd;
		lineColor = strtoul(shapeDescription[4].c_str(), &pEnd, 16);
		fillColor = strtoul(shapeDescription[5].c_str(), &pEnd, 16);
	}
	catch (const invalid_argument&)
	{
		throw invalid_argument("Wrong color format!\n");
	}

	auto circle = make_unique<CCircle>(center, radius, lineColor, fillColor);
	m_shapeList.push_back(move(circle));
	m_output << "Circle is created\n";
}

void CCommandHandler::PrintShapeWithMinPerimetr()
{
	if (!m_shapeList.empty())
	{
		auto shapeMinPerimeter = min_element(m_shapeList.cbegin(), m_shapeList.cend(), [](const auto& arg1, const auto& arg2) {
			return arg1->GetPerimeter() < arg2->GetPerimeter();
		});

		m_output << "Min perimeter shape: " << (*shapeMinPerimeter)->ToString() << endl;
	}
}

void CCommandHandler::PrintShapeWithMaxArea()
{
	if (!m_shapeList.empty())
	{
		auto shapeMaxArea = max_element(m_shapeList.begin(), m_shapeList.end(), [](const auto& arg1, const auto& arg2) {
			return arg1->GetArea() < arg2->GetArea();
		});

		m_output << "Max area shape: " << (*shapeMaxArea)->ToString() << endl;
	}
}

void CCommandHandler::DrawShapes() const
{
	if (m_shapeList.empty())
	{
		throw CErrorMessage("ERROR: List of shapes is empty!\n");
	}

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 700), "Shapes", sf::Style::Default, settings);
	CCanvas canvas(window);

	while (window.isOpen())
	{
		sf::Event event{};

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color(255, 255, 255));
		for (const auto& shape : m_shapeList)
		{
			shape->Draw(canvas);
		}

		window.display();
	}
}