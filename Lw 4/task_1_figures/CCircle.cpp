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
	  << "\tperimeter = " << to_string(GetPerimeter()) << "\n"
	  << "\tarea = " << to_string(GetArea()) << "\n"
	  << "\tline color = " << to_string(m_lineColor) << "\n"
	  << "\tfill color = " << to_string(m_fillColor) << "\n";

	return s.str();
}

string CCircle::GetType() const
{
	return "\n\tCircle";
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
	s << "\tcenter = (" << to_string(m_center.GetX()) << ", " << to_string(m_center.GetY())
	  << ")\n\tradius = " << to_string(m_radius) << "\n";
}

void CCircle::Draw(ICanvas& canvas)
{
	canvas.DrawCircle(m_center, m_radius, m_lineColor);
	canvas.FillCircle(m_center, m_radius, m_fillColor);
}