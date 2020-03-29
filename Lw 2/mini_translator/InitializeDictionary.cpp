#include "InitializeDictionary.h"

void RemoveSpaces(std::string& str)
{
	str.erase(0, str.find_first_not_of(" "));
	str.erase(str.find_last_not_of(" ") + 1);
}

std::vector<std::string> GetTranslationVector(const std::string& str)
{
	std::vector<std::string> wordsVector;
	std::istringstream inputStr(str);
	std::string word;

	while (std::getline(inputStr, word, ','))
	{
		RemoveSpaces(word);
		wordsVector.push_back(word);
	}
	return wordsVector;
}

std::pair<std::string, std::vector<std::string>> ParseLine(const std::string& str)
{
	std::string keyWord;
	std::string translationWord;
	std::pair<std::string, std::vector<std::string>> elemDictionary;

	auto wordEnd = str.find(TRANSLATE);
	keyWord = str.substr(0, wordEnd);
	transform(keyWord.begin(), keyWord.end(), keyWord.begin(), tolower);
	elemDictionary.first = keyWord;

	auto translateStart = wordEnd + TRANSLATE.length();
	translationWord = str.substr(translateStart);
	elemDictionary.second = GetTranslationVector(translationWord);

	return elemDictionary;
}

Dictionary GetDictionary(std::istream& input)
{
	Dictionary dictionary;
	std::string str;
	std::pair<std::string, std::vector<std::string>> dictionaryElem;

	while (getline(input, str))
	{
		dictionaryElem = ParseLine(str);
		dictionary.dictionaryWords.emplace(dictionaryElem.first, dictionaryElem.second);
	}

	return dictionary;
}

Dictionary GetDictionaryFromInputFile(const std::string& file)
{
	std::ifstream input(file);
	if (!input.is_open())
	{
		std::cout << "Failed to open file: " << file << std::endl;
	}

	return GetDictionary(input);
}