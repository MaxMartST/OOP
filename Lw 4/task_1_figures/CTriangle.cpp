#include "pch.h"
#include "CTriangle.h"
#include "CPoint.h"
#include "SegmentLength.h"

using namespace std;

CTriangle::CTriangle(const CPoint& point1, const CPoint& point2, const CPoint& point3, const uint32_t lineColor, const uint32_t fillColor)
	: m_vertex1(point1)
	, m_vertex2(point2)
	, m_vertex3(point3)
	, m_lineColor(lineColor)
	, m_fillColor(fillColor)
{
}

string CTriangle::ToString() const
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

string CTriangle::GetType() const
{
	return "\n\tTriangle";
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

double CTriangle::GetPerimeter() const
{
	return GetSegmentLength(m_vertex1, m_vertex2) + GetSegmentLength(m_vertex2, m_vertex3) + GetSegmentLength(m_vertex3, m_vertex1);
}

double CTriangle::GetArea() const
{
	double a = GetSegmentLength(m_vertex1, m_vertex2);
	double b = GetSegmentLength(m_vertex2, m_vertex3);
	double c = GetSegmentLength(m_vertex3, m_vertex1);
	double p = GetPerimeter() / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_lineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

void CTriangle::AppendProperties(ostream& s) const
{
	s << "\tfirst vertex = (" << m_vertex1.GetX() << ", " << m_vertex1.GetY()
	  << ")\n\tsecond vertex = (" << m_vertex2.GetX() << ", " << m_vertex2.GetY()
	  << ")\n\tthird vertex = (" << m_vertex3.GetX() << ", " << m_vertex3.GetY() << ")" << endl;
}

void CTriangle::Draw(ICanvas& canvas)
{
	vector<CPoint> coordinate;

	coordinate.push_back(m_vertex1);
	coordinate.push_back(m_vertex2);
	coordinate.push_back(m_vertex3);

	canvas.FillPolygon(coordinate, m_fillColor);

	canvas.DrawLine(coordinate[0], coordinate[1], m_lineColor);
	canvas.DrawLine(coordinate[1], coordinate[2], m_lineColor);
	canvas.DrawLine(coordinate[2], coordinate[0], m_lineColor);
}
