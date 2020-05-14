#pragma once
#include "pch.h"
#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(const CPoint& point1, const CPoint& point2, const CPoint& point3, const uint32_t lineColor, const uint32_t fillColor);
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	double GetArea() const override;
	uint32_t GetFillColor() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	std::string GetType() const;

private:
	void AppendProperties(std::ostream& strm) const override;

	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	uint32_t m_lineColor;
	uint32_t m_fillColor;
};
