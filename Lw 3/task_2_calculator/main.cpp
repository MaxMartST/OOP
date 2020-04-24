#include "pch.h"
#include "CCalculator.h"
#include "CCalculatorMenu.h"

#include <Windows.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	CCalculator calculator;
	CCalculatorMenu controlСalculator(calculator, cin, cout);

	while ((!cin.eof()) && (!cin.fail()))
	{
		cout << "> ";
		if (!controlСalculator.SetCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}

	return 0;
}