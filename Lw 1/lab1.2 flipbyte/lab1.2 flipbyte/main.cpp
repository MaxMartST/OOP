#include <bitset>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputArg;
};

std::optional<Args> ParsArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Use one argument - a positive integer " << std::endl;
		return std::nullopt;
	}
	Args args;
	args.inputArg = argv[1];
	return args;
}

void CheckRange(int number)
{
	if (std::numeric_limits<uint8_t>::max() < number || number < std::numeric_limits<uint8_t>::min())
	{
		throw std::exception("Invalid number range. Valid range is from 0 to 255");
	}
}

bool CheckArgument(std::string arg)
{
	int temp;
	try
	{
		temp = stoi(arg);
		CheckRange(temp);
		return true;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Error: " << e.what() << ". Argument must be a number"<< std::endl;
		return false;
	}
	catch (const std::out_of_range& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return false;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return false;
	}
}

int FlipByte(const uint8_t arg)
{
	uint8_t number = arg;
	uint8_t result = 0;

	for (int i = 0; i < 8; ++i)
	{
		result |= (number & 1) << (7 - i);
		number >>= 1;
	}
	return static_cast<int>(result);
}

int main(int argc, char* argv[])
{
	auto args = ParsArgs(argc, argv);

	if (!args)
	{
		return 1;
	}
	if (!CheckArgument(args->inputArg))
	{
		return 1;
	}

	std::cout << FlipByte(static_cast<uint8_t>(stoi(args->inputArg))) << std::endl;

	return 0;
}