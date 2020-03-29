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
std::pair<std::string, std::vector<std::string>> ParseLine(const std::string& str);
Dictionary GetDictionary(std::istream& input);
Dictionary GetDictionaryFromInputFile(const std::string& file);