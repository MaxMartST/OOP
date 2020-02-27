#include "pch.h"
#include "main.h"

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParsArgs(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "Useg: lw1.1 <input.txt> <outfile.txt>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}

void CopyStreams(std::ifstream& input, std::ofstream& output)
{
	char ch;
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			break;
		}
	}
}

bool CopyFile(const std::string inputFileName, const std::string outputFileName)
{
	std::ifstream input;
	input.open(inputFileName);
	if (!input.is_open())
	{
		std::cout << "Fale to open '" << inputFileName << "' for reading" << std::endl;
		return false;
	}

	std::ofstream output;
	output.open(outputFileName);
	if (!output.is_open())
	{
		std::cout << "Fale to open '" << outputFileName << "' for writing" << std::endl;
		return false;
	}

	CopyStreams(input, output);

	if (input.bad())
	{
		std::cout << "Filed to read date from input file" << std::endl;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output file" << std::endl;
		return false;
	}
	return true;
}

int main(int argc, char *argv[])
{
	auto args = ParsArgs(argc, argv);

	if (!args)
	{
		return 1;
	}
	if (!CopyFile(args->inputFileName, args->outputFileName))
	{
		return 1;
	}
	
	return 0;
}