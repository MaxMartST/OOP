#include "RecordAndPrintVector.h"

std::optional<std::vector<double>> InitiVector(std::istream& inputStream)
{
	std::vector<double> inputVector(std::istream_iterator<double>(inputStream), (std::istream_iterator<double>()));

	return inputVector;
}

void PrintVector(const std::vector<double>& outVector)
{
	std::cout << "\nSize of vector: " << outVector.size() << "\n";
	copy(outVector.begin(), outVector.end(), std::ostream_iterator<double>(std::cout, " "));
}

int Add(int x, int y)
{
	return x + y;
}