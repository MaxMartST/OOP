#include "Interpreter.h"
#include "InitializeDictionary.h"
#include "pch.h"

using namespace std;

void PrintRussianTranslation(const vector<string>& translation)
{
	for (size_t i = 0; i < translation.size(); i++)
	{
		cout << translation.at(i);
		if (i < translation.size() - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void PrintEnglishTranslation(const string& translation)
{
	cout << translation << endl;
}

void AddWordDictionary(const string& word, const string& translate, Dictionary& dictionary)
{
	Word keyWord;
	keyWord.keyWord = word;
	keyWord.statusWord = Status::NEW;

	dictionary.dictionaryWords.emplace(keyWord, GetTranslationVector(translate));
	dictionary.statusDictionary = Status::NEW;
}

void NotFoundWord(const string& word, Dictionary& dictionary)
{
	cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;

	std::cout << ">";
	string translationWord;
	getline(cin, translationWord);

	if (translationWord == SKIP_WORD)
	{
		cout << "\nСлово \"" << word << "\" проигнорировано." << endl;
	}
	else
	{
		AddWordDictionary(word, translationWord, dictionary);
		cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translationWord << "\"." << endl;
	}
}

optional<vector<string>> GetRussianTranslation(const Dictionary& dictionary, const string& word)
{
	string translationWord;

	for (auto value : dictionary.dictionaryWords)
	{
		translationWord = value.first.keyWord;
		transform(translationWord.begin(), translationWord.end(), translationWord.begin(), tolower);

		if (translationWord == word)
		{
			return value.second;
		}
	}

	return nullopt;
}

optional<string> GetEnglishTranslation(const Dictionary& dictionary, const string& word)
{
	//setlocale(LC_ALL, "");
	string translationWord;

	for (auto value : dictionary.dictionaryWords)
	{
		for (auto translation : value.second)
		{
			translationWord = translation;
			transform(translationWord.begin(), translationWord.end(), translationWord.begin(), tolower);

			if (translationWord == word)
			{
				return value.first.keyWord;
			}
		}
	}

	return nullopt;
}

void Interpreter(Dictionary& dictionary)
{
	string requestWord, inputString;

	do
	{
		std::cout << ">";
		getline(cin, inputString);
		requestWord = inputString;
		transform(requestWord.begin(), requestWord.end(), requestWord.begin(), tolower);

		if (auto translation = GetRussianTranslation(dictionary, requestWord))
		{
			PrintRussianTranslation(*translation);
			continue;
		}

		if (auto translation = GetEnglishTranslation(dictionary, requestWord))
		{
			PrintEnglishTranslation(*translation);
			continue;
		}

		if (requestWord != CLOSE)
		{
			NotFoundWord(inputString, dictionary);
		}

	} while (requestWord != CLOSE);

	cout << "Выход из переводчика" << endl;
}