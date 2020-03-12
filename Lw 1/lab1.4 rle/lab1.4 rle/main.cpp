#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdio.h>
#include <string>
#include <cstdint>
#include <vector>
#include <filesystem>

const std::string COMMAND_PACK = "pack";
const std::string COMMAND_UNPACK = "unpack";
const unsigned int NUMBER_ARGS = 4;

namespace fs = std::filesystem;

struct Args
{
	std::string command;
	std::string inputFile;
	std::string outputFile;
};

struct ReadChar
{
	uint8_t count = 0;
	uint8_t ch = 0;
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

/*void PrintCode(uint8_t& count, const uint8_t& ch, std::ofstream& output)
{
	//output << unsigned(count) << ch;
}*/

void RleEncode(const uintmax_t& fileSize, std::fstream& input, std::ofstream& output)
{
	ReadChar readChar;
	bool eof = false;
	char ch = 0;

	for (std::uintmax_t i = 0; i < fileSize; ++i)
	{
		if (i == fileSize - 1)
		{
			eof = true;
		}

		input.get(ch);

		if (readChar.count == 0)
		{
			readChar.ch = static_cast<uint8_t>(ch);
		}

		if ((readChar.ch == static_cast<uint8_t>(ch)) && (readChar.count < std::numeric_limits<uint8_t>::max()))
		{
			readChar.count++;
		}
		else
		{
			//PrintCode(readChar.count, readChar.ch, output);
			output.write((char*)&readChar, sizeof readChar);
			readChar.ch = static_cast<uint8_t>(ch);
			readChar.count = 1;
		}

		if (eof && (readChar.count > 0))
		{
			//PrintCode(readChar.count, readChar.ch, output);
			output.write((char*)&readChar, sizeof readChar);
		}
	}
}

void RleDencode(const uintmax_t& fileSize, std::fstream& input, std::ofstream& output)
{
	//std::cout << "RleDencode" << std::endl;
	//std::cout << "File Size: " << fileSize << std::endl;

	char count;
	uint8_t last;
	char ch;

	input.get(count);
	input.get(ch);
	//std::cout << ch;

	int num = static_cast<int>(count) - '0';

	for (int i = 0; i < num; i++)
	{

		std::cout << ch;
	}

	/*for (std::uintmax_t i = 0; i < fileSize; i++)
	{
		input.get(ch);
		count = static_cast<uint8_t>(ch);
		if (count == 0)
		{
			std::cout << "Invalid situation: zero repetition of a character" << std::endl;
			break;
		}

		std::cout << count;

		//input.get(ch);
		//last = static_cast<uint8_t>(ch);
		//for (std::uint8_t i = 0; i < count; i++)
		//{
		//	//output << unsigned(last);
		//	std::cout << ch;
		//}
	}*/

}

uintmax_t GetFileSize(const std::string& fileName)
{
	try
	{
		return fs::file_size(fileName);
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << std::endl;
		return 0;
	}
}

bool BinaryFileCompression(const std::string& com, const std::string& inputFile, const std::string& outputFile)
{
	std::fstream input;
	input.open(inputFile, std::ios::binary | std::ios::in);
	if (!input.is_open())
	{
		std::cout << "Fale to open '" << inputFile << "' for reading" << std::endl;
		return false;
	}

	std::ofstream output;
	output.open(outputFile, std::ios::binary | std::ios::out | std::ios::trunc);
	if (!output.is_open())
	{
		std::cout << "Fale to open '" << outputFile << "' for writing" << std::endl;
		return false;
	}

	auto fileSize = GetFileSize(inputFile);
	if (!(fileSize % 2) == 0)
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