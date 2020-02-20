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

int main(int argc, char *argv[])
{
	auto args = ParsArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	std::ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Fale to open '" << args->inputFileName << "' for reading" << std::endl;
		return 1;
	}

	std::ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Fale to open '" << args->outputFileName << "' for writing" << std::endl;
		return 1;
	}

	CopyStreams(input, output);

	if (input.bad())
	{
		std::cout << "Filed to read date from input file" << std::endl;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output file" << std::endl;
		return 1;
	}

	return 0;
}

void CopyStreams(std::ifstream &input, std::ofstream &output)
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
