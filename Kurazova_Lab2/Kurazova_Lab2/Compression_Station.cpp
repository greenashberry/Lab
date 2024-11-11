#include "Compression_Station.h"
#include <iostream>;
#include <string>
#include <limits>
#include <unordered_map>
#include "Instruments.h"
#include <fstream>
using namespace std;

int Compression_Station::MaxID = 0;

Compression_Station::Compression_Station()
{
	id = MaxID++;
}

void change_number_of_active_workshops(Compression_Station& CS)
{
	cout << "Input number of active workshops:" << endl;
	CS.number_of_active_workshops = GetNumber(0, CS.number_of_workshops);
	update_workshops_effectiveness(CS);
}

void update_workshops_effectiveness(Compression_Station& CS)
{
	CS.workshops_effectiveness = (CS.number_of_active_workshops * 100) / CS.number_of_workshops;
}

bool CheckByName(const Compression_Station& CS, std::string parameter)
{
	return CS.name == parameter;
}

bool CheckByEqual(const Compression_Station& CS, int parameter)
{
	return CS.workshops_effectiveness == parameter;
}

bool CheckByMore(const Compression_Station& CS, int parameter)
{
	return CS.workshops_effectiveness >= parameter;
}

bool CheckByLess(const Compression_Station& CS, int parameter)
{
	return CS.workshops_effectiveness <= parameter;
}

std::ostream& operator<<(std::ostream& out, const Compression_Station& CS)
{
	cout << endl;
	cout << "Compression station's ID: " << CS.id << endl;
	cout << "Compression station: " << CS.name << std::endl;
	cout << "Number of workshops: " << CS.number_of_workshops << std::endl;
	cout << "Number of active workshops: " << CS.number_of_active_workshops << std::endl;
	cout << "Effectivenes: " << CS.effectiveness << "%" << std::endl;
	cout << "Workshop usage procentage: " << CS.workshops_effectiveness << endl;
	return out;
}

std::istream& operator >> (std::istream& in, std::unordered_map<int, Compression_Station>& CS_System)
{
	Compression_Station CS;
	cout << "ID of the compression station: " << CS.id << endl;
	cout << "Input compression station's name:" << endl;
	CS.name = GetName();
	cout << "Input number of workshops:" << endl;
	CS.number_of_workshops = GetNumber(1);
	cout << "Input number of active workshops:" << endl;
	CS.number_of_active_workshops = GetNumber(0, CS.number_of_workshops);
	update_workshops_effectiveness(CS);
	cout << "Input effectivenes (in %): " << endl;
	CS.effectiveness = GetNumber(0, 100);
	cout << "Workshop usage procentage: " << CS.workshops_effectiveness << endl;
	CS_System.insert({ CS.id, CS });
	return in;
}

std::ofstream& operator<<(std::ofstream& out, const Compression_Station& CS)
{
	out << "CSTATION" << endl
		<< CS.id << endl
		<< CS.name << endl
		<< CS.number_of_workshops << endl
		<< CS.number_of_active_workshops << endl
		<< CS.effectiveness << endl;
	return out;
}

std::ifstream& operator>>(std::ifstream& in, unordered_map<int, Compression_Station>& CS_system)
{
	Compression_Station CS;
	if (((in >> CS.id).fail()) || (in.peek() != '\n') || (CS.id < 0))
	{
		in.clear();
		in.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "File is invalid!" << endl;
		return in;
	}
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(in, CS.name);
	if (((in >> CS.number_of_workshops).fail()) || (in.peek() != '\n') || (CS.number_of_workshops < 0))
	{
		in.clear();
		in.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "File is invalid!" << endl;
		return in;
	}
	if (((in >> CS.number_of_active_workshops).fail()) || (in.peek() != '\n') || (CS.number_of_active_workshops < 0) || (CS.number_of_active_workshops > CS.number_of_workshops))
	{
		in.clear();
		in.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "File is invalid!" << endl;
		return in;
	}
	if (((in >> CS.effectiveness).fail()) || (in.peek() != '\n') || (CS.effectiveness < 0) || (CS.effectiveness > 100))
	{
		in.clear();
		in.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "File is invalid!" << endl;
		return in;
	}
	update_workshops_effectiveness(CS);
	CS_system.insert({ CS.id, CS });
	CS.MaxID = max(CS.MaxID, CS.id);
	return in;
}


