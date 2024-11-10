#include "Gas_Transportation_System.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "Pipe.h"
#include "Compression_Station.h"
using namespace std;

bool CheckByName(const Pipe& truba, std::string parameter);
bool CheckByMaintenanceStatus(const Pipe& truba, bool parameter);
bool CheckByName(const Compression_Station& CS, std::string parameter);
bool CheckByEqual(const Compression_Station&, int);
bool CheckByMore(const Compression_Station&, int);
bool CheckByLess(const Compression_Station&, int);

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
		cout << "There is no compression stations." << endl;
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

void Gas_Transportation_System::delete_pipe(unordered_map<int, Pipe>& Pipeline, int ID)
{
	Pipeline.erase(ID);
}

void Gas_Transportation_System::delete_CS(unordered_map<int, Compression_Station>& CS_system, int ID)
{
	CS_system.erase(ID);
}

void Gas_Transportation_System::PipesFiltering(std::unordered_map<int, Pipe>& Pipeline)
{
	cout << "Choose filter choice:" << endl
		<< "    1. Name" << endl
		<< "    2. Maintenance status" << endl;
	switch (GetNumber(1, 2))
	{
	case 1:
	{
		cout << "Input name:" << endl;
		string PipeNameToFind = GetName();
		unordered_map<int, Pipe> filtered = FindPipesByFilter(Pipeline, CheckByName, PipeNameToFind);
		cout << filtered;
		break;
	}
	case 2:
	{
		cout << "Input maintenance status:" << endl;
		bool PipeStatusToFind = GetNumber(0, 1);
		unordered_map<int, Pipe> filtered = FindPipesByFilter(Pipeline, CheckByMaintenanceStatus, PipeStatusToFind);
		cout << filtered;
		break;
	}
	}
}

void Gas_Transportation_System::CSFiltering(std::unordered_map<int, Compression_Station> CS_system)
{
	cout << "Choose filter choice:" << endl
		<< "    1. Name" << endl
		<< "    2. Workshop usage (in %)" << endl;
	switch (GetNumber(1, 2))
	{
	case 1:
	{
		cout << "Input name:" << endl;
		string CSNameToFind = GetName();
		unordered_map<int, Compression_Station> filtered = FindCSByFilter(CS_system, CheckByName, CSNameToFind);
		cout << filtered;
		break;
	}
	case 2:
		cout << "Input percent of workshop usage:" << endl;
		int CSWorkshopsToFind = GetNumber(0, 100);
		cout << "Choose an option:" << endl
			<< "  1. Equal" << endl
			<< "  2. More (and equal)" << endl
			<< "  3. Less (and equal)" << endl;
		switch (GetNumber(1, 3))
		{
		case 1:
		{
			unordered_map<int, Compression_Station> filtered = FindCSByFilter(CS_system, CheckByEqual, CSWorkshopsToFind);
			cout << filtered;
			break;
		}
		case 2:
		{
			unordered_map<int, Compression_Station> filtered = FindCSByFilter(CS_system, CheckByMore, CSWorkshopsToFind);
			cout << filtered;
			break;
		}
		case 3:
		{
			unordered_map<int, Compression_Station> filtered = FindCSByFilter(CS_system, CheckByLess, CSWorkshopsToFind);
			cout << filtered;
			break;
		}
		}
		break;
	}
}



