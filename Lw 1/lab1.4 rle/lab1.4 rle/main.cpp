#include "ParseArgument.h"
#include "LinkerBinaryFile.h"

int main(int argc, char* argv[])
{
	if (auto args = ParseArgs(argc, argv))
	{
		return FileLinker(*args) ? 0 : 1;
	}
	else
	{
		return 1;
	}
}