#include "CompareTwoDouble.h"
#include <boost/math/special_functions/relative_difference.hpp>

bool IsEqual(double x, double y)
{
	//return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
	return boost::math::relative_difference(x, y) < std::numeric_limits<double>::epsilon();
}