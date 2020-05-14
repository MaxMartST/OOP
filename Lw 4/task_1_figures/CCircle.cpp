#include "pch.h"
#include "CCircle.h"

using namespace std;

CCircle::CCircle(const CPoint& center, const double radius, const uint32_t lineColor, const uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_lineColor(lineColor)
	, m_fillColor(fillColor)
{
}

string CCircle::ToString() const
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

string CCircle::GetType() const
{
	return "Circle";
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * GetRadius();
}

double CCircle::GetArea() const
{
	return M_PI * pow(GetRadius(), 2);
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_lineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

void CCircle::AppendProperties(ostream& s) const
{
	s << "\tcenter = ( " << m_center.GetX() << " , " << m_center.GetY()
	  << " ), radius = " << m_radius << endl;
}
