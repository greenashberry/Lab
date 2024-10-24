#include "Pipe.h"
#include <iostream>
#include <string>

Pipe::Pipe()
{
}

bool Pipe::existence_check_Pipe(const Pipe&)
{
	return false;
}


std::ostream& operator<<(std::ostream& out, const Pipe& truba)
{
	return out;
}

std::istream& operator>>(std::istream& in, Pipe& truba)
{
	return in;
}
