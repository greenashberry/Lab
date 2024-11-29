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

void Link::CreateLink(Gas_Transportation_System& GTS, std::vector<Link> system)
{
	Link k;
	while ((!GTS.CS_system.contains(k.CS_inlet)) || (!GTS.CS_system.contains(k.CS_outlet)) || (!GTS.Pipeline.contains(k.pipeline)))
	{
		cout << "Input an ID of inlet compression station:" << endl;
		k.CS_inlet = GetNumber(0);
		if (!GTS.Pipeline.contains(k.CS_inlet))
		{
			cin.ignore(1000, '\n');
			cout << "There is no pipe with this ID." << endl;
			continue;
		}
		cout << "Input an ID of outlet compression station:" << endl;
		k.CS_outlet = GetNumber(0);
		if (!GTS.Pipeline.contains(k.CS_outlet))
		{
			cin.ignore(1000, '\n');
			cout << "There is no pipe with this ID." << endl;
			continue;
		}
		cout << "Input pipe's diameter: " << endl;
		int parameter = GetNumber(0, 1000);

	}
}
