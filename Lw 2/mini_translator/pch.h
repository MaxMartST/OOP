#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include <vector>

const size_t YES = 121;
const size_t NO = 110;

enum class Status
{
	NEW_WORD,
	OLD_WORD
};

struct Dictionary
{
	std::map<std::string, std::vector<std::string>> dictionaryWords;
	Status statusDictionary = Status::OLD_WORD;
};