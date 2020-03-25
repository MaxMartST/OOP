#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>

std::optional<std::vector<double>> GetVectorFromStream(std::istream& inputStream);
void PrintSortVector(std::ostream& outputStream, const std::vector<double>& resultVector);
