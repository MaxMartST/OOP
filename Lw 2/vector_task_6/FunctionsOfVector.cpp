#include "FunctionsOfVector.h"

void ChangeVector(std::vector<double>& numbers)
{
	if (!numbers.empty())
	{
		auto minMaxElement = std::minmax_element(std::begin(numbers), std::end(numbers));

		double minElem = *minMaxElement.first;
		double maxElem = *minMaxElement.second;

		auto multiplyByMaxElement = [maxElem](double numbers) {
			return (numbers * maxElem);
		};

		auto multiplyByMaxDivideByMin = [minElem, maxElem](double numbers) {
			return ((numbers * maxElem) / minElem);
		};

		if (minElem)
		{
			std::transform(numbers.begin(), numbers.end(), numbers.begin(), multiplyByMaxDivideByMin);
		}
		else
		{
			std::transform(numbers.begin(), numbers.end(), numbers.begin(), multiplyByMaxElement);
		}
	}
}