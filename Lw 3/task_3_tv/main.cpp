#include "pch.h"
#include "CCommandTerminal.h"
#include "CTVSet.h"

using namespace std;

int main()
{
	CTVSet tv;
	CCommandTerminal commandTerminal(tv, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!commandTerminal.SetCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	return 0;
}
