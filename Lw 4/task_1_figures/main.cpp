#include "pch.h"
#include "CCommandHandler.h"
#include "CErrorMessage.h"
#include "IShape.h"

using namespace std;

int main(int argc, char argv[])
{
	CCommandHandler ch(cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		try
		{
			ch.HandleCommand();
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
			return 1;
		}
		catch (const CErrorMessage& em)
		{
			cout << em.GetErrorMessage();
			return 1;
		}
	}

	ch.PrintShapeWithMinPerimetr();
	ch.PrintShapeWithMaxArea();

	return 0;
}
