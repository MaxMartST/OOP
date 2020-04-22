#include "pch.h"
#include "CRemoteControl.h"
#include "CTVSet.h"

#include <Windows.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	CTVSet tv;
	CRemoteControl remoteControl(tv, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!remoteControl.SetCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	return 0;
}

//использую GitHub Desktop
