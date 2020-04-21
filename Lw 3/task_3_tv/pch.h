#pragma once

#include "targetver.h"
#include <boost/bimap.hpp>

#include <stdio.h>
#include <tchar.h>

#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

typedef boost::bimap<int, std::string> ChannelStructure;
typedef ChannelStructure::value_type ChannelAndName;