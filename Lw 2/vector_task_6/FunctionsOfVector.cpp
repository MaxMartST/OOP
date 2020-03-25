#include "FunctionsOfVector.h"

bool MyltiByMaxDivMinAllElemVector(std::vector<double>& vectorNumers)
{
	if (vectorNumers.empty())
	{
		return true;
	}

	std::vector<double>::iterator minimum, maximum;
	auto minMaxElement = std::make_pair(minimum, maximum) = std::minmax_element(std::begin(vectorNumers), std::end(vectorNumers));

	if (*minMaxElement.first == 0)
	{
		return false;
	}

	double minElem = *minMaxElement.first;
	double maxElem = *minMaxElement.second;

	auto multiplyByMaxDivideByMin = [minElem, maxElem](double number) {
		return ((number * maxElem) / minElem);
	};
	std::transform(vectorNumers.begin(), vectorNumers.end(), vectorNumers.begin(), multiplyByMaxDivideByMin);

	return true;
}