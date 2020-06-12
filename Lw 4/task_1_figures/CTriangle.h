#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include <string>
#include <cstdint>
#include <iostream>

class CTriangle : public ISolidShape
{
public:
	CTriangle(const CPoint& point1, const CPoint& point2, const CPoint& point3, const uint32_t lineColor, const uint32_t fillColor);

	double GetPerimeter() const override;
	double GetArea() const override;

	std::string GetType() const;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	void Draw(ICanvas& canvas) override;

private:
	void AppendProperties(std::ostream& strm) const override;

	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;

	uint32_t m_lineColor;
	uint32_t m_fillColor;
};
