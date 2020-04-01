#pragma once
#include "pch.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <utility>
#include <conio.h>

const std::string CLOSE = "...";
const std::string SKIP_WORD = " ";

void Interpreter(Dictionary& dictionary);