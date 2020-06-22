#include "InitializeDictionary.h"
#include "pch.h"
#include <regex>

using namespace std;

void RemoveSpaces(string& str)
{
	str.erase(0, str.find_first_not_of(" "));
	str.erase(str.find_last_not_of(" ") + 1);
}

vector<string> GetTranslationVector(const string& str)
{
	vector<string> wordsVector;
	istringstream inputStr(str);
	string word;

	while (getline(inputStr, word, ','))
	{
		RemoveSpaces(word);
		wordsVector.push_back(word);
	}

	return wordsVector;
}

pair<Word, vector<string>> ParseLine(const string& str)
{
	string keyWord;
	string translationWord;
	pair<Word, vector<string>> elemDictionary;

	auto wordEnd = str.find(TRANSLATE);
	keyWord = str.substr(0, wordEnd);
	elemDictionary.first.keyWord = keyWord;

	auto translateStart = wordEnd + TRANSLATE.length();
	translationWord = str.substr(translateStart);
	elemDictionary.second = GetTranslationVector(translationWord);

	return elemDictionary;
}

void ReadDictionaryFromStream(Dictionary& dictionary, istream& input)
{
	string str;
	pair<Word, vector<string>> dictionaryElem;

	while (getline(input, str))
	{
		dictionaryElem = ParseLine(str);
		dictionary.dictionaryWords.emplace(dictionaryElem.first, dictionaryElem.second);
	}
}

void DictionaryInitialization(Dictionary& dictionary, std::string& fileName)
{
	ifstream input(fileName, ios::in);

	if (input.is_open())
	{
		ReadDictionaryFromStream(dictionary, input);
		std::cout << "Словарь проинициализирован" << std::endl;
	}
	else
	{
		std::cout << "Не удалось проинициализировать словарь!" << endl;
		//fileName.clear();
		//указанный файл не найден. Значит проверить корректность указанного
		//if (CheckFileName(fileName))
		//{
		//	cout << "correct file name" << endl;
		//}
		//else
		//{
		//	cout << "invalid file name" << endl;
		//}
	}
}

//bool CheckFileName(const std::string& nameFile)
//{
//	const std::regex regular("([\\w-]*[^\+\|\?\\\"><]+)\\.txt");
//	std::cmatch base_match;
//
//	if (std::regex_match(nameFile.c_str(), base_match, regular))
//	{
//		return true;
//	}
//
//	return false;
//	//return (std::regex_match(nameFile, base_match, regular));
//}