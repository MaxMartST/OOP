#include "pch.h"
#include "LinkerBinaryFile.h"
#include "ParseArgument.h"

bool CorrectFileReading(std::istream& input)
{
	if (input.bad())
	{
		std::cout << "Filed to read date from input file" << std::endl;
		return false;
	}

	return true;
}

bool FlushStreamBuffer(std::ostream& output)
{
	if (!output.flush())
	{
		std::cout << "Failed to write data to output file" << std::endl;
		return false;
	}

	return true;
}

bool FlushChunk(RLEChunk& chunk, std::ostream& output)
{
	output.write((char*)&chunk, sizeof chunk);
	chunk.counter = 0;

	return true;
}

bool PackNextChar(RLEChunk& chunk, char ch, std::ostream& output)
{
	if (chunk.counter == 0)
	{
		chunk.currentChar = static_cast<uint8_t>(ch);
	}

	if ((chunk.currentChar == static_cast<uint8_t>(ch)) && (chunk.counter < std::numeric_limits<uint8_t>::max()))
	{
		chunk.counter++;
	}
	else
	{
		return FlushChunk(chunk, output);
	}

	return false;
}

bool Pack(std::istream& input, std::ostream& output)
{
	RLEChunk chunk;
	char ch;

	while (!input.eof())
	{
		input.read((char*)&ch, sizeof ch);

		if (PackNextChar(chunk, ch, output))
		{
			chunk.currentChar = static_cast<uint8_t>(ch);
		}

		if (input.eof() && (chunk.counter > 0))
		{
			return FlushChunk(chunk, output);
		}
	}

	return (FlushStreamBuffer(output) && CorrectFileReading(input)) ? true : false;
}

bool UnpackChunk(const RLEChunk& chunk, std::ostream& output)
{
	for (std::uint8_t i = 0; i < static_cast<uint8_t>(chunk.counter); i++)
	{
		if (!output.write((char*)&chunk.currentChar, sizeof chunk.currentChar)) 
		{
			std::cout << "Unpacking error" << std::endl;
			return false;
		}
	}

	return true;
}

bool ReadChunk(RLEChunk& chunk)
{
	if (chunk.counter == 0)
	{
		std::cout << "Zero character repetition" << std::endl;
		return false;
	}

	return true;
}

bool Unpack(std::istream& input, std::ostream& output)
{
	RLEChunk chunk;

	while (input.read((char*)&chunk, sizeof chunk))
	{
		if (!ReadChunk(chunk))
		{
			return false;
		}

		if (!UnpackChunk(chunk, output))
		{
			return false;
		}
	}

	return (FlushStreamBuffer(output) && CorrectFileReading(input)) ? true : false;
}

bool TransformFile(const std::string& inputFileName, const std::string& outputFileName, const std::function<bool(std::istream&, std::ostream&)> Transformer)
{
	std::ifstream input(inputFileName, std::ios::binary | std::ios::in);
	std::ofstream output(outputFileName, std::ios::binary | std::ios::out | std::ios::trunc);

	if (!input.is_open())
	{
		std::cout << "Faile to open '" << inputFileName << "' for reading" << std::endl;
		return false;
	}

	if (!output.is_open())
	{
		std::cout << "Faile to open '" << outputFileName << "' for writing" << std::endl;
		return false;
	}

	return Transformer(input, output);
}

bool EvenPackedFileLength(const std::string& fileName)
{
	try
	{
		uintmax_t size = fs::file_size(fileName);
		if (!((size % 2) == 0))
		{
			std::cout << "Odd packed file length" << std::endl;
			return false;
		}
		return true;
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
}

bool FileLArchiver(const Args& args)
{
	switch (args.mode)
	{
	case Mode::PACK:
		return TransformFile(args.inputFileName, args.outputFileName, Pack);
	case Mode::UNPACK:
		return EvenPackedFileLength(args.inputFileName) ? TransformFile(args.inputFileName, args.outputFileName, Unpack) : false;
	}

	return true;
}