#include <iostream>
#include "calc.h"

using namespace std;

int main()
{
	try
	{
		Calc calc;
		calc.run();
	}
	catch (const std::exception&)
	{
		cout << "we can't solve this yet, check the condition you wrote." << endl;
	}
}

