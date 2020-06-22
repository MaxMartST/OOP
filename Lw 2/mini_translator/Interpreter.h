#pragma once
#include "Dictionary.h"
#include <optional>

const std::string CLOSE = "...";
const std::string SKIP_WORD;

void PrintRussianTranslation(const std::vector<std::string>& translation);
void PrintEnglishTranslation(const std::string& translation);
void AddWordDictionary(const std::string& word, const std::string& translate, Dictionary& dictionary);
void NotFoundWord(const std::string& word, Dictionary& dictionary);
std::optional<std::vector<std::string>> GetRussianTranslation(const Dictionary& dictionary, const std::string& word);
std::optional<std::string> GetEnglishTranslation(const Dictionary& dictionary, const std::string& word);
void Interpreter(Dictionary& dictionary);