#pragma once
#include <string>
#include <iostream>
#include "Instruments.h"
#include <unordered_map>

class Compression_Station
{
	int id;
	std::string name;
	int number_of_workshops;
	int effectiveness;
public:
	static int MaxID_CS;
	int number_of_active_workshops;
	float workshopss_effectivenes = number_of_active_workshops / number_of_workshops;

	Compression_Station();

	void change_number_of_active_workshops();

	friend std::ostream& operator << (std::ostream& out, const Compression_Station& CS);
	friend std::istream& operator >> (std::istream& in, std::unordered_map<int, Compression_Station>&);

};

