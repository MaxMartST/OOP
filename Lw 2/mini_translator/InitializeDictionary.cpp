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

std::pair<Word, std::vector<std::string>> ParseLine(const std::string& str)
{
	std::string keyWord;
	std::string translationWord;
	std::pair<Word, std::vector<std::string>> elemDictionary;

	auto wordEnd = str.find(TRANSLATE);
	keyWord = str.substr(0, wordEnd);
	//transform(keyWord.begin(), keyWord.end(), keyWord.begin(), tolower);
	elemDictionary.first.keyWord = keyWord;

	auto translateStart = wordEnd + TRANSLATE.length();
	translationWord = str.substr(translateStart);
	elemDictionary.second = GetTranslationVector(translationWord);

	return elemDictionary;
}

void ReadDictionaryFromStream(Dictionary& dictionary, std::istream& input)
{
	std::string str;
	std::pair<Word, std::vector<std::string>> dictionaryElem;

	while (getline(input, str))
	{
		dictionaryElem = ParseLine(str);
		dictionary.dictionaryWords.emplace(dictionaryElem.first, dictionaryElem.second);
	}
}

void DictionaryInitialization(Dictionary& dictionary)
{
	std::ifstream input(dictionary.dictionaryFileName, std::ios::in);
	if (!input.is_open())
	{
		std::cout << "Failed to open file: " << dictionary.dictionaryFileName << std::endl;
	}

	ReadDictionaryFromStream(dictionary, input);
}

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