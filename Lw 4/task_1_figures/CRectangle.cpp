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
	  << "\tperimeter = " << to_string(GetPerimeter()) << endl
	  << "\tarea = " << to_string(GetArea()) << endl
	  << "\tline color = " << to_string(m_lineColor) << endl
	  << "\tfill color = " << to_string(m_fillColor) << endl;

	return s.str();
}

string CRectangle::GetType() const
{
	return "\n\tRectangle";
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
	s << "\tleft top vertex = (" << to_string(m_leftTopVertex.GetX()) << ", " << to_string(m_leftTopVertex.GetY())
	  << ")"
	  << "\n\twidth = " << to_string(m_width) << "\n\theight = " << to_string(m_height) << "\n";
}

void CRectangle::Draw(ICanvas& canvas)
{
	vector<CPoint> coordinate;

	coordinate.push_back(GetLeftTop());
	coordinate.push_back({ GetLeftTop().GetX(), GetRightBottom().GetY() });
	coordinate.push_back(GetRightBottom());
	coordinate.push_back({ GetRightBottom().GetX(), GetLeftTop().GetY() });

	canvas.FillPolygon(coordinate, m_fillColor);

	canvas.DrawLine(coordinate[0], coordinate[1], m_lineColor);
	canvas.DrawLine(coordinate[1], coordinate[2], m_lineColor);
	canvas.DrawLine(coordinate[2], coordinate[3], m_lineColor);
	canvas.DrawLine(coordinate[3], coordinate[0], m_lineColor);
}