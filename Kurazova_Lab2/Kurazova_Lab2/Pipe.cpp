#include "Pipe.h"
#include <iostream>
#include <string>
#include "Instruments.h"
#include "Gas_Transportation_System.h"
using namespace std;

int Pipe::MaxID = 0;

Pipe::Pipe()
{
	id = MaxID++;
}

void Pipe::change_maintenance_status(Pipe& truba)
{
	cout << "Input pipe's maintenance status (1 - in maintenance, 0 - not in maintenance):" << endl;
	truba.maintenance_status = GetNumber(0, 1);
}

int Pipe::GetID(const Pipe& truba)
{
	return truba.id;
}

bool CheckByName(const Pipe& truba, string parameter)
{
	return ((truba.name.find(parameter) != string::npos) ? 1 : 0);
}

bool CheckByMaintenanceStatus(const Pipe& truba, bool parameter)
{
	return truba.maintenance_status == parameter;
}

bool CheckByDiameter(const Pipe& truba, int parameter)
{
	return truba.diameter == parameter;
}

std::ostream& operator<<(std::ostream& out, const Pipe& truba)
{
	cout << "\nId: " << truba.id << std::endl;
	cout << "Pipe: " << truba.name << std::endl;
	cout << "Pipe length: " << truba.length << std::endl;
	cout << "Pipe diameter: " << truba.diameter << std::endl;
	cout << "Pipe status: " << (truba.maintenance_status ? "in maintenance" : "working") << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, std::unordered_map<int, Pipe>& Pipeline)
{
	Pipe truba;
	cout << "ID of the pipe: " << truba.id << endl;
	cout << "Inpit pipe's name:" << endl;
	truba.name = GetName();
	cout << "Input pipe's length:" << endl;
	truba.length = GetNumber(1);
	cout << "Input pipe's diameter:" << endl;
	truba.diameter = GetNumber(1);
	cout << "Input pipe's maintenance status (1 - in maintenance, 0 - not in maintenance):" << endl;
	truba.maintenance_status = GetNumber(0, 1);
	Pipeline.insert({ truba.GetID(truba), truba });
	return in;
}

std::ofstream& operator<<(std::ofstream& out, const Pipe& truba)
{
	out << "PIPE" << endl
		<< truba.id << endl
		<< truba.name << endl
		<< truba.length << endl
		<< truba.diameter << endl
		<< truba.maintenance_status << endl;
	return out;
}

std::ifstream& operator>>(std::ifstream& in, std::unordered_map<int, Pipe>& Pipeline)
{
	Pipe truba;
	if (((in >> truba.id).fail()) || (in.peek() != '\n') || (truba.id < 0))
	{
		in.clear();
		in.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "File is invalid!" << endl;
		return in;
	}
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(in, truba.name);
	if (((in >> truba.length).fail()) || (in.peek() != '\n') || (truba.length < 0))
	{
		in.clear();
		in.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "File is invalid!" << endl;
		return in;
	}
	if (((in >> truba.diameter).fail()) || (in.peek() != '\n') || (truba.diameter < 0))
	{
		in.clear();
		in.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "File is invalid!" << endl;
		return in;
	}
	if (((in >> truba.maintenance_status).fail()) || (in.peek() != '\n') || ((truba.maintenance_status != 0) && (truba.maintenance_status != 1)))
	{
		in.clear();
		in.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "File is invalid!" << endl;
		return in;
	}
	Pipeline.insert({ truba.id, truba });
	truba.MaxID = max(truba.id, truba.MaxID);
	return in;
}


