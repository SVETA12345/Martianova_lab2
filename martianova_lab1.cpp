#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include "Pipe.h"
#include "Station.h"
#include "Station.cpp"
#include <unordered_map>

using namespace std;
typedef unordered_map <int, Station> MapStation;

// оператор ввода трубы
void operator >> (istream& in, Pipe& pipe){
    do
    {
        // очищает флаг ошибки
        cin.clear();
        // переходит к следующей новой строке
        cin.ignore(10000, '\n');
        cout << "Type name: ";
        getline(cin, pipe.name);
    } while (pipe.name == "");
    do
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Type length: ";
        cin >> pipe.length;
    } while (cin.fail() || pipe.length<0);
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type diameter: ";
        cin >> pipe.diameter;
    } while (cin.fail() || pipe.diameter<0);
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type in repair (1=in repair, 0=not in repair): ";
        cin >> pipe.isRepair;
    } while (cin.fail());
}


// редактирование трубы
void EditPipe(Pipe &pipe)
{
    pipe.isRepair=!pipe.isRepair;
};

// редактирование станции
void EditStation(Station &station)
{
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Number of workshops in operation: ";
        cin >> station.countWork;
    } while (cin.fail() || station.countWork<0 || station.countWork>station.countAll);
};

// вывод трубы в консоль
void operator << (ostream& out, const Pipe& p){
    cout << "Pipe" << endl;
    cout << "Name: " << p.name
         << "\tLength: " << p.length
         << "\tDiameter: " << p.diameter
         << "\tIsRepair: " << p.isRepair << endl;
}

// чтение данных из файла о станции
auto LoadStation(unordered_map<int, Station> &AllStation)
{
    
    ifstream fin;
    string st, s;
    Station station;
    int indexLine=0;
    int lengthStation = 9;
    string listData[5];
    // окрываем файл
    fin.open("data.txt");
    // проверка на открытие файла
    if (fin.is_open())
    {
        while (getline(fin, st))
        { // пока не достигнут конец файла класть очередную строку в переменную (st)
            // ss - это объект stringstream, который ссылается на строку st.
            stringstream ss(st);
            if (st.find("station") != string::npos);
            int index = 0;
            {
                while (getline(ss, s, ';'))
                {

                        if (index == 0)
                    {
                        // c_str () возвращает указатель на символьный массив, который содержит строку объекта стринг (string) в том виде, в котором она размещалась бы, во встроенном строковом типе
                        listData[index] = s.substr(lengthStation, strlen(s.c_str()));
                    }
                    else
                    {
                        listData[index] = s;
                    }
                    
                    ++index;
                }
                station.name = listData[0];
                // преобрзование строки в число
                station.countAll = stoi(listData[1]);
                station.countWork = stoi(listData[2]);
                station.effect = listData[3];
                int id = stoi(listData[4]);
                station.GetReplaceId(id);
                AllStation[id]=station;
                Station::MaxId=max(stoi(listData[4])+1, station.MaxId);
            }
        }
        fin.close();
    }
};

// чтение данных из файла о трубе
Pipe LoadPipe()
{
    ifstream fin;
    string st, s;
    Pipe pipe;
    string a1[4];
    int index = 0;
    int lengthPipe=6;
    // окрываем файл
    fin.open("data.txt");
    // проверка на открытие файла
    if (fin.is_open())
    {
        while (getline(fin, st))
        { // пока не достигнут конец файла класть очередную строку в переменную (st)
            // ss - это объект stringstream, который ссылается на строку st.
            stringstream ss(st);
            if (st.find("pipe") != string::npos)
            {
                while (getline(ss, s, ';'))
                {
                    if (index == 0)
                    {
                        // c_str () возвращает указатель на символьный массив, который содержит строку объекта стринг (string) в том виде, в котором она размещалась бы, во встроенном строковом типе
                        a1[index] = s.substr(lengthPipe, strlen(s.c_str()));
                    }
                    else
                    {
                        a1[index] = s;
                    }
                    index += 1;
                }
                pipe.name = a1[0];
                // преобрзование строки double в число
                pipe.length = atof( a1[1].c_str() );
                pipe.diameter = atof( a1[2].c_str() );
                pipe.isRepair = stoi(a1[3]);
            }
        }
        fin.close();
    }

    return pipe;
};



// сохранение данных в файл
void SaveStation(Station s, ofstream & fout){
    int id=s.GetId();
    fout << "station:" << ' ' << s.name << ";" << to_string(s.countAll) << ";" << to_string(s.countWork) << ";" << s.effect<<";"<<to_string(id)<< endl;
};
void SavePipe(const Pipe p, ofstream & fout){
    fout << "pipe:" << ' ' << p.name << ";" << to_string(p.length) << ";" << to_string(p.diameter) << ";" << to_string(p.isRepair) << endl;
}

void SaveStationPipe(MapStation & AllStation, const Pipe p, bool isStation, bool isPipe)
{
    // объект файлового потока вывода
    ofstream fout;
    // запись в файл
    fout.open("data.txt");
    if (fout.is_open())
    {
        if (isStation)
        {
             for (auto& i : AllStation) {
                cout<< i.first;
             SaveStation(i.second, fout);
             }
        }
        if (isPipe)
        {
            SavePipe(p, fout);
        }
        fout.close();
    }
};

void PrintMenu()
{
    cout << "Добавить трубу: 1" << endl
         << "Добавить КС: 2" << endl
         << "Просмотр всех объектов: 3" << endl
         << "Редактировать трубу: 4" << endl
         << "Редактировать КС: 5" << endl
         << "Сохранить: 6" << endl
         << "Загрузить: 7" << endl
         << "Выход: 0" << endl;
};

int main()
{
    MapStation AllStation;
    Station station;
    Pipe pipe;
    bool isStation = false;
    bool isPipe = false;
    while (1)
    {
        PrintMenu();
        int i = 0;
        do{
            if (cin.fail() || i>7){
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin >> i;
        } while(cin.fail() || i>7);
        switch (i)
        {
        case 1:
        {
            cin >> pipe;
            isPipe=true;
            break;
        }
        case 2:
        {
            cin >> station;
            int id=station.GetChangeId();
            AllStation[id]=station;
            isStation=true;   
            break;
        }
        case 3:
        {
            if (AllStation.size()>0)
            {
                for (auto& i : AllStation) {
                    cout<<i.second;
             }
                
            }
            if (isPipe)
            {
                cout<<pipe;
            }
            break;
        }
        case 4:
        {
            if (isPipe)
            {
                EditPipe(pipe);
                cout<< pipe;
            }
            else
            {
                cout << "Трубы не существует" << endl;
            }
            break;
        }
        case 5:
        {
            if (isStation)
            {
                EditStation(station);
                cout<<station;
            }
            else
            {
                cout << "Станции не существует" << endl;
            }
            break;
        }
        case 6:
        {
            SaveStationPipe(AllStation, pipe, isStation, isPipe);
            break;
        }
        case 7:
        {
            LoadStation(AllStation);
            pipe=LoadPipe();
            
            for (auto& i : AllStation) {
        cout << i.second;
    }
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Произошла ошибка" << endl;
        }
        }
    }
    return 0;
}


//https://iq.opengenus.org/istringstream-in-cpp/
//https://stackoverflow.com/questions/5781597/incomplete-type-is-not-allowed-stringstream
//https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
//https://favtutor.com/blogs/split-string-cpp
//https://stackoverflow.com/questions/392981/how-can-i-convert-string-to-double-in-c