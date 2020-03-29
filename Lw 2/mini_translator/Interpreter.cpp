
#include "Interpreter.h"
#include "InitializeDictionary.h"

void PrintRussianTranslation(const std::vector<std::string>& translation)
{
	std::cout << "Translation: ";
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
	std::cout << "Translation: ";
	std::cout << translation << std::endl;
}

void AddWordDictionary(const std::string& word, const std::string& translate, Dictionary& dictionary)
{
	dictionary.dictionaryWords.emplace(word, GetTranslationVector(translate));
	dictionary.statusDictionary = Status::NEW_WORD;
	std::cout << "Word \"" << word << "\" saved as \"" << translate << "\"" << std::endl;
}

void NotFoundWord(const std::string& word, Dictionary& dictionary)
{
	std::cout << "Failed to find this word: " << word << std::endl;
	std::cout << "Want to add it to your dictionary? Y/N" << std::endl;

	int key;
	do
	{
		key = _getch();
		if (key == YES)
		{
			std::string translate;
			std::cout << "Translate: ";
			getline(std::cin, translate);
			AddWordDictionary(word, translate, dictionary);
			break;
		}
		
		if (key != YES && key != NO)
		{
			std::cout << "\nWrong command! Try again" << std::endl;
		}

	} while (key != NO);
}

std::optional<std::vector<std::string>> GetRussianTranslation(const Dictionary& dictionary, const std::string& word)
{
	if (auto it = dictionary.dictionaryWords.find(word); it != dictionary.dictionaryWords.end())
	{
		return it->second;
	}

	return std::nullopt;
}

std::optional<std::string> GetEnglishTranslation(const Dictionary& dictionary, const std::string& word)
{
	for (auto item : dictionary.dictionaryWords)
	{
		for (auto translation : item.second)
		{
			if (translation == word)
			{
				return item.first;
			}
		}
	}

	return std::nullopt;
}

void Interpreter(Dictionary& dictionary)
{
	std::string requestWord;

	do
	{
		std::cout << "Find a translation for a word: ";
		getline(std::cin, requestWord);
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

	std::cout << "Exit the translator" << std::endl;
}