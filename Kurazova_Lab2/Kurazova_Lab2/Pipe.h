#pragma once
#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>


class Pipe
{
	int id;
	std::string name;
	int length;
	int diameter;
public:
	static int MaxID_Pipe;
	bool maintenance_status;

	Pipe();

	void change_maintenance_status(Pipe&);
	int GetID(const Pipe&);

	friend std::ostream& operator << (std::ostream& out, const Pipe&);
	friend std::istream& operator >> (std::istream& in, std::unordered_map<int, Pipe>&);
	friend std::ofstream& operator << (std::ofstream& out, const Pipe&);
	friend std::ifstream& operator >> (std::ifstream& in, std::unordered_map<int, Pipe>&);

	template<typename T>
	using FilterPipe = bool(*)(const Pipe& truba, T parameter);
	bool CheckByName(const Pipe& truba, string parameter)
	{
		return truba.name == parameter;
	}
	bool CheckByMaintenanceStatus(const Pipe& truba, bool parameter)
	{
		return truba.maintenance_status == parameter;
	}
};

