#include "pch.h"
#include "InitializeDictionary.h"
#include "Interpreter.h"
#include "SaveDictionary.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

bool ParseDictionaryFileName(int argc, char* argv[], std::string& fileName)
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

	std::cout << "Количество аргументов превышено" << std::endl;
	return false;
}

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