#include "CMockedCanvas.h"

void CMockedCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	m_figureElements.push_back("DrawLine");
}

void CMockedCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor)
{
	m_figureElements.push_back("FillPolygon");
}

void CMockedCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
	m_figureElements.push_back("DrawCircle");
}

void CMockedCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
	m_figureElements.push_back("FillCircle");
}

std::vector<std::string> CMockedCanvas::GetFigureElements() const
{
	return m_figureElements;
}