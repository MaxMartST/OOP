#include "CompareTwoDouble.h"

bool IsEqual(double x, double y)
{
	return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}