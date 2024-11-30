#pragma once
#include "Compression_Station.h"
#include "Pipe.h"
#include <string>
#include "Gas_Transportation_System.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "Instruments.h"

struct Link
{
	int pipeline = -1;
	int CS_inlet = -1;
	int CS_outlet = -1;

	bool CreateLink(Gas_Transportation_System& GTS, std::vector<Link> system, Link k);

	friend std::ostream& operator << (std::ostream& out, const Link& link);
	friend std::ofstream& operator << (std::ofstream& out, const Link& link);
	friend std::ofstream& operator << (std::ofstream& out, const std::vector<Link>& system);

	template <typename T>
	bool CheckAnExistence(int id, const std::unordered_map<int, T>& elements)
	{
		return elements.contains(id);
	}
};