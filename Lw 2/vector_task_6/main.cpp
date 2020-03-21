#include "RecordAndPrintVector.h"

int main()
{
	auto inputVector = InitiVector(std::cin);

	if (!inputVector)
	{
		return 1;
	}

	PrintVector(*inputVector);

	return 0;
}