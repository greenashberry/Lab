#include "Compression_Station.h"
#include <iostream>;
#include <string>
#include <limits>
#include <unordered_map>
#include "Instruments.h"
using namespace std;

int Compression_Station::MaxID_CS = 0;

Compression_Station::Compression_Station()
{
	id = MaxID_CS++;
}

std::ostream& operator<<(std::ostream& out, const Compression_Station& CS)
{
	cout << "Compression station: " << CS.name << std::endl;
	cout << "Number of workshops: " << CS.number_of_workshops << std::endl;
	cout << "Number of active workshops: " << CS.number_of_active_workshops << std::endl;
	cout << "Effectivenes: " << CS.effectiveness << "%" << std::endl;
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
	CS_System.insert({ CS.id, CS });
	return in;
}

void Compression_Station::change_number_of_active_workshops()
{
}
