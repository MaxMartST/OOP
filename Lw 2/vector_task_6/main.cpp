#include "RecordAndPrintVector.h"
#include "FunctionsOfVector.h"

int main()
{
	auto vectorNumbers = GetVectorFromStream(std::cin);

	if (!vectorNumbers)
	{
		std::cout << "Error: reading data from a stream to a vector" << std::endl;
		return 1;
	}

	ChangeVector(*vectorNumbers);

	PrintSortVector(std::cout, *vectorNumbers);

	return 0;
}