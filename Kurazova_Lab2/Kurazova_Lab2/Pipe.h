#pragma once
#include "Instruments.h"
#include <string>
#include <iostream>


class Pipe
{
	std::string name;
	int length;
	int diameter;

public:
	bool maintenance_status;

	Pipe();

	void change_maintenance_status(Pipe&);
	bool existence_check_Pipe(const Pipe&);

	friend std::ostream& operator << (std::ostream& out, const Pipe& truba);
	friend std::istream& operator >> (std::istream& in, Pipe& truba);
};

