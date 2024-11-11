#pragma once
#include <string>
#include <iostream>
#include "Instruments.h"
#include <fstream>
#include <unordered_map>
#include <string>

class Compression_Station
{
	int id;
	std::string name;
	int number_of_workshops;
	int effectiveness;
public:
	static int MaxID;
	int number_of_active_workshops;
	int workshops_effectiveness = (number_of_active_workshops * 100) / number_of_workshops;

	Compression_Station();

	friend void update_workshops_effectiveness(Compression_Station& CS);
	friend void change_number_of_active_workshops(Compression_Station&);
	std::string get_pipe_name(const Compression_Station& CS) { return CS.name; };
	friend bool CheckByName(const Compression_Station& CS, std::string parameter);
	friend bool CheckByEqual(const Compression_Station&, int);
	friend bool CheckByMore(const Compression_Station&, int);
	friend bool CheckByLess(const Compression_Station&, int);
	int get_workshops_number() const { return number_of_workshops; };

	friend std::ostream& operator << (std::ostream& out, const Compression_Station& CS);
	friend std::istream& operator >> (std::istream& in, std::unordered_map<int, Compression_Station>&);
	friend std::ofstream& operator << (std::ofstream& out, const Compression_Station& CS);
	friend std::ifstream& operator >> (std::ifstream& in, std::unordered_map<int, Compression_Station>&);
};