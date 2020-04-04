#pragma once
#include <iterator>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

std::string RemoveExtraSpaces(std::string const& str);
void RemoveExtraSpacesFromStream(std::istream& input, std::ostream& output);