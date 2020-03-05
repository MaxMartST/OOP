#include <array>
#include <assert.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdio.h>
#include <string>
#include <iomanip>

const unsigned int MATRIX_SIZE = 3;
typedef double Matrix[MATRIX_SIZE][MATRIX_SIZE];

std::optional<std::string> ParsArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Use the name of the input file" << std::endl;
		return std::nullopt;
	}
	return argv[1];
}

void ReadStream(std::ifstream& input, double inMatrix[][MATRIX_SIZE])
{
	bool Error = false;
	std::string line;
	int row = 0;
	int col;

	while (getline(input, line))
	{
		col = 0;
		if (row < MATRIX_SIZE)
		{
			std::stringstream stringIterator(line);

			while (!stringIterator.eof() && !Error)
			{
				if (col == MATRIX_SIZE)
				{
					throw "invalid number of matrix columns!";
				}

				if (!(stringIterator >> inMatrix[row][col]))
				{
					Error = !Error;
				}
				col++;
			}

			if (col != MATRIX_SIZE)
			{
				Error = !Error;
				throw "invalid number of matrix columns!";
			}
		}
		row++;
	}
	if (line == "")
	{
		throw "file is empty!";
	}

	if (row != MATRIX_SIZE)
	{
		throw "invalid number of matrix row!";
	}
}

std::optional<Matrix*> GetMatrixFromFile(const std::string& fileName)
{
	std::ifstream input;
	input.open(fileName);

	if (!input.is_open())
	{
		std::cout << "Faile to open '" << fileName << "' for reading" << std::endl;
		return std::nullopt;
	}
	static Matrix matrix;

	try
	{
		ReadStream(input, matrix);
	}
	catch (const char* e)
	{
		std::cout << "Error: " << e << std::endl;
		return std::nullopt;
	}

	return &matrix;
}

double GetDeterminant(const double inMatrix[][MATRIX_SIZE])
{
	return inMatrix[0][0] * inMatrix[1][1] * inMatrix[2][2] + inMatrix[1][0] * inMatrix[0][2] * inMatrix[2][1] + inMatrix[0][1] * inMatrix[1][2] * inMatrix[2][0]
		- inMatrix[2][0] * inMatrix[1][1] * inMatrix[0][2] - inMatrix[0][1] * inMatrix[1][0] * inMatrix[2][2] - inMatrix[0][0] * inMatrix[1][2] * inMatrix[2][1];
}

void TransposeMatrix(double inMatrix[][MATRIX_SIZE])
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = i; j < MATRIX_SIZE; j++)
		{
			std::swap(inMatrix[i][j], inMatrix[j][i]);
		}
	}
}

double GetAlgebraicComplement(const double inMatrix[][MATRIX_SIZE], int y, int x)
{
	double minorElements[4];
	int itemNumber = 0;

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if ((i != y) && (j != x))
			{
				minorElements[itemNumber++] = inMatrix[i][j];
			}
		}
	}
	return ((minorElements[0] * minorElements[3]) - (minorElements[1] * minorElements[2]));
}

Matrix* GetAdjugateMatrix(const double inMatrix[][MATRIX_SIZE])
{
	static Matrix matrix;

	double mark = 1;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			matrix[i][j] = mark * GetAlgebraicComplement(inMatrix, i, j);
			mark = -mark;
		}
	}

	return &matrix;
}

std::optional<Matrix*> InvertMatrix(double inMatrix[][MATRIX_SIZE])
{
	double determinant = GetDeterminant(inMatrix);
	if (determinant == 0)
	{
		return std::nullopt;
	}
	TransposeMatrix(inMatrix);
	Matrix* complements = GetAdjugateMatrix(inMatrix);

	double number = 1 / determinant;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			(*complements)[i][j] = (*complements)[i][j] * number;
		}
	}

	return complements;
}

void PrintMatrix(const double inMatrix[][MATRIX_SIZE])
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			std::cout << std::setprecision(3) << std::fixed << inMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParsArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	if (auto inputMatrix = GetMatrixFromFile(*args))
	{
		if (auto resultMatrix = InvertMatrix(**inputMatrix))
		{
			PrintMatrix(**resultMatrix);
			return 0;
		}
		else
		{
			std::cout << "Invalid matrix. Determinant is 0!" << std::endl;
			return 1;
		}
	}
	else
	{
		return 1;
	}
}