#include "pch.h"
#include "CCommandHandler.h"
#include "AdditionalFunctions.h"
#include "CCanvas.h"
#include "CCircle.h"
#include "CErrorMessage.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CheckArguments.h"
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

bool CCommandHandler::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		try
		{
			it->second(strm);
		}
		catch (const exception& e)
		{
			m_output << e.what();
			return false;
		}
		catch (const CErrorMessage& em)
		{
			m_output << em.GetErrorMessage();
			return false;
		}
	}
	else
	{
		m_output << "ERROR: Unknown command!\n";
	}

	return true;
}

size_t CCommandHandler::GetNumberShapesOfList()
{
	return m_shapeList.size();
}

void CCommandHandler::CreateLineSegment(istream& args)
{
	vector<double> coordinate;
	vector<string> shapeDescription;
	string description;
	getline(args, description);

	if (description.empty())
	{
		throw CErrorMessage("ERROR: Shape [lineSegment] no arguments!\n");
	}

	description = RemoveExtraSpacesInLine(description);
	boost::split(shapeDescription, description, boost::is_any_of(" "));

	if (shapeDescription.size() != 5)
	{
		throw CErrorMessage("ERROR: Not all arguments of the [lineSegment] are indicated!\n");
	}

	for (size_t arg = 0; arg < 4; ++arg)
	{
		if (!CheckCoordinate(shapeDescription[arg]))
		{
			throw invalid_argument("ERROR: Invalid coordinate argument encountered in [lineSegment] command!\n");
		};
		coordinate.push_back(stod(shapeDescription[arg]));
	}

	if (!CheckColor(shapeDescription[4]))
	{
		throw invalid_argument("ERROR: Invalid color argument detected in [lineSegment] command!\n");
	};

	CPoint node1 = { coordinate[0], coordinate[1] };
	CPoint node2 = { coordinate[2], coordinate[3] };
	uint32_t lineColor;

	try
	{
		char* pEnd;
		lineColor = strtoul(shapeDescription[4].c_str(), &pEnd, 16);
	}
	catch (const invalid_argument&)
	{
		throw invalid_argument("ERROR: Wrong [lineSegment] color format!\n");
	}

	auto lineSegment = make_unique<CLineSegment>(node1, node2, lineColor);
	m_shapeList.push_back(move(lineSegment));
}

void CCommandHandler::CreateTriangle(istream& args)
{
	vector<double> coordinate;
	vector<string> shapeDescription;
	string description;

	getline(args, description);

	if (description.empty())
	{
		throw CErrorMessage("ERROR: Shape [triangle] no arguments!\n");
	}

	description = RemoveExtraSpacesInLine(description);
	boost::split(shapeDescription, description, boost::is_any_of(" "));

	if (shapeDescription.size() != 8)
	{
		throw CErrorMessage("ERROR: Not all arguments of the [triangle] are indicated!\n");
	}

	for (size_t arg = 0; arg < 6; ++arg)
	{
		if (!CheckCoordinate(shapeDescription[arg]))
		{
			throw invalid_argument("ERROR: Invalid coordinate argument encountered in [triangle] command!\n");
		};
		coordinate.push_back(stod(shapeDescription[arg]));
	}

	if (!CheckColor(shapeDescription[6]) || !CheckColor(shapeDescription[7]))
	{
		throw invalid_argument("ERROR: Invalid color argument detected in [triangle] command!\n");
	};

	CPoint node1 = { coordinate[0], coordinate[1] };
	CPoint node2 = { coordinate[2], coordinate[3] };
	CPoint node3 = { coordinate[4], coordinate[5] };

	uint32_t lineColor;
	uint32_t fillColor;

	try
	{
		char* pEnd;
		lineColor = strtoul(shapeDescription[6].c_str(), &pEnd, 16);
		fillColor = strtoul(shapeDescription[7].c_str(), &pEnd, 16);
	}
	catch (const invalid_argument&)
	{
		throw invalid_argument("ERROR: Wrong [triangle] color format!\n");
	}

	auto triangle = make_unique<CTriangle>(node1, node2, node3, lineColor, fillColor);
	m_shapeList.push_back(move(triangle));
}

void CCommandHandler::CreateRectangle(istream& args)
{
	vector<double> arguments;
	vector<string> shapeDescription;
	string description;

	getline(args, description);

	if (description.empty())
	{
		throw CErrorMessage("ERROR: Shape [rectangle] no arguments!\n");
	}

	description = RemoveExtraSpacesInLine(description);
	boost::split(shapeDescription, description, boost::is_any_of(" "));

	if (shapeDescription.size() != 6)
	{
		throw CErrorMessage("ERROR: Not all arguments of the [rectangle] are indicated!\n");
	}

	for (size_t arg = 0; arg < 4; ++arg)
	{
		if (!CheckCoordinate(shapeDescription[arg]))
		{
			throw invalid_argument("ERROR: Invalid coordinate argument encountered in [rectangle] command!\n");
		};
		arguments.push_back(stod(shapeDescription[arg]));
	}

	if (!CheckColor(shapeDescription[4]) || !CheckColor(shapeDescription[5]))
	{
		throw invalid_argument("ERROR: Invalid color argument detected in [rectangle] command!\n");
	};

	CPoint leftTopVertex = { arguments[0], arguments[1] };
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
		throw invalid_argument("ERROR: Wrong [rectangle] color format!\n");
	}

	if (arguments[2] < 0 || arguments[3] < 0)
	{
		throw invalid_argument("ERROR: The height and width of the [rectangle] cannot be less than zero!\n");
	}

	auto rectangle = make_unique<CRectangle>(leftTopVertex, arguments[2], arguments[3], lineColor, fillColor);
	m_shapeList.push_back(move(rectangle));
}

void CCommandHandler::CreateCircle(istream& args)
{
	vector<double> arguments;
	vector<string> shapeDescription;
	string description;

	getline(args, description);

	if (description.empty())
	{
		throw CErrorMessage("ERROR: Shape [circle] no arguments!\n");
	}

	description = RemoveExtraSpacesInLine(description);
	boost::split(shapeDescription, description, boost::is_any_of(" "));

	if (shapeDescription.size() != 5)
	{
		throw CErrorMessage("ERROR: Not all arguments of the [circle] are indicated!\n");
	}

	for (size_t arg = 0; arg < 3; ++arg)
	{
		if (!CheckCoordinate(shapeDescription[arg]))
		{
			throw invalid_argument("ERROR: Invalid coordinate argument encountered in [circle] command!\n");
		};
		arguments.push_back(stod(shapeDescription[arg]));
	}

	if (!CheckColor(shapeDescription[3]) || !CheckColor(shapeDescription[4]))
	{
		throw invalid_argument("ERROR: Invalid color argument detected in [circle] command!\n");
	};

	CPoint center = { arguments[0], arguments[1] };
	uint32_t lineColor;
	uint32_t fillColor;

	try
	{
		char* pEnd;
		lineColor = strtoul(shapeDescription[3].c_str(), &pEnd, 16);
		fillColor = strtoul(shapeDescription[4].c_str(), &pEnd, 16);
	}
	catch (const invalid_argument&)
	{
		throw invalid_argument("ERROR: Wrong [circle] color format!\n");
	}

	if (arguments[2] < 0)
	{
		throw invalid_argument("ERROR: The radius of the [circle] cannot be less than zero!\n");
	}

	auto circle = make_unique<CCircle>(center, arguments[2], lineColor, fillColor);
	m_shapeList.push_back(move(circle));
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
	if (!m_shapeList.empty())
	{
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
}