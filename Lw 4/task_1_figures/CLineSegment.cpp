#include "pch.h"
#include "CLineSegment.h"
#include "SegmentLength.h"
#include "CPoint.h"

using namespace std;

CLineSegment::CLineSegment(const CPoint& point1, const CPoint& point2, const uint32_t color)
	: m_startPoint(point1)
	, m_endPoint(point2)
	, m_color(color)
{
}

string CLineSegment::ToString() const
{
	ostringstream s;
	s << GetType() << ":" << endl;

	AppendProperties(s);

	s << setprecision(3)
	  << "\tlength = " << to_string(GetPerimeter()) << "\n"
	  << "\tcolor = " << to_string(m_color) << "\n";

	return s.str();
}

string CLineSegment::GetType() const
{
	return "\n\tLine segment";
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

double CLineSegment::GetPerimeter() const
{
	return GetSegmentLength(m_endPoint, m_startPoint);
}

double CLineSegment::GetArea() const
{
	return 0;
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_color;
}

void CLineSegment::AppendProperties(ostream& s) const
{
	s << "\tbegins = (" << to_string(m_startPoint.GetX()) << ", " << to_string(m_startPoint.GetY())
	  << ")\n\tends = (" << to_string(m_endPoint.GetX()) << ", " << to_string(m_endPoint.GetY()) << ")\n";
}

void CLineSegment::Draw(ICanvas& canvas)
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_color);
}