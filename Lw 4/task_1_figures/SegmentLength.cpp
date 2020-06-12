#include "CLineSegment.h"
#include "pch.h"

double GetSegmentLength(const CPoint& point1, const CPoint& point2)
{
	return sqrt(pow(point1.GetX() - point2.GetX(), 2) + pow(point1.GetY() - point2.GetY(), 2));
};