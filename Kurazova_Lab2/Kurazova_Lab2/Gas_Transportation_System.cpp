#include "Gas_Transportation_System.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "Pipe.h"
#include "Compression_Station.h"
#include <unordered_set>
using namespace std;

bool CheckByName(const Pipe& truba, std::string parameter);
bool CheckByMaintenanceStatus(const Pipe& truba, bool parameter);
bool CheckByName(const Compression_Station& CS, std::string parameter);
bool CheckByEqual(const Compression_Station&, int);
bool CheckByMore(const Compression_Station&, int);
bool CheckByLess(const Compression_Station&, int);
void change_number_of_active_workshops(Compression_Station&);

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

void Gas_Transportation_System::PipesFiltering(Gas_Transportation_System& GTS, std::unordered_map<int, Pipe>& Pipeline)
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
		if (!filtered.empty()) { PipelinePacket(GTS, filtered); };
		break;
	}
	case 2:
	{
		cout << "Input maintenance status:" << endl;
		bool PipeStatusToFind = GetNumber(0, 1);
		unordered_map<int, Pipe> filtered = FindPipesByFilter(Pipeline, CheckByMaintenanceStatus, PipeStatusToFind);
		cout << filtered;
		if (!filtered.empty()) { PipelinePacket(GTS, filtered); };
		break;
	}
	}
}

void Gas_Transportation_System::CSFiltering(Gas_Transportation_System& GTS, std::unordered_map<int, Compression_Station> CS_system)
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
		if (!filtered.empty()) { CSPacket(GTS, filtered); };
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
			if (!filtered.empty()) { CSPacket(GTS, filtered); };
			break;
		}
		case 2:
		{
			unordered_map<int, Compression_Station> filtered = FindCSByFilter(CS_system, CheckByMore, CSWorkshopsToFind);
			cout << filtered;
			if (!filtered.empty()) { CSPacket(GTS, filtered); };
			break;
		}
		case 3:
		{
			unordered_map<int, Compression_Station> filtered = FindCSByFilter(CS_system, CheckByLess, CSWorkshopsToFind);
			cout << filtered;
			if (!filtered.empty()) { CSPacket(GTS, filtered); };
			break;
		}
		}
		break;
	}
}

void Gas_Transportation_System::PacketEditPipe(std::unordered_map<int, Pipe>& Pipeline, unordered_set<int>& IDs, bool state)
{
	for (const auto& s : IDs)
	{
		Pipeline[s].maintenance_status = state;
	}
}

void Gas_Transportation_System::PacketEditCS(std::unordered_map<int, Compression_Station>& CS_System, std::unordered_set<int>& IDs)
{
	for (const auto& s : IDs)
	{
		cout << "Number of workshops of this CS: " << CS_System[s].get_workshops_number() << endl;
		change_number_of_active_workshops(CS_System[s]);
	}
}

int Gas_Transportation_System::PipelinePacket(Gas_Transportation_System& GTS, std::unordered_map<int, Pipe>& Pipe_List)
{
	if (Pipe_List.empty())
	{
		return 0;
	}
	cout << "Pick an option:" << endl
		<< "	1. Delete pipes" << endl
		<< "	2. Change maintenance status" << endl
		<< "	3. Exit" << endl;
	switch (GetNumber(1, 3))
	{
	case 1:
	{
		unordered_set<int> IDs = GetIds(Pipe_List);
		DeleteObjects(GTS.Pipeline, IDs);
		return 1;
	}
	case 2:
	{
		unordered_set<int> IDs = GetIds(Pipe_List);
		cout << "Input maintenance status (1 - in maintenance, 0 - not in maintenance): " << endl;
		bool state = GetNumber(0, 1);
		PacketEditPipe(GTS.Pipeline, IDs, state);
		return 1;
	}
	case 3:
	{
		return 0;
	}
	}
}

int Gas_Transportation_System::CSPacket(Gas_Transportation_System& GTS, std::unordered_map<int, Compression_Station>& CS_System)
{
	if (CS_System.empty())
	{
		return 0;
	}
	cout << "Pick an option:" << endl
		<< "	1. Delete CSs" << endl
		<< "	2. Change namber of active workshops" << endl
		<< "	3. Exit" << endl;
	switch (GetNumber(1, 3))
	{
	case 1:
	{
		unordered_set<int> IDs = GetIds(CS_System);
		DeleteObjects(GTS.Pipeline, IDs);
		return 1;
	}
	case 2:
	{
		unordered_set<int> IDs = GetIds(CS_System);
		cout << "Input maintenance status (1 - in maintenance, 0 - not in maintenance): " << endl;
		PacketEditCS(GTS.CS_system, IDs);
		return 1;
	}
	case 3:
	{
		return 0;
	}
	}
}






