#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "Instruments.h"
#include "Pipe.h"
#include "Compression_Station.h"
#include <fstream>
#include <unordered_set>

struct Gas_Transportation_System
{
	std::unordered_map<int, Pipe> Pipeline;
	std::unordered_map<int, Compression_Station> CS_system;

	friend std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Pipe>& Pipeline);
	friend std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Compression_Station>& CS_system);
	friend std::ostream& operator << (std::ostream& out, const Gas_Transportation_System& GTS);
	friend std::ofstream& operator << (std::ofstream& out, const std::unordered_map<int, Pipe>& Pipeline);
	friend std::ofstream& operator << (std::ofstream& out, const std::unordered_map<int, Compression_Station>& CS_system);
	friend std::ofstream& operator << (std::ofstream& out, const Gas_Transportation_System& GTS);
	friend std::ifstream& operator >> (std::ifstream& in, Gas_Transportation_System& GTS);

	void delete_pipe(std::unordered_map<int, Pipe>& Pipeline, int ID);
	void delete_CS(std::unordered_map<int, Compression_Station>& CS_system, int ID);
	void PipesFiltering(Gas_Transportation_System& GTS, std::unordered_map<int, Pipe>&);
	void CSFiltering(Gas_Transportation_System& GTS, std::unordered_map<int, Compression_Station>);
	void PacketEditPipe(std::unordered_map<int, Pipe>&, std::unordered_set<int>&, bool);
	void PacketEditCS(std::unordered_map<int, Compression_Station>&, std::unordered_set<int>&);
	int PipelinePacket(Gas_Transportation_System& GTS, std::unordered_map<int, Pipe>& Pipe_List);
	int CSPacket(Gas_Transportation_System& GTS, std::unordered_map<int, Compression_Station>& CS_System);


	template<class T>
	int DeleteObjects(std::unordered_map<int, T>& System, std::unordered_set<int>& IDs)
	{
		if ((System.empty()) || (IDs.empty()))
		{
			std::cout << "There is no objects or you didn't give any IDs." << std::endl;
			return 0;
		}
		for (const auto& s : IDs)
		{
			System.erase(s);
		}
		return 1;
	}

	template<class T>
	std::unordered_set<int> GetIds(const std::unordered_map<int, T>& System)
	{
		std::unordered_set<int> IDs;
		if (System.empty())
		{
			std::cout << "You don't have any of these objects!" << std::endl;
			return IDs;
		}
		std::cout << "Choose an option:" << std::endl
			<< "	1. Choose by hand" << std::endl
			<< "	2. Choose all" << std::endl;
		switch (GetNumber(1, 2))
		{
		case 1:
		{
			while (true)
			{
				std::cout << "Type -1 to stop" << std::endl;
				int option = GetNumber(-1, T::MaxID - 1);
				switch (option)
				{
				case -1: { return IDs; }
				default: 
				{
					if (System.contains(option))
					{
						IDs.insert(option);
					}
					else
					{
						std::cout << "There is no object with this ID!" << std::endl;
					}
				}
				}
			}
		}
		case 2:
		{
			for (const auto& s : System)
			{
				IDs.insert(s.first);
			}
			return IDs;
		}
		}
	}

	template<typename T>
	using FilterPipes = bool(*)(const Pipe& truba, T parameter);

	template<typename T>
	std::unordered_map<int, Pipe> FindPipesByFilter(const std::unordered_map<int, Pipe>& Pipeline, FilterPipes<T> filter, T parameter)
	{
		std::unordered_map <int, Pipe> result;
		for (auto& s : Pipeline)
		{
			if (filter(s.second, parameter))
			{
				result.insert(s);
			}
		}
		return result;
	}

	template<typename T>
	using FilterCS = bool(*)(const Compression_Station& CS, T parameter);

	template<typename T>
	std::unordered_map<int, Compression_Station> FindCSByFilter(const std::unordered_map<int, Compression_Station>& CS_system, FilterCS<T> filter, T parameter)
	{
		std::unordered_map<int, Compression_Station> result;
		for (auto& s : CS_system)
		{
			if (filter(s.second, parameter))
			{
				result.insert(s);
			}
		}
		return result;
	}
};