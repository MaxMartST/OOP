#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdio.h>
#include <string>
#include <vector>
#include <filesystem>

const std::string COMMAND_PACK = "pack";
const std::string COMMAND_UNPACK = "unpack";
const unsigned int NUMBER_ARGS = 4;
const unsigned int RANGE_LIMIT = 256;

namespace fs = std::filesystem;

struct Args
{
	std::string command;
	std::string inputFile;
	std::string outputFile;
};

struct ReadChar
{
	bool eof = false;
	uint8_t count = 0;
	char ch = 0;
	uint8_t last = 0;
};

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

void PrintCode(uint8_t& count, const uint8_t& ch, std::ofstream& output)
{
	output << unsigned(count) << ch;
}

void RleEncode(const uintmax_t& fileSize, std::ifstream& input, std::ofstream& output)
{
	ReadChar readChar;

	for (std::uintmax_t i = 0; i < fileSize; ++i)
	{
		if (i == fileSize - 1)
		{
			readChar.eof = true;
		}

		input.get(readChar.ch);

		if (readChar.count == 0)
		{
			readChar.last = static_cast<uint8_t>(readChar.ch);
		}

		if ((readChar.last == static_cast<uint8_t>(readChar.ch)) && (readChar.count < std::numeric_limits<uint8_t>::max()))
		{
			readChar.count++;
		}
		else
		{
			PrintCode(readChar.count, readChar.last, output);
			readChar.last = static_cast<uint8_t>(readChar.ch);
			readChar.count = 1;
		}

		if ((readChar.eof) && (readChar.count > 0))
		{
			PrintCode(readChar.count, readChar.last, output);
		}
	}

	/*while (input.get(ch))
	{
		if (static_cast<uint8_t>(ch) == last)
		{
			readChar.count++;
			while (input.get(ch) && readChar.count < RANGE_LIMIT)
			{
				if (static_cast<uint8_t>(ch) == last)
				{
					readChar.count++;
				}
				else
				{
					break;
				}
			}
			PrintCode(readChar.count, readChar.ch, output);
			last = 0;
		}
		if (last != 0 && static_cast<uint8_t>(ch) != last && readChar.count != RANGE_LIMIT)
		{
			PrintCode(readChar.count, readChar.ch, output);
		}
		readChar.ch = static_cast<uint8_t>(ch);
		last = static_cast<uint8_t>(ch);
		readChar.count = 1;
	}
	PrintCode(readChar.count, readChar.ch, output);*/
}

void RleDencode(const uintmax_t& fileSize, std::ifstream& input, std::ofstream& output)
{
	std::cout << "RleEncode" << std::endl;
}

uintmax_t GetFileSize(const std::string& fileName)
{
	try
	{
		return fs::file_size(fileName);
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
		return 0;
	}
}

bool IsFileSizeEven(const uintmax_t& number)
{
	return (number % 2 == 0);
}

bool BinaryFileCompression(const std::string& com, const std::string& inputFile, const std::string& outputFile)
{
	std::ifstream input;
	input.open(inputFile, std::ios::binary | std::ios::in);
	if (!input.is_open())
	{
		std::cout << "Fale to open '" << inputFile << "' for reading" << std::endl;
		return false;
	}

	std::ofstream output;
	output.open(outputFile, std::ios::binary);
	if (!output.is_open())
	{
		std::cout << "Fale to open '" << outputFile << "' for writing" << std::endl;
		return false;
	}

	auto fileSize = GetFileSize(inputFile);
	if (!IsFileSizeEven(fileSize))
	{
		std::cout << "Odd packed file length" << std::endl;
		return false;
	}

	if (com == COMMAND_PACK)
	{
		RleEncode(fileSize, input, output);
	}
	else if (com == COMMAND_UNPACK)
	{
		RleDencode(fileSize, input, output);
	}

	if (input.bad())
	{
		std::cout << "Filed to read date from input file" << std::endl;
		return false;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output file" << std::endl;
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParsArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	if (!BinaryFileCompression(args->command, args->inputFile, args->outputFile))
	{
		return 1;
	}

	return 0;
}