#include "Link.h"
#include <iostream>
#include <fstream>
#include "Pipe.h"
#include "Gas_Transportation_System.h"
#include "Compression_Station.h"
#include <vector>
#include <unordered_map>
#include "Instruments.h"
using namespace std;

bool CheckByDiameter(const Pipe& Truba, int parameter);
bool CheckByAvailability(const Pipe& Truba, bool parameter);
struct Gas_Transportation_System;
std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Pipe>& Pipeline);

bool Link::CreateLink(Gas_Transportation_System& GTS, std::vector<Link>& system, Link& k)
{
	if (GTS.CS_system.size() < 2)
	{
		cout << "There is no compression stations." << endl;
		return 0;
	}
	while (!CheckAnExistence(k.CS_inlet, GTS.CS_system))
	{
		cout << "Input an ID of inlet compression station:" << endl;
		k.CS_inlet = GetNumber(0);
		if (!CheckAnExistence(k.CS_inlet, GTS.CS_system))
		{
			cout << "There is no compression station with this ID!" << endl;
		}
	}
	while (!CheckAnExistence(k.CS_outlet, GTS.CS_system) || (k.CS_inlet == k.CS_outlet))
	{
		cout << "Input an ID of outlet compression station:" << endl;
		k.CS_outlet = GetNumber(0);
		if (!CheckAnExistence(k.CS_outlet, GTS.CS_system))
		{
			cout << "There is no compression station with this ID!" << endl;
		}
		if (k.CS_inlet == k.CS_outlet)
		{
			cout << "Your inlet compresssion station can't be your outlet compression station." << endl;
		}
	}
	int diameter;
	cout << "Input a diameter of needed pipe:" << endl;
	diameter = GetNumber(1);
	unordered_map<int, Pipe> suitable_pipes = FindPipesByFilter(GTS.Pipeline, CheckByDiameter, diameter);
	unordered_map<int, Pipe> available_pipes = FindPipesByFilter(suitable_pipes, CheckByAvailability, false);
	if (available_pipes.empty())
	{
		cout << "There is no available suitable pipes. Redirecting you to adding a new pipe." << endl;
		cin >> GTS.Pipeline;
		k.pipeline = Pipe::MaxID - 1;
		GTS.Pipeline[k.pipeline].part_of_the_link = 1;
	}
	else
	{
		cout << "Available pipes:" << endl;
		cout << available_pipes;
		cout << "Choose out of the availavle pipes:" << endl;
		while (!CheckAnExistence(k.pipeline, available_pipes))
		{
			k.pipeline = GetNumber(0);
			if (!CheckAnExistence(k.pipeline, available_pipes))
			{
				cout << "Choose out of available pipes!" << endl;
			}
			else
			{
				GTS.Pipeline[k.pipeline].part_of_the_link = 1;
			}
		}
	}
	system.push_back(k);
	return 1;
}

std::ostream& operator<<(std::ostream& out, const Link& link)
{
	cout << "ID of the inlet compression station: " << link.CS_inlet << endl;
	cout << "ID of the outlet compression station: " << link.CS_outlet << endl;
	cout << "ID of the pipe in connection: " << link.pipeline << endl << endl;
	return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<Link>& system)
{
	if (system.empty())
	{
		cout << "There is no active connections." << endl;
	}
	else
	{
		for (auto i : system)
		{
			cout << i;
		}
	}
	return out;
}
