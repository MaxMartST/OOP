#include "CUrlParsingError.h"
#include <string>

using namespace std;

CUrlParsingError::CUrlParsingError(string const& msg = "ERROR")
	: invalid_argument(msg)
{
}