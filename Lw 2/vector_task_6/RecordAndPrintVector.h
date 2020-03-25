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

bool ReadingDataFromStreamInVector(std::istream& inputStream, std::vector<double>& vectorNumers);
void PrintSortVector(std::vector<double>& outVector);
