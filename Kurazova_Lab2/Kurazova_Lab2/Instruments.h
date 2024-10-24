#pragma once
#include <iostream>
#include <string>

template <typename N>
N GetNumber(N left_border, N right_border)
{
	N x;
	while ((std::cin >> x).fail() || (std::cin.peek() != '\n') || (N > left_border) || (N > right_border))
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Wrong input! Please, input correct number:" << std::endl;
	}
	std::cerr << x << std::endl;
	return x;
}


bool GetBool(bool& parameter) 
{
	while ((std::cin >> parameter).fail() || (std::cin.peek() != '\n') || ((parameter != 1) && (parameter != 0)))
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Wrong input! Please, input bool (1 or 0):" << std::endl;
	}
}