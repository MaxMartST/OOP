#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <stdio.h>

namespace fs = std::filesystem;

struct ReadChar
{
	uint8_t count = 0;
	uint8_t ch = 0;
};

void RleEncode(const uintmax_t& fileSize, std::fstream& input, std::ofstream& output);

bool CheckTheCountOfRepetitions(const uint8_t& count);

void RleDecode(const uintmax_t& fileSize, std::fstream& input, std::ofstream& output);

uintmax_t GetFileSize(const std::string& fileName);

void RleBinaryFiles(const uintmax_t& fileSize, const std::string& com, std::fstream& input, std::ofstream& output);

bool FileSizeCheck(const uintmax_t& fileSize);

bool FileLinker(const std::string& com, const std::string& inputFile, const std::string& outputFile);