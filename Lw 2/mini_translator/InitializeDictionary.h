#pragma once
#include "Dictionary.h"
#include <string>
#include <vector>

const std::string TRANSLATE = ": ";

void RemoveSpaces(std::string& str);
std::vector<std::string> GetTranslationVector(const std::string& str);
std::pair<Word, std::vector<std::string>> ParseLine(const std::string& str);
void ReadDictionaryFromStream(Dictionary& dictionary, std::istream& input);
void DictionaryInitialization(Dictionary& dictionary);
bool ParseDictionaryFileName(int argc, char* argv[], std::string& fileName);
bool CheckFileName(const std::string& nameFile);