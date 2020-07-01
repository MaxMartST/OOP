#pragma once
#include <string>
#include <algorithm>
#include <iostream>
#include <optional>

const std::string COMMAND_PACK = "pack";
const std::string COMMAND_UNPACK = "unpack";

enum class Mode
{
	PACK,
	UNPACK
};

const unsigned int NUMBER_ARGS = 4;

struct Args
{
	Mode mode;
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Mode> GetMode(const std::string& command);
std::optional<Args> ParseArgs(int argc, char* argv[]);