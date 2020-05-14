#pragma once

class CPoint
{
public:
	CPoint(const double x, const double y);
	double GetX() const;
	double GetY() const;

private:
	double m_x, m_y;
};
