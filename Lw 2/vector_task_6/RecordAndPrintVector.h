#pragma once
#include <iostream>
#include <iterator>
#include <optional>
#include <vector>

std::optional<std::vector<double>> InitiVector(std::istream& inputStream);
void PrintVector(const std::vector<double> & outVector);
int Add(int x, int y);
