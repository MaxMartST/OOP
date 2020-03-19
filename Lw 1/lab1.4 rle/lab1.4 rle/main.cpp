#include "ParseArgument.h"
#include "ArchiverBinaryFile.h"

int main(int argc, char* argv[])
{
	if (auto args = ParseArgs(argc, argv))
	{
		return FileLArchiver(*args) ? 0 : 1;
	}
	else
	{
		return 1;
	}
}