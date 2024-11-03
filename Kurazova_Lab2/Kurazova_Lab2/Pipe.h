#pragma once
#include <string>
#include <iostream>
#include <unordered_map>


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
};

