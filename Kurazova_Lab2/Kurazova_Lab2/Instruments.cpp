#include "Instruments.h"
#include <iostream>
#include <string>
using namespace std;

std::string GetName()
{
	string value;
	while (true)
	{
		getline(cin, value);
		if (!value.empty())
		{
			return value;
		}
		else
		{
			std::cin.ignore(1000, '\n');
			std::cout << "Wrong input! Please, input correct string:" << std::endl;
		}
	}
}
