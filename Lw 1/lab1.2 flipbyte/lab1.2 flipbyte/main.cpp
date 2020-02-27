#include <bitset>
#include <iostream>
#include <optional>
#include <string>

struct Content
{
	std::string inputString;
	int number;
};

void CheckRange(int number)
{
	if (std::numeric_limits<uint8_t>::max() < number || number < std::numeric_limits<uint8_t>::min())
	{
		throw std::out_of_range("Invalid number range. Valid range is from 0 to 255");
	}
}

std::optional<Content> ParsArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Use one argument - a positive integer " << std::endl;
		return std::nullopt;
	}
	Content content;
	content.inputString = argv[1];//сделать отдельную переменную 

	try
	{
		content.number = stoi(content.inputString);
		CheckRange(content.number);
		return content;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Error: " << e.what() << ". Argument must be a number" << std::endl;
		return std::nullopt;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return std::nullopt;
	}
}

uint8_t FlipByte(const uint8_t inputNumber)
{
	uint8_t number = inputNumber;
	uint8_t result = 0;

	for (int i = 0; i < 8; ++i)
	{
		result |= (number & 1) << (7 - i);
		number >>= 1;
	}
	return result;
}

int main(int argc, char* argv[])
{
	auto args = ParsArgs(argc, argv);

	if (!args)
	{
		return 1;
	}
	std::cout << static_cast<int>(FlipByte(static_cast<uint8_t>(args->number))) << std::endl;

	return 0;
}