#include "InitializeDictionary.h"

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

void DictionaryInitialization(Dictionary& dictionary)
{
	ifstream input(dictionary.dictionaryFileName, ios::in);
	if (!input.is_open())
	{
		cout << "Failed to open file: " << dictionary.dictionaryFileName << endl;
	}

	ReadDictionaryFromStream(dictionary, input);
}