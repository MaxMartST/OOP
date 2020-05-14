#include "pch.h"
#include "CRectangle.h"
#include "CPoint.h"

using namespace std;

CRectangle::CRectangle(const CPoint& leftTop, const double width, const double height, const uint32_t lineColor, const uint32_t fillColor)
	: m_leftTopVertex(leftTop)
	, m_width(width)
	, m_height(height)
	, m_lineColor(lineColor)
	, m_fillColor(fillColor)
{
}

string CRectangle::ToString() const
{
	ostringstream s;
	s << GetType() << ":" << endl;

	AppendProperties(s);

	s << setprecision(4)
	  << "\tperimeter = " << GetPerimeter() << endl
	  << "\tarea = " << GetArea() << endl
	  << "\tline color = " << m_lineColor << endl
	  << "\tfill color = " << m_fillColor << endl;

	return s.str();
}

string CRectangle::GetType() const
{
	return "Rectangle";
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopVertex;
}

CPoint CRectangle::GetRightBottom() const
{
	CPoint rigthBttom(m_leftTopVertex.GetX() + m_width, m_leftTopVertex.GetY() - m_height);
	return rigthBttom;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

double CRectangle::GetPerimeter() const
{
	return GetWidth() * 2 + GetHeight() * 2;
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_lineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

void CRectangle::AppendProperties(ostream& s) const
{
	s << "\tleft top vertex = (" << m_leftTopVertex.GetX() << ", " << m_leftTopVertex.GetY()
	  << "), width = " << m_width << ", height = " << m_height << endl;
}
