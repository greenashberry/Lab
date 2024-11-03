#pragma once
#include <iostream>
#include <string>
#include <limits>

template <typename N>
N GetNumber(const N left_border = 0, const N right_border = std::numeric_limits<N>::max())
{
	N x;
	while (((std::cin >> x).fail()) || (std::cin.peek() != '\n') || (x < left_border) || (x > right_border))
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Wrong input! Please, input correct number:" << std::endl;
	}
	std::cerr << x << std::endl;
	return x;
}

std::string GetName();

