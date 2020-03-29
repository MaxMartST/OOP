#include "pch.h"
#include "SaveDictionary.h"
#include "InitializeDictionary.h"
#include "Interpreter.h"
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

std::optional<std::string> ParsingArguments(int argc, char* argv[])
{
	if (argc > 2)
	{
		std::cout << "Useg: mini_translator <input.txt> OR mini_translator <null>" << std::endl;
		return std::nullopt;
	}

	if (argc = 2)
	{
		return argv[1];
	}

	return std::nullopt;
}

int main(int argc, char* argv[])
{
	//setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//если есть файл загрузки словаря, то производим его инициализацию
	auto args = ParsingArguments(argc, argv);

	Dictionary dictionary;

	if (args)
	{
		dictionary = GetDictionaryFromInputFile(*args);
	}

	Interpreter(dictionary);
	SaveDictionary(dictionary);

	return 0;
}