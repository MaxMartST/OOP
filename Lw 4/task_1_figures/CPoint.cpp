#include "pch.h"
#include "CPoint.h"

CPoint::CPoint(const double x, const double y)
	: m_x(x)
	, m_y(y)
{
}

double CPoint::GetX() const
{
	return m_x;
}

double CPoint::GetY() const
{
	return m_y;
}
