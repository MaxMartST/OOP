#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../mini_translator/InitializeDictionary.h"
#include "../mini_translator/Interpreter.h"
#include "../mini_translator/SaveDictionary.h"
#include "../mini_translator/pch.h"

TEST_CASE("Structure initialization Word")
{
	Word word;
	std::string str = "cat";

	SECTION("Creating a structure object and assigning a value to the keyWord field. Default word Status")
	{
		word.keyWord = "cat";

		REQUIRE(word.keyWord == str);
		REQUIRE(word.statusWord == Status::OLD);
	}

	SECTION("Changing the value of the status field")
	{
		word.keyWord = str;
		word.statusWord = Status::NEW;

		REQUIRE(word.statusWord == Status::NEW);
	}
}

TEST_CASE("Structure initialization Dictionary")
{
	std::string fileName = "dictionary.txt";
	Dictionary dictionary(fileName);

	SECTION("Constructor initialization with value. Default Dictionary Status.")
	{
		REQUIRE(dictionary.dictionaryFileName == fileName);
		REQUIRE(dictionary.statusDictionary == Status::OLD);
	}

	SECTION("Adding pairs: word and translation")
	{
		Word word1;
		std::string str = "cat";
		word1.keyWord = str;
		word1.statusWord = Status::NEW;

		std::vector<std::string> trabslator;
		trabslator.push_back("кот");
		trabslator.push_back("кошка");

		dictionary.dictionaryWords.emplace(word1, trabslator);
		dictionary.statusDictionary = Status::NEW;

		std::map<Word, std::vector<std::string>>::iterator it = dictionary.dictionaryWords.begin();

		REQUIRE(it->first.keyWord == str);
		REQUIRE(it->second == trabslator);
		REQUIRE(dictionary.statusDictionary == Status::NEW);
	}
}

TEST_CASE("Parse file name for dictionary")
{
	std::string projectPath = "C:\\IPS\\My repos\\OOP\\Lw 2\\x64\\Debug\\mini_translator.exe";
	std::string fileName = "dictionary.txt";

	SECTION("Indicating boot file")
	{
		std::string file;
		char arg[][255] = { "C:\\IPS\\My repos\\OOP\\Lw 2\\x64\\Debug\\mini_translator.exe", "dictionary.txt" };
		char* str[2];
		int numberArguments = 2;

		str[0] = &arg[0][0];
		str[1] = &arg[1][0];

		REQUIRE(ParseDictionaryFileName(numberArguments, str, file));
	}

	SECTION("No boot file specified")
	{
		std::string file;
		char arg[][255] = { "C:\\IPS\\My repos\\OOP\\Lw 2\\x64\\Debug\\mini_translator.exe" };
		char* str[2];
		int numberArguments = 1;

		str[0] = &arg[0][0];

		REQUIRE(ParseDictionaryFileName(numberArguments, str, file));
	}

	SECTION("Number of arguments is higher than allowed")
	{
		std::string file;
		char arg[][255] = { "C:\\IPS\\My repos\\OOP\\Lw 2\\x64\\Debug\\mini_translator.exe", "input.txt", "output.txt" };
		char* str[3];
		int numberArguments = 3;

		str[0] = &arg[0][0];
		str[1] = &arg[1][0];
		str[2] = &arg[2][0];

		REQUIRE(!ParseDictionaryFileName(numberArguments, str, file));
	}
}

TEST_CASE("Initializing a dictionary from a file")
{
	std::string fileName = "dictionary.txt";
	Dictionary dictionary(fileName);

	std::vector<std::string> word = {
		{ "cat" },
		{ "dog" },
		{ "good day" },
		{ "home" },
		{ "language" }
	};

	std::vector<std::vector<std::string>> trabslator = {
		{ "кошка", "кот" },
		{ "собака" },
		{ "хороший день" },
		{ "дом" },
		{ "язык" }
	};

	DictionaryInitialization(dictionary);
	std::map<Word, std::vector<std::string>>::iterator it = dictionary.dictionaryWords.begin();

	size_t sizeDictionary = dictionary.dictionaryWords.size();

	REQUIRE(sizeDictionary == 5);

	for (size_t inWor = 0; inWor < sizeDictionary; ++inWor)
	{
		REQUIRE(it->first.keyWord == word.at(inWor));
		for (size_t iDi = 0; iDi < it->second.size(); ++iDi)
		{
			REQUIRE(it->second.at(iDi) == trabslator[inWor][iDi]);
		}
		advance(it, 1);
	}
}

TEST_CASE("Translation output of the specified word.")
{
	std::string fileName = "dictionary.txt";
	Dictionary dictionary(fileName);
	DictionaryInitialization(dictionary);

	SECTION("Dictionary translation search. GetRussianTranslation")
	{
		std::string word = { "cat" };
		std::vector<std::string> trabslatorWord = { "кошка", "кот" };

		auto translation = GetRussianTranslation(dictionary, word);

		REQUIRE(translation.value().size() == 2);
		REQUIRE(GetRussianTranslation(dictionary, word).value() == trabslatorWord);
	}

	SECTION("Search for a translation of a word that is not in the dictionary. GetRussianTranslation")
	{
		std::string word = { "star" };

		REQUIRE(GetRussianTranslation(dictionary, word) == std::nullopt);
	}

	SECTION("Dictionary translation search. GetEnglishTranslation")
	{
		std::string word = { "кот" };
		std::string translationWord = { "cat" };

		auto translation = GetEnglishTranslation(dictionary, word);

		REQUIRE(translation.value() == translationWord);
	}

	SECTION("Search for a translation of a word that is not in the dictionary. GetEnglishTranslation")
	{
		std::string word = { "звезда" };
		std::string translationWord = { "star" };

		REQUIRE(GetRussianTranslation(dictionary, word) == std::nullopt);
	}
}

TEST_CASE("Adding new words to the dictionary")
{
	std::string fileName = "dictionary.txt";
	Dictionary dictionary(fileName);
	DictionaryInitialization(dictionary);

	size_t sizeDictionary = dictionary.dictionaryWords.size();
	std::map<Word, std::vector<std::string>>::iterator it;

	SECTION("Adding a new word will change the status of the dictionary and the number of words in it")
	{
		std::string newWord = { "star" };
		std::string translationWord = { "звезда" };

		Word word;
		word.keyWord = newWord;

		AddWordDictionary(newWord, translationWord, dictionary);
		it = dictionary.dictionaryWords.find(word);

		REQUIRE(dictionary.dictionaryWords.size() == sizeDictionary + 1);
		REQUIRE(dictionary.statusDictionary == Status::NEW);
		REQUIRE(it->second.at(0) == translationWord);
		REQUIRE(it->first.statusWord == Status::NEW);
	}
}

TEST_CASE("Saving the dictionary to a file")
{
	std::stringstream output;

	SECTION("Saving the dictionary to a file when the name is specified")
	{
		std::string fileName = "dictionary.txt";
		Dictionary dictionary(fileName);
		DictionaryInitialization(dictionary);
	
		std::string newWord = { "star" };
		std::string translationWord = { "звезда" };

		AddWordDictionary(newWord, translationWord, dictionary);

		REQUIRE(IterateOverDictionary(dictionary, output));
		REQUIRE(output.str() == "star: звезда\n");
	}

	SECTION("Saving the dictionary to a file when no name is specified")
	{
		std::string fileName = "";
		Dictionary dictionary(fileName);
		DictionaryInitialization(dictionary);
		
		std::string newWord1 = { "star" };
		std::string translationWord1 = { "звезда" };

		std::string newWord2 = { "window" };
		std::string translationWord2 = { "окно" };

		REQUIRE(dictionary.dictionaryWords.size() == 0);

		AddWordDictionary(newWord1, translationWord1, dictionary);
		AddWordDictionary(newWord2, translationWord2, dictionary);

		REQUIRE(dictionary.dictionaryWords.size() == 2);

		REQUIRE(IterateOverDictionary(dictionary, output));
		REQUIRE(output.str() == "star: звезда\nwindow: окно\n");
	}
}