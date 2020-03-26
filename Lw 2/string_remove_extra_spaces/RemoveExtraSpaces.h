#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

std::string RemoveExtraSpaces(std::string const& str);
void RemoveExtraSpacesFromStream(std::istream& input, std::ostream& output);