#include "pch.h"
#include "Dictionary.h"
#include "CommandLineParsing.h"
#include "InitializeDictionary.h"
#include "Interpreter.h"
#include "SaveDictionary.h"

using namespace std;

int main(int argc, char* argv[])
{
	//setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string fileName;
	if (!ParsingFileNameForDictionary(argc, argv, fileName))
	{
		return 1;
	}

	Dictionary dictionary;

	if (!fileName.empty())
	{
		DictionaryInitialization(dictionary, fileName);
	}

	Interpreter(dictionary);
	SaveDictionary(dictionary, fileName);

	return 0;
}