#include "ParseArgument.h"

std::optional<Mode> GetMode(const std::string& command)
{
	if (command == COMMAND_PACK)
	{
		return Mode::PACK;
	}
	else if (command == COMMAND_UNPACK)
	{
		return Mode::UNPACK;
	}

	return std::nullopt;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != NUMBER_ARGS)
	{
		std::cout << "ERROR: Invalid name file! \nUse command: <input.txt>, <outfile.txt>" << std::endl;
		return std::nullopt;
	}
	
	std::string str = argv[1];
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return static_cast<char>(tolower(c)); });

	auto mode = GetMode(str);
	if (!mode)
	{
		std::cout << "ERROR: Invalid command! \nUse command: pack or unpack" << std::endl;
		return std::nullopt;
	}

	Args args;
	args.mode = *mode;
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];

	return args;
}