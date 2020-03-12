#include "pch.h"
#include "LinkerBinaryFile.h"

bool FileSizeCheck(const uintmax_t& fileSize)
{
	return ((fileSize % 2) == 0) ? true : false;
}

void RleEncode(const uintmax_t& fileSize, std::fstream& input, std::ofstream& output)
{
	ReadChar readChar;
	bool eof = false;
	char ch;

	for (std::uintmax_t i = 0; i < fileSize; ++i)
	{
		if (i == fileSize - 1)
		{
			eof = true;
		}

		input.read((char*)&ch, sizeof ch);

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
			output.write((char*)&readChar, sizeof readChar);
			readChar.ch = static_cast<uint8_t>(ch);
			readChar.count = 1;
		}

		if (eof && (readChar.count > 0))
		{
			output.write((char*)&readChar, sizeof readChar);
		}
	}
}

bool CheckTheCountOfRepetitions(const uint8_t& count)
{
	if (count == 0)
	{
		std::cout << "Zero character repetition" << std::endl;
		return false;
	}

	return true;
}

void RleDecode(const uintmax_t& fileSize, std::fstream& input, std::ofstream& output)
{
	if (FileSizeCheck(fileSize))
	{
		ReadChar readChar;

		for (std::uintmax_t a = 0; a < fileSize / 2; a++)
		{
			input.read((char*)&readChar, sizeof readChar);

			if (!CheckTheCountOfRepetitions(readChar.count))
			{
				break;
			}

			for (std::uint8_t b = 0; b < readChar.count; b++)
			{
				output.write((char*)&readChar.ch, sizeof readChar.ch);
			}
		}
	}
	else
	{
		std::cout << "Odd packed file length" << std::endl;
	}
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

void RleBinaryFiles(const uintmax_t& fileSize, const std::string& com, std::fstream& input, std::ofstream& output)
{
	if (com == COMMAND_PACK)
	{
		RleEncode(fileSize, input, output);
	}
	else if (com == COMMAND_UNPACK)
	{
		RleDecode(fileSize, input, output);
	}
}

bool FileLinker(const std::string& com, const std::string& inputFile, const std::string& outputFile)
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

	RleBinaryFiles(fileSize, com, input, output);

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