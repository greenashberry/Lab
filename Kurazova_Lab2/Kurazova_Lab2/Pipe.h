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
	static int MaxID;
	bool maintenance_status;
	bool part_of_the_link = 0;

	Pipe();

	void change_maintenance_status(Pipe&);
	int GetID(const Pipe&);

	friend bool CheckByName(const Pipe& truba, std::string parameter);
	friend bool CheckByMaintenanceStatus(const Pipe& truba, bool parameter);
	friend bool CheckByDiameter(const Pipe& Truba, int parameter);
	friend bool CheckByAvailability(const Pipe& Truba, bool parameter);
	int GetLength() const { return length; };

	friend std::ostream& operator << (std::ostream& out, const Pipe&);
	friend std::istream& operator >> (std::istream& in, std::unordered_map<int, Pipe>&);
	friend std::ofstream& operator << (std::ofstream& out, const Pipe&);
	friend std::ifstream& operator >> (std::ifstream& in, std::unordered_map<int, Pipe>&);
};

