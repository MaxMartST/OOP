#pragma once
#include "pch.h"
#include "CPoint.h"
#include "IShape.h"

class CLineSegment final : public IShape
{
public:
	CLineSegment(const CPoint& point1, const CPoint& point2, const uint32_t color);

	double GetPerimeter() const override;
	double GetArea() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	std::string GetType() const;

private:
	void AppendProperties(std::ostream& strm) const override;

	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_color;
};
