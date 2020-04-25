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
		controlСalculator.SetCommand();
	}

	return 0;
}