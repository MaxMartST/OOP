#pragma once
#include "pch.h"
#include "Dictionary.h"

bool FlushStreamBuffer(std::ostream& output);
void SendPairStream(const std::string& word, const std::vector<std::string>& transfer, std::ostream& file);
bool IterateOverDictionary(const Dictionary& dictionary, std::ostream& file);
void SaveDictionaryExistingFile(const Dictionary& dictionary);
bool WriteToSpecifiedFile(const Dictionary& dictionary, std::ostream& file);
void SaveDictionaryToSpecifiedFile(const Dictionary& dictionary);
void SaveDictionary(const Dictionary& dictionary);