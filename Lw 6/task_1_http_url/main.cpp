#include "pch.h"
#include "CCommandHandler.h"
#include "CUrlParsingError.h"

using namespace std;

int main()
{
	CCommandHandler ch(cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (ch.HandleCommand())
		{
			break;
		}
	}

	return 0;
}