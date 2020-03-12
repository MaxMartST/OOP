#pragma once

#include <optional>
#include <iostream>
#include <algorithm>

const unsigned int NUMBER_ARGS = 4;

struct Args
{
	std::string command;
	std::string inputFile;
	std::string outputFile;
};

std::optional<Args> ParsArgs(int argc, char* argv[]);