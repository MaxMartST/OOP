#pragma once
#include "ParseArgument.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <stdio.h>
#include <functional>

namespace fs = std::filesystem;
typedef std::function<bool(std::istream&, std::ostream&)> Transformer;

struct RLEChunk
{
	uint8_t counter = 0;
	uint8_t currentChar = 0;
};

bool Pack(std::istream& input, std::ostream& output);
//bool UnpackChunk(std::istream& input, std::ostream& output);
bool Unpack(std::istream& input, std::ostream& output);
bool FileArchiver(const Args& args);
bool ChackSizeFile(std::istream& input);