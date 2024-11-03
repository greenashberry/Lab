#include "Pipe.h"
#include <iostream>
#include <string>
#include "Instruments.h"
#include "Gas_Transportation_System.h"
using namespace std;

int Pipe::MaxID_Pipe = 0;

Pipe::Pipe()
{
	id = MaxID_Pipe++;
}

void Pipe::change_maintenance_status(Pipe&)
{

}

int Pipe::GetID(const Pipe& truba)
{
	return truba.id;
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


