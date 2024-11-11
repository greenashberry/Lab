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
std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Pipe>& Pipeline);
std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Compression_Station>& CS_system);
void PipesFiltering(std::unordered_map<int, Pipe>&);
void CSFiltering(std::unordered_map<int, Compression_Station>);



void Menu()
{
    cout << "1. Add pipe" << endl;
    cout << "2. Add compression station" << endl;
    cout << "3. View all objects" << endl;
    cout << "4. Find pipes" << endl;
    cout << "5. Find compression stations" << endl;
    cout << "6. Save" << endl;
    cout << "7. Load" << endl;
    cout << "8. Redact pipes" << endl;
    cout << "9. Redact CSs" << endl;
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
        switch (GetNumber(0, 9))
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
            GTS.PipesFiltering(GTS, GTS.Pipeline);
            break;
            //Фильтрация труб
        }
        case 5:
        {
            GTS.CSFiltering(GTS, GTS.CS_system);
            break;
            //Фильтрация КС
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
        case 8:
        {
            GTS.PipelinePacket(GTS, GTS.Pipeline);
            break;
        }
        case 9:
        {
            GTS.CSPacket(GTS, GTS.CS_system);
            break;
        }
        case 0:
        {
            return 0;
        }
        }
    }
}
