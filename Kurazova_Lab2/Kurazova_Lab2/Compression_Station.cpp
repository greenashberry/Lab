#include "Compression_Station.h"
#include <iostream>;
#include <string>

std::ostream& operator<<(std::ostream& out, const Compression_Station& CS)
{
	return out;
}

std::istream& operator>>(std::istream& in, Compression_Station& CS)
{
	return in;
}

Compression_Station::Compression_Station()
{
}

void Compression_Station::change_number_of_active_workshops()
{
}
