#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <chrono>
#include <unordered_map>;
#include "redirect_output_wrapper.h"
#include "Pipe.h"
#include "Compression_Station.h"
#include "Gas_Transportation_System.h"
#include "Instruments.h"
using namespace std;

void Menu();
void PipesFiltering(Gas_Transportation_System&);
void CSFiltering(Gas_Transportation_System&);
bool CheckByName(const Pipe& truba, std::string parameter);
bool CheckByMaintenanceStatus(const Pipe& truba, bool parameter);
bool CheckByName(const Compression_Station& CS, std::string parameter);
bool CheckByEffectiveness(const Compression_Station& CS, int parameter);
std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Pipe>& Pipeline);
std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Compression_Station>& CS_system);


void PipesFiltering(Gas_Transportation_System& GTS)
{
    cout << "Choose filter choice:" << endl
        << "    1. Name" << endl
        << "    2. Maintenance status" << endl;
    switch (GetNumber(1, 2))
    {
    case 1:
    {
        cout << "Input name:" << endl;
        string PipeNameToFind = GetName();
        cout << GTS.FindPipesByFilter(GTS.Pipeline, CheckByName, PipeNameToFind);
        break;
    }
    case 2:
    {
        cout << "Input maintenance status:" << endl;
        bool PipeStatusToFind = GetNumber(0, 1);
        cout << GTS.FindPipesByFilter(GTS.Pipeline, CheckByMaintenanceStatus, PipeStatusToFind);
        break;
    }
    }
}


void CSFiltering(Gas_Transportation_System& GTS)
{
    cout << "Choose filter choice:" << endl
        << "    1. Name" << endl
        << "    2. Workshop usage (in %)" << endl;
    switch (GetNumber(1, 2))
    {
    case 1:
    {
        cout << "Input name:" << endl;
        string CSNameToFind = GetName();
        cout << GTS.FindCSByFilter(GTS.CS_system, CheckByName, CSNameToFind);
        break;
    }
    case 2:
        cout << "Input percent of workshop usage:" << endl;
        int CSWorkshopsToFind = GetNumber(0, 100);
        cout << GTS.FindCSByFilter(GTS.CS_system, CheckByEffectiveness, CSWorkshopsToFind);
        break;
    }
}


void Menu()
{
    cout << "1. Add pipe" << endl;
    cout << "2. Add compression station" << endl;
    cout << "3. View all objects" << endl;
    cout << "4. Find pipes" << endl;
    cout << "5. Find compression stations" << endl;
    cout << "6. Save" << endl;
    cout << "7. Load" << endl;
    cout << "0. Exit" << endl;
}


int main()
{
    redirect_output_wrapper cer_out(cerr);
    string time = std::format("{:%d_%m_%Y %H_%M_%OS}", chrono::system_clock::now());
    ofstream logfile("log_" + time);
    if (logfile)
    {
        cer_out.redirect(logfile);
    }

    Gas_Transportation_System GTS;

    while (1)
    {
        Menu();
        switch (GetNumber(0, 7))
        {
        case 1:
        {
            cin >> GTS.Pipeline;
            break;
            //Здесь добавление трубы
        }
        case 2:
        {
            cin >> GTS.CS_system;
            break;
            //Добавить КС
        }
        case 3:
        {
            cout << GTS;
            break;
            //Посмотреть все объекты
        }
        case 4:
        {
            PipesFiltering(GTS);
            break;
        }
        case 5:
        {
            CSFiltering(GTS);
            break;
        }
        case 6:
        {
            cout << "Enter name for a file:" << endl;
            string savefile = GetName();
            ofstream fout(savefile);
            fout << GTS;
            fout.close();
            break;
            //Сохранить
        }
        case 7:
        {
            cout << "Please input the name of the save file:" << endl;
            string savefile = GetName();
            ifstream fin(savefile);
            fin >> GTS;
            fin.close();
            break;
            //Загрузить
        }
        case 0:
        {
            return 0;
        }
        }
    }
}
