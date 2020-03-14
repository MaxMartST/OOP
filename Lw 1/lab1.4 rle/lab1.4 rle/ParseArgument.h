#pragma once

#include "pch.h"
#include <algorithm>
#include <iostream>
#include <optional>

const unsigned int NUMBER_ARGS = 4;

struct Args
{
	Mode mode;
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Mode> GetMode(const std::string& command);

std::optional<Args> ParseArgs(int argc, char* argv[]);