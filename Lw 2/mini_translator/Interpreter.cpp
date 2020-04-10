#include "Interpreter.h"
#include "InitializeDictionary.h"

void PrintRussianTranslation(const std::vector<std::string>& translation)
{
	for (size_t i = 0; i < translation.size(); i++)
	{
		std::cout << translation.at(i);
		if (i < translation.size() - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}

void PrintEnglishTranslation(const std::string& translation)
{
	std::cout << translation << std::endl;
}

void AddWordDictionary(const std::string& word, const std::string& translate, Dictionary& dictionary)
{
	Word keyWord;
	keyWord.keyWord = word;
	keyWord.statusWord = Status::NEW;

	dictionary.dictionaryWords.emplace(keyWord, GetTranslationVector(translate));
	dictionary.statusDictionary = Status::NEW;
}

void NotFoundWord(const std::string& word, Dictionary& dictionary)
{
	std::cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << std::endl;

	std::string translate;
	getline(std::cin, translate);

	if (translate == SKIP_WORD)
	{
		std::cout << "\nСлово \"" << word << "\" проигнорировано." << std::endl;
	}
	else
	{
		AddWordDictionary(word, translate, dictionary);
		std::cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translate << "\"." << std::endl;
	}
}

std::optional<std::vector<std::string>> GetRussianTranslation(const Dictionary& dictionary, const std::string& word)
{
	std::string translationWord;

	for (auto value : dictionary.dictionaryWords)
	{
		translationWord = value.first.keyWord;
		transform(translationWord.begin(), translationWord.end(), translationWord.begin(), tolower);

		if (translationWord == word)
		{
			return value.second;
		}
	}

	return std::nullopt;
}

std::optional<std::string> GetEnglishTranslation(const Dictionary& dictionary, const std::string& word)
{
	//setlocale(LC_ALL, "");
	std::string translationWord;

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

	return std::nullopt;
}

void Interpreter(Dictionary& dictionary)
{
	setlocale(LC_ALL, "");
	std::string requestWord, inputString;

	do
	{
		getline(std::cin, inputString);
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
			NotFoundWord(requestWord, dictionary);
		}

	} while (requestWord != CLOSE);

	std::cout << "Выход из переводчика" << std::endl;
}