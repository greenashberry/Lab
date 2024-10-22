#pragma once
#include <string>
#include <iostream>

class Compression_Station
{
	std::string name;
	int number_of_workshops;
	int effectiveness;
public:
	int number_of_active_workshops;

	Compression_Station();

	void change_number_of_active_workshops();

	friend std::ostream& operator << (std::ostream& out, const Compression_Station& CS);
	friend std::istream& operator >> (std::istream& in, Compression_Station& CS);
};

