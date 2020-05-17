#include "CCanvas.h"

using namespace std;
using namespace sf;

CCanvas::CCanvas(RenderWindow& window)
	: m_window(window)
{
}

Color ConvertColor(uint32_t color)
{
	return Color((color / (256 * 256) % 256), (color / (256) % 256), (color % 256));
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	Vertex line[] = {
		Vertex(Vector2f((float)from.GetX(), (float)m_window.getSize().y - (float)from.GetY())),
		Vertex(Vector2f((float)to.GetX(), (float)m_window.getSize().y - (float)to.GetY()))
	};

	line[0].color = ConvertColor(lineColor);
	line[1].color = ConvertColor(lineColor);

	m_window.draw(line, 2, Lines);
	m_drawingHistory.push_back("DrawLine");
}

void CCanvas::FillPolygon(vector<CPoint> points, uint32_t fillColor)
{
	ConvexShape convexShape;
	convexShape.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); i++)
	{
		convexShape.setPoint(i, Vector2f((float)points[i].GetX(), (float)m_window.getSize().y - (float)points[i].GetY()));
	}

	convexShape.setFillColor(ConvertColor(fillColor));

	m_window.draw(convexShape);
	m_drawingHistory.push_back("FillPolygon");
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
	CircleShape circle((float)radius);

	circle.setOutlineColor(ConvertColor(lineColor));
	circle.setOrigin((float)radius, (float)radius);
	circle.setOutlineThickness(0.5);
	circle.move((float)center.GetX(), (float)m_window.getSize().y - (float)center.GetY());

	m_window.draw(circle);
	m_drawingHistory.push_back("DrawCircle");
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
	CircleShape circle((float)radius);

	circle.setFillColor(ConvertColor(fillColor));
	circle.setOrigin((float)radius, (float)radius);
	circle.move((float)center.GetX(), (float)m_window.getSize().y - (float)center.GetY());

	m_window.draw(circle);
	m_drawingHistory.push_back("FillCircle");
}

vector<string> CCanvas::GetDrawingHistory()
{
	return m_drawingHistory;
}