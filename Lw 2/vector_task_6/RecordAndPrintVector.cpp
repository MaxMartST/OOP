#include "RecordAndPrintVector.h"

std::optional<std::vector<double>> GetVectorFromStream(std::istream& inputStream)
{
	std::vector<double> numers;
	copy(std::istream_iterator<double>(inputStream), (std::istream_iterator<double>()), std::back_inserter(numers));

	if (!inputStream.eof())
	{
		std::cout << "Error writing to vector from stream!" << std::endl;
		return std::nullopt;
	}

	return numers;
}

void PrintSortVector(std::ostream& outputStream, const std::vector<double>& resultVector)
{
	std::vector<double> outVector = resultVector;
	sort(outVector.begin(), outVector.end());

	for (const auto& element : outVector)
	{
		outputStream << std::fixed << std::setprecision(3) << element << " ";
	}
	outputStream << std::endl;
}