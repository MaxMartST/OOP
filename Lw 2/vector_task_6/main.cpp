#include "RecordAndPrintVector.h"
#include "FunctionsOfVector.h"

int main()
{
	std::vector<double> vectorNumers;

	if (!ReadingDataFromStreamInVector(std::cin, vectorNumers))
	{
		std::cout << "Error: reading data from a stream to a vector" << std::endl;
		return 1;
	}

	if (!MyltiByMaxDivMinAllElemVector(vectorNumers))
	{
		std::cout << "Error: invalid value min element" << std::endl;
		return 1;
	}

	PrintSortVector(vectorNumers);

	return 0;
}