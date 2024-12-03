#pragma once
#include "Compression_Station.h"
#include "Pipe.h"
#include <string>
#include "Gas_Transportation_System.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "Instruments.h"
#include <unordered_set>
#include <stack>

struct Link
{
	int pipeline = -1;
	int CS_inlet = -1;
	int CS_outlet = -1;

	bool CreateLink(Gas_Transportation_System& GTS, std::vector<Link>& system, Link& k);
	friend void TopSort(const std::unordered_map<int, Compression_Station>& CS, const std::vector<Link>& connections);
	friend void dfs(int station, std::vector<int>& order, std::unordered_set<int>& visited, const std::vector<Link>& connections, std::unordered_set<int>& gray_stations, bool& flag);
	friend void deletePipeConnection(int id, std::vector<Link>& connections);
	friend void deleteCSConnections(int id, std::vector<Link>& connections);

	friend std::ostream& operator << (std::ostream& out, const Link& link);
	friend std::ostream& operator << (std::ostream& out, const std::vector<Link>& system);
	friend std::ofstream& operator << (std::ofstream& out, const Link& link);
	friend std::ofstream& operator << (std::ofstream& out, const std::vector<Link>& system);
	friend std::ifstream& operator >> (std::ifstream& out, Link& connection);
	
	
	template <typename T>
	bool CheckAnExistence(int id, const std::unordered_map<int, T>& elements)
	{
		return elements.contains(id);
	}
};