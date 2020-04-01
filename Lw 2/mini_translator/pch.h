#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include <vector>

const size_t YES = 121;
const size_t NO = 110;

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
	Dictionary(std::string& str)
	{
		dictionaryFileName = str;
	}

	std::string dictionaryFileName;
	std::map<Word, std::vector<std::string>> dictionaryWords;
	Status statusDictionary = Status::OLD;
};