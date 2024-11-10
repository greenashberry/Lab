#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "Instruments.h"
#include "Pipe.h"
#include "Compression_Station.h"
#include <fstream>

class Gas_Transportation_System
{
public:
	std::unordered_map<int, Pipe> Pipeline;
	std::unordered_map<int, Compression_Station> CS_system;

	friend std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Pipe>& Pipeline);
	friend std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Compression_Station>& CS_system);
	friend std::ostream& operator << (std::ostream& out, const Gas_Transportation_System& GTS);
	friend std::ofstream& operator << (std::ofstream& out, const std::unordered_map<int, Pipe>& Pipeline);
	friend std::ofstream& operator << (std::ofstream& out, const std::unordered_map<int, Compression_Station>& CS_system);
	friend std::ofstream& operator << (std::ofstream& out, const Gas_Transportation_System& GTS);
	friend std::ifstream& operator >> (std::ifstream& in, Gas_Transportation_System& GTS);

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