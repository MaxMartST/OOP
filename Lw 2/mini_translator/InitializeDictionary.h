#pragma once
#include "pch.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <utility>

const std::string TRANSLATE = ": ";

void RemoveSpaces(std::string& str);
std::vector<std::string> GetTranslationVector(const std::string& str);
std::pair<Word, std::vector<std::string>> ParseLine(const std::string& str);
void ReadDictionaryFromStream(Dictionary& dictionary, std::istream& input);
void DictionaryInitialization(Dictionary& dictionary);
bool ParseDictionaryFileName(int argc, char* argv[], std::string& fileName);