#include "CommandLineParsing.h"

using namespace std;

bool ParsingFileNameForDictionary(int argc, char* argv[], string& fileName)
{
	if (argc == 2)
	{
		fileName = argv[1];
		return true;
	}

	if (argc == 1)
	{
		return true;
	}

	cout << "Количество аргументов превышено" << endl;

	return false;
}