#include "Instruments.h"
#include <iostream>
#include <string>
using namespace std;

std::string GetName()
{
    string name;
    while (true)
    {
        getline(cin, name);
        if (!name.empty())
        {
            return name;
        }
        else
        {
            cout << "Invalid input. Please input a valid name." << endl;
        }
    }
    return std::string();
}
