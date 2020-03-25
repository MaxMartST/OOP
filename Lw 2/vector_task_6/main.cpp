#include "RecordAndPrintVector.h"
#include "FunctionsOfVector.h"

int main()
{
	auto vectorNumers = GetVectorFromStream(std::cin);

	if (!vectorNumers)
	{
		std::cout << "Error: reading data from a stream to a vector" << std::endl;
		return 1;
	}

	auto resultVector = ChangeVector(*vectorNumers);

	if (!resultVector)
	{
		std::cout << "Error: invalid value min element" << std::endl;
		return 1;
	}

	PrintSortVector(std::cout , *vectorNumers);

	return 0;
}