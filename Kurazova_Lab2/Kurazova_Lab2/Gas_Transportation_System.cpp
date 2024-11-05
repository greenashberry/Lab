#include "Gas_Transportation_System.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "Pipe.h"
#include "Compression_Station.h"
using namespace std;

std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Pipe>& Pipeline)
{
	if (Pipeline.size() == 0)
	{
		cout << "There is no pipes." << endl;
	}
	else
	{
		for (const auto& truba : Pipeline)
		{
			cout << truba.second;
		}
	}
	return out;
}

std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Compression_Station>& CS_system)
{
	if (CS_system.size() == 0)
	{
		cout << "There is no compression station." << endl;
	}
	else
	{
		for (const auto& CS : CS_system)
		{
			cout << CS.second;
		}
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const Gas_Transportation_System& GTS)
{
	cout << GTS.Pipeline;
	cout << GTS.CS_system;
	return out;
}

std::ofstream& operator<<(std::ofstream& out, const std::unordered_map<int, Pipe>& Pipeline)
{
	if (Pipeline.size() == 0)
	{
		return out;
	}
	for (const auto& truba : Pipeline)
	{
		out << truba.second;
	}
	return out;
}

std::ofstream& operator<<(std::ofstream& out, const std::unordered_map<int, Compression_Station>& CS_system)
{
	if (CS_system.size() == 0)
	{
		return out;
	}
	for (const auto& CS : CS_system)
	{
		out << CS.second;
	}
}

std::ofstream& operator<<(std::ofstream& out, const Gas_Transportation_System& GTS)
{
	if ((GTS.Pipeline.size() != 0) || (GTS.CS_system.size() != 0))
	{
		out << GTS.Pipeline;
		out << GTS.CS_system;
	}
	else
	{
		cout << "You are trying to save literally nothing." << endl;
	}
	return out;
}

std::ifstream& operator>>(std::ifstream& in, Gas_Transportation_System& GTS)
{
	if (!in)
	{
		cout << "File doesn't exist or it is invalid!" << endl;
		return in;
	}
	string input;
	while (getline(in, input))
	{
		if (input == "PIPE")
		{
			in >> GTS.Pipeline;
		}
		else if (input == "CSTATION")
		{
			in >> GTS.CS_system;
		}
	}
	return in;
}
