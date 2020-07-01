#include "ArchiverBinaryFile.h"
#include "ParseArgument.h"

using namespace std;
using namespace fs;

bool CorrectFileReading(istream& input)
{
	if (input.bad())
	{
		cout << "ERROR: Filed to read date from input file!" << endl;
		return false;
	}

	return true;
}

bool FlushStreamBuffer(ostream& output)
{
	if (!output.flush())
	{
		cout << "ERROR: Failed to write data to output file!" << endl;
		return false;
	}

	return true;
}

bool FlushChunk(RLEChunk& chunk, char ch, ostream& output)// записать упаковку в файл из потока output
{
	if (!output.write((char*)&chunk, sizeof chunk))
	{
		return false;
	}

	chunk.currentChar = static_cast<uint8_t>(ch);
	chunk.counter = 1;

	return true;
}

/*void FlushChunk(RLEChunk& chunk, ostream& output)
{
	output.write((char*)&chunk, sizeof chunk);
	chunk.counter = 0;
}*/

//bool PackNextChar(RLEChunk& chunk, char ch, ostream& output)
//{
//	if (chunk.counter == 0)
//	{
//		chunk.currentChar = static_cast<uint8_t>(ch);
//	}
//
//	if ((chunk.currentChar == static_cast<uint8_t>(ch)) && (chunk.counter < numeric_limits<uint8_t>::max()))
//	{
//		chunk.counter++;
//	}
//	else
//	{
//		return FlushChunk(chunk, output);
//	}
//
//	return false;
//}

bool Pack(istream& input, ostream& output)
{
	RLEChunk chunk;
	char ch;

	while (input.get(ch))
	{
		if (chunk.counter == 0 || chunk.currentChar == static_cast<uint8_t>(ch))
		{
			chunk.currentChar = static_cast<uint8_t>(ch);
			++chunk.counter;
		}
		else
		{
			FlushChunk(chunk, ch, output);
		}

		while (input.get(ch))
		{
			if (!(chunk.counter < std::numeric_limits<uint8_t>::max()))
			{
				break;		
			}

			if (chunk.currentChar == static_cast<uint8_t>(ch))
			{
				++chunk.counter;
				continue;
			}

			break;
		}

		FlushChunk(chunk, ch, output);

		if (input.eof())
		{
			chunk.counter = 0;
		}
	}

	//while (input.get(ch))
	//{
	//	if (PackNextChar(chunk, ch, output))
	//	{
	//		chunk.currentChar = static_cast<uint8_t>(ch);
	//		chunk.counter++;
	//	}
	//}

	if (input.eof() && (chunk.counter == 1))
	{
		return FlushChunk(chunk, ch, output);
	}

	return (FlushStreamBuffer(output) && CorrectFileReading(input));
}

bool UnpackChunk(const RLEChunk& chunk, ostream& output)
{
	for (uint8_t i = 0; i < static_cast<uint8_t>(chunk.counter); i++)
	{
		if (!output.write((char*)&chunk.currentChar, sizeof chunk.currentChar))
		{
			cout << "Unpacking error" << endl;
			return false;
		}
	}

	return true;
}

bool ReadChunk(RLEChunk& chunk)
{
	if (chunk.counter == 0)
	{
		cout << "Zero character repetition" << endl;
		return false;
	}

	return true;
}

bool Unpack(istream& input, ostream& output)
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

	return (FlushStreamBuffer(output) && CorrectFileReading(input));
}

bool TransformFile(const string& inputFileName, const string& outputFileName, const function<bool(istream&, ostream&)> Transformer)
{
	ifstream input(inputFileName, ios::binary | ios::in);
	ofstream output(outputFileName, ios::binary | ios::out | ios::trunc);

	if (!input.is_open())
	{
		cout << "ERROR: Faile to open '" << inputFileName << "' for reading!" << endl;
		return false;
	}

	if (!output.is_open())
	{
		cout << "ERROR: Faile to open '" << outputFileName << "' for writing!" << endl;
		return false;
	}

	return Transformer(input, output);
}

bool EvenPackedFileLength(const string& fileName)
{
	try
	{
		uintmax_t size = file_size(fileName);

		if (!((size % 2) == 0))
		{
			cout << "ERROR: Odd packed file length!" << endl;
			return false;
		}

		return true;
	}
	catch (const filesystem_error& e)
	{
		cout << e.what() << endl;
		return false;
	}
}

bool FileArchiver(const Args& args)
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