#include <array>
#include <assert.h>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdio.h>
#include <string>

const unsigned int MATRIX_SIZE = 3;
using Matrix = std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>;

std::optional<std::string> ParseMatrixFileName(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Use the name of the input file" << std::endl;
		return std::nullopt;
	}
	return argv[1];
}

bool ReadStream(std::ifstream& input, Matrix& matrix)
{
	bool error = false;
	std::string line;
	int row = 0;
	int col;

	while (getline(input, line))
	{
		col = 0;
		if (row < MATRIX_SIZE)
		{
			std::stringstream stringIterator(line);

			while (!stringIterator.eof() && !error)
			{
				if (col == MATRIX_SIZE)
				{
					std::cout << "invalid number of matrix columns!" << std::endl;
					return false;
				}

				stringIterator >> matrix[row][col];
				col++;
			}

			if (col != MATRIX_SIZE)
			{
				error = !error;
				std::cout << "invalid number of matrix columns!" << std::endl;
				return false;
			}
		}
		row++;
	}
	if (line == "" && row != MATRIX_SIZE)
	{
		std::cout << "file is empty!" << std::endl;
		return false;
	}

	if (row != MATRIX_SIZE)
	{
		std::cout << "invalid number of matrix row!" << std::endl;
		return false;
	}

	return true;
}

std::optional<Matrix> GetMatrixFromFile(const std::string& fileName)
{
	std::ifstream input;
	input.open(fileName);

	if (!input.is_open())
	{
		std::cout << "Faile to open '" << fileName << "' for reading" << std::endl;
		return std::nullopt;
	}

	Matrix matrix;
	if (!ReadStream(input, matrix))
	{
		return std::nullopt;
	}

	return matrix;
}

double GetDeterminant(const Matrix& matrix)
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[1][0] * matrix[0][2] * matrix[2][1] + matrix[0][1] * matrix[1][2] * matrix[2][0]
		- matrix[2][0] * matrix[1][1] * matrix[0][2] - matrix[0][1] * matrix[1][0] * matrix[2][2] - matrix[0][0] * matrix[1][2] * matrix[2][1];
}

Matrix GetTransposeMatrix(const Matrix& matrix)
{


	Matrix newMatrix;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			newMatrix[j][i] = matrix[i][j];
		}
	}

	return newMatrix;
}

double GetAlgebraicComplement(const Matrix& matrix, int y, int x)
{
	double minorElements[4];
	int itemNumber = 0;

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if ((i != y) && (j != x))
			{
				minorElements[itemNumber++] = matrix[i][j];
			}
		}
	}
	return ((minorElements[0] * minorElements[3]) - (minorElements[1] * minorElements[2]));
}
Matrix GetAdjugateMatrix(const Matrix& matrix)
{
	Matrix newMatrix;
	double mark = 1;

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			newMatrix[i][j] = mark * GetAlgebraicComplement(matrix, i, j);
			mark = -mark;
		}
	}

	return newMatrix;
}

Matrix GetResultMatrix(const double& coefficient, Matrix& matrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			matrix[i][j] = matrix[i][j] * coefficient;
		}
	}

	return matrix;
}

std::optional<Matrix> InvertMatrix(const Matrix& matrix)
{
	double determinant = GetDeterminant(matrix);
	if (determinant == 0)
	{
		return std::nullopt;
	}

	double coefficient = 1 / determinant;
	Matrix transposeMatrix = GetTransposeMatrix(matrix);
	Matrix adjugateMatrix = GetAdjugateMatrix(transposeMatrix);

	return GetResultMatrix(coefficient, adjugateMatrix);
}

void PrintMatrix(const Matrix& matrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			std::cout << std::setprecision(3) << std::fixed << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseMatrixFileName(argc, argv);
	if (!args)
	{
		return 1;
	}

	if (auto inputMatrix = GetMatrixFromFile(*args))
	{
		if (auto resultMatrix = InvertMatrix(*inputMatrix))
		{
			PrintMatrix(*resultMatrix);
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