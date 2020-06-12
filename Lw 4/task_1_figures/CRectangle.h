#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include <cstdint>
#include <string>
#include <iostream>
#include <cstddef>

class CRectangle : public ISolidShape
{
public:
	CRectangle(const CPoint& rightBottom, const double width, const double height, const uint32_t lineColor, const uint32_t fillColor);

	double GetPerimeter() const override;
	double GetArea() const override;
	double GetWidth() const;
	double GetHeight() const;

	std::string GetType() const;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

	void Draw(ICanvas& canvas) override;

private:
	void AppendProperties(std::ostream& strm) const override;

	CPoint m_leftTopVertex;

	double m_width;
	double m_height;

	uint32_t m_lineColor;
	uint32_t m_fillColor;

	size_t const NODE = 4;
};
