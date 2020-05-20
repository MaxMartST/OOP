#include "pch.h"
#include "CCommandHandler.h"
#include "CUrlParsingError.h"

using namespace std;

int main()
{
	CCommandHandler ch(cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		try
		{
			cout << "> ";
			ch.HandleCommand();
		}
		catch (invalid_argument const& ia)
		{
			cout << ia.what() << endl;
		}
	}

	//ch.PrintUrlHistory();

	return 0;
}