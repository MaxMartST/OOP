#include "RecordAndPrintVector.h"

bool ReadingDataFromStreamInVector(std::istream& inputStream, std::vector<double>& vectorNumers)
{
	vectorNumers.clear();
	copy(std::istream_iterator<double>(inputStream), (std::istream_iterator<double>()), std::back_inserter(vectorNumers));

	if (!inputStream.eof())
	{
		std::cout << "Error writing to vector from stream!" << std::endl;
		return false;
	}

	return true;
}

void PrintSortVector(std::vector<double>& outVector)
{
	//std::sort(outVector.begin(), outVector.end());

	for (const double& value : outVector)
	{
		std::cout << std::setprecision(3) << std::fixed << value << " ";
	}
}