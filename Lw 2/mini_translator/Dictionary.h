#pragma once
#include <map>
#include <string>
#include <vector>

enum class Status
{
	NEW,
	OLD
};

struct Word
{
	std::string keyWord;
	Status statusWord = Status::OLD;

	bool operator<(const Word& word1) const
	{
		return this->keyWord < word1.keyWord;
	}
};

struct Dictionary
{
	Dictionary() = default;

	//std::string dictionaryFileName;
	std::map<Word, std::vector<std::string>> dictionaryWords;
	Status statusDictionary = Status::OLD;
};