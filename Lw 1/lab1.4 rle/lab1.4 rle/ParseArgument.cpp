#include "ParseArgument.h"
#include "pch.h"

std::optional<Args> ParsArgs(int argc, char* argv[])
{
	if (argc != NUMBER_ARGS)
	{
		std::cout << "Use: command, <input.txt>, <outfile.txt>" << std::endl;
		return std::nullopt;
	}

	Args args;
	std::string str = argv[1];
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return static_cast<char>(tolower(c)); });

	if (str == COMMAND_PACK)
	{
		args.command = COMMAND_PACK;
	}
	else if (str == COMMAND_UNPACK)
	{
		args.command = COMMAND_UNPACK;
	}
	else
	{
		std::cout << "Use command: pack or unpack" << std::endl;
		return std::nullopt;
	}

	args.inputFile = argv[2];
	args.outputFile = argv[3];

	return args;
}