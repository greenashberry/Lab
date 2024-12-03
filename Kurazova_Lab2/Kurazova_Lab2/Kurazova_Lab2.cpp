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
#include "Link.h"
using namespace std;

struct Link;
void Menu();
std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Pipe>& Pipeline);
std::ostream& operator << (std::ostream& out, const std::unordered_map<int, Compression_Station>& CS_system);
void PipesFiltering(std::unordered_map<int, Pipe>&);
void CSFiltering(std::unordered_map<int, Compression_Station>);
void TopSort(const std::unordered_map<int, Compression_Station>& CS, const std::vector<Link>& connections);
void LoadConnections(std::vector<Link>& connections, const Gas_Transportation_System& GTS, ifstream& in);

void Menu()
{
    cout << "1. Add pipe" << endl;
    cout << "2. Add compression station" << endl;
    cout << "3. View all objects" << endl;
    cout << "4. Find pipes" << endl;
    cout << "5. Find compression stations" << endl;
    cout << "6. Save" << endl;
    cout << "7. Load" << endl;
    cout << "8. Edit pipes" << endl;
    cout << "9. Edit CSs" << endl;
    cout << "10. Add a connection" << endl;
    cout << "11. View all connections" << endl;
    cout << "12. Topological sort" << endl;
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
    Gas_Transportation_System FreeObjects;
    vector<Link> connections;

    while (1)
    {
        Menu();
        switch (GetNumber(0, 12))
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
            GTS.PipesFiltering(GTS, GTS.Pipeline, connections);
            break;
            //Фильтрация труб
        }
        case 5:
        {
            GTS.CSFiltering(GTS, GTS.CS_system, connections);
            break;
            //Фильтрация КС
        }
        case 6:
        {
            cout << "Enter name for a file:" << endl;
            string savefile = GetName();
            ofstream fout(savefile);
            fout << GTS;
            fout << connections;
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
            LoadConnections(connections, GTS, fin);
            fin.close();
            break;
            //Загрузить
        }
        case 8:
        {
            GTS.PipelinePacket(GTS, GTS.Pipeline, connections);
            break;
        }
        case 9:
        {
            GTS.CSPacket(GTS, GTS.CS_system, connections);
            break;
        }
        case 10:
        {
            Link k;
            k.CreateLink(GTS, connections, k);
            break;
        }
        case 11:
        {
            cout << connections;
            break;
        }
        case 12:
        {
            TopSort(GTS.CS_system, connections);
            break;
        }
        case 0:
        {
            return 0;
        }
        }
    }
}
