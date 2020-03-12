#include "ParseArgument.h"
#include "LinkerBinaryFile.h"

int main(int argc, char* argv[])
{
	if (auto args = ParsArgs(argc, argv))
	{
		return FileLinker(args->command, args->inputFile, args->outputFile) ? 0 : 1;
	}
	else
	{
		return 1;
	}
}