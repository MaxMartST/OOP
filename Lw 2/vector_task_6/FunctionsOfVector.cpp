#include "FunctionsOfVector.h"

std::optional<std::vector<double>> ChangeVector(const std::vector<double>& numers)
{
	if (numers.empty())
	{
		return numers;
	}

	std::vector<double> resultVector = numers;
	std::vector<double>::iterator minimum, maximum;
	auto minMaxElement = std::make_pair(minimum, maximum) = std::minmax_element(std::begin(resultVector), std::end(resultVector));

	if (*minMaxElement.first == 0)
	{
		return std::nullopt;
	}

	double minElem = *minMaxElement.first;
	double maxElem = *minMaxElement.second;

	auto multiplyByMaxDivideByMin = [minElem, maxElem](double number) {
		return ((number * maxElem) / minElem);
	};
	std::transform(resultVector.begin(), resultVector.end(), resultVector.begin(), multiplyByMaxDivideByMin);

	return resultVector;
}