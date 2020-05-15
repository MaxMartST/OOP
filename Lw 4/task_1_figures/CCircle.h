#pragma once
#include "pch.h"
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(const CPoint& center, const double radius, const uint32_t lineColor, const uint32_t fillColor);

	double GetPerimeter() const override;
	double GetArea() const override;
	double GetRadius() const;

	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	CPoint GetCenter() const;
	std::string GetType() const;

	void Draw(ICanvas& canvas);

private:
	void AppendProperties(std::ostream& strm) const override;

	CPoint m_center;
	double m_radius;
	uint32_t m_lineColor;
	uint32_t m_fillColor;
};
