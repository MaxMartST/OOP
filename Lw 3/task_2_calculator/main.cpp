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
	Status statusMenu;

	while ((!cin.eof()) && (!cin.fail()))
	{
		cout << "> ";
		statusMenu = controlСalculator.SetCommand();
		
		if (Status::ERORR == statusMenu)
		{
			cout << "Unknown command!" << endl;
		}

		if (Status::EXIT == statusMenu)
		{
			cout << "Exit!" << endl;
			break;
		}
	}

	return 0;
}