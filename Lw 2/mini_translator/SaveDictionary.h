#pragma once
#include "Dictionary.h"
#include <iostream>

bool FlushStreamBuffer(std::ostream& output);
void SendPairStream(const std::string& word, const std::vector<std::string>& transfer, std::ostream& file);
bool IterateOverDictionary(const Dictionary& dictionary, std::ostream& file);
void SaveDictionaryExistingFile(const Dictionary& dictionary, const std::string fileName);
bool WriteToSpecifiedFile(const Dictionary& dictionary, std::ostream& file);
void SaveDictionaryToSpecifiedFile(const Dictionary& dictionary);
void SaveDictionary(const Dictionary& dictionary, std::string fileName);