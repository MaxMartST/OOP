#include "pch.h"
#include "CCommandHandler.h"
#include "IShape.h"

using namespace std;

int main(int argc, char argv[])
{
	CCommandHandler ch(cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!ch.HandleCommand())
		{
			return 1;
		}
	}

	ch.PrintShapeWithMinPerimetr();
	ch.PrintShapeWithMaxArea();
	ch.DrawShapes();

	return 0;
}
