#include "pch.h"
#include "InitializeDictionary.h"
#include "Interpreter.h"
#include "SaveDictionary.h"

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string fileName;
	if (!ParseDictionaryFileName(argc, argv, fileName))
	{
		return 1;
	}

	Dictionary dictionary(fileName);

	if (!dictionary.dictionaryFileName.empty())
	{
		DictionaryInitialization(dictionary);
	}

	Interpreter(dictionary);
	SaveDictionary(dictionary);

	return 0;
}