﻿#include <bitset>
#include <iostream>
#include <optional>
#include <string>

int CheckRange(int number)
{
	if (std::numeric_limits<uint8_t>::max() < number || number < std::numeric_limits<uint8_t>::min())
	{
		throw std::out_of_range("Invalid number range. Valid range is from 0 to 255");
	}
	return number;
}

std::optional<int> ParsArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Use one argument - a positive integer " << std::endl;
		return std::nullopt;
	}
	int number;

	try
	{
		number = CheckRange(std::stoi(argv[1]));
		return number;
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
	std::cout << static_cast<int>(FlipByte(static_cast<uint8_t>(*args))) << std::endl;

	return 0;
}