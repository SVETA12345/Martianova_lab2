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
#include "Pipe.h"
#include "Pipe.cpp"

using namespace std;
typedef unordered_map<int, Station> MapStation;
typedef unordered_map<int, Pipe> MapPipe;

// проверка, является ли строка числом
bool isDigit(string line)
{
    char *p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}
// редактирование трубы
void EditPipe(MapPipe &AllPipe, ofstream &fin)
{
    int id;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите id станции: ";
        cin >> id;
        fin<<id<<endl;
    } while (cin.fail() || AllPipe.find(id) == AllPipe.end());
    AllPipe[id].isRepair = !AllPipe[id].isRepair;
};
//редактирование всех труб
void EditAllPipe(MapPipe &AllPipe)
{
    for (auto &i : AllPipe)
    {
        i.second.isRepair = !i.second.isRepair;
    }
    
};
// редактирование списка труб
void EditListPipes(MapPipe &AllPipe, ofstream &fin){
    string listId;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите id через пробел: ";
        getline(cin, listId);
        fin<<listId<<endl;
    } while (listId == "");
    // разбиение строки на пробелы
    stringstream ss(listId);
    string id;
    while (ss >> id)
    {
        if (isDigit(id) && to_string(stoi(id))==id && AllPipe.find(stoi(id)) != AllPipe.end())
        {
            AllPipe[stoi(id)].isRepair = !AllPipe[stoi(id)].isRepair;
        }
    }
};
// редактирование станции
void EditStation(MapStation &AllStation, ofstream &fin)
{
    int id = 0;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите id станции: ";
        cin >> id;
        fin<<id<<endl;
    } while (cin.fail() || AllStation.find(id) == AllStation.end());
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Number of workshops in operation: ";
        cin >> AllStation[id].countWork;
        fin<<AllStation[id].countWork<<endl;
    } while (cin.fail() || AllStation[id].countWork < 0 || AllStation[id].countWork > AllStation[id].countAll);
};

// удаление станции
void DeleteStation(MapStation &AllStation, ofstream &fin)
{
    int id;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите id станции: ";
        cin >> id;
        fin<<id<<endl;
    } while (cin.fail() || AllStation.find(id) == AllStation.end());
    AllStation.erase(id);
};
// фильтрация станции по имени
unordered_map<int, Station> FindStationByName(MapStation AllStation, string name = "Unknow")
{
    MapStation res;
    for (auto &i : AllStation)
    {
        if (i.second.name == name)
        {
            res[i.first] = i.second;
        }
    }
    return res;
}
// фильтрация станции по цехам
unordered_map<int, Station> FindStationByWorkShop(MapStation AllStation, float per)
{
    MapStation res;
    float item;
    for (auto &i : AllStation)
    {
        item=((i.second.countAll)/100)*(i.second.countAll-i.second.countWork);
        if (item == per)
        {
            res[i.first] = i.second;
        }
    }
    return res;
}
// фильтрация трубы по признаку в ремонте
unordered_map<int, Pipe> FindPipeByIsRepair(MapPipe AllPipe, bool isRepair)
{
    MapPipe res;
    int i = 0;
    for (auto &i : AllPipe)
    {
        if (i.second.isRepair == isRepair)
        {
            res[i.first] = i.second;
        }
    }
    return res;
}

// фильтрация трубы по названию
unordered_map<int, Pipe> FindPipeByName(MapPipe AllPipe, string name)
{
    MapPipe res;
    int i = 0;
    for (auto &i : AllPipe)
    {
        if (i.second.name == name)
        {
            res[i.first] = i.second;
        }
    }
    return res;
}
// удаление трубы
void DeletePipe(MapPipe &AllPipe, ofstream &fin)
{
    int id;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите id трубу: ";
        cin >> id;
        fin<<id<<endl;
    } while (cin.fail() || AllPipe.find(id) == AllPipe.end());
    AllPipe.erase(id);
};

// удаление списка труб
void DeleteListPipes(MapPipe &AllPipe, ofstream &fin)
{
    string listId;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите id через пробел: ";
        getline(cin, listId);
        fin<<listId<<endl;
    } while (listId == "");
    // разбиение строки на пробелы
    stringstream ss(listId);
    string id;
    while (ss >> id)
    {
        if (isDigit(id) && to_string(stoi(id))==id && AllPipe.find(stoi(id)) != AllPipe.end())
        {
            AllPipe.erase(stoi(id));
        }
    }
}
// чтение данных из файла о станции
auto LoadStation(unordered_map<int, Station> &AllStation, string nameFile)
{

    ifstream fin;
    string st, s;
    Station station;
    int indexLine = 0;
    int lengthStation = 9;
    string listData[5];
    // окрываем файл
    fin.open(nameFile+".txt");
    // проверка на открытие файла
    if (fin.is_open())
    {
        while (getline(fin, st))
        { // пока не достигнут конец файла класть очередную строку в переменную (st)
            // ss - это объект stringstream, который ссылается на строку st.
            stringstream ss(st);
            if (st.find("station") != string::npos)
            {
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
                    AllStation[id] = station;
                    Station::MaxId = max(stoi(listData[4]) + 1, station.MaxId);
                }
            }
        }
        fin.close();
    }
};

// чтение данных из файла о трубе
auto LoadPipe(unordered_map<int, Pipe> &AllPipe, string nameFile)
{
    ifstream fin;
    string st, s;
    Pipe pipe;
    string a1[5];

    int lengthPipe = 6;
    // окрываем файл
    fin.open(nameFile+".txt");
    // проверка на открытие файла
    if (fin.is_open())
    {
        while (getline(fin, st))
        { // пока не достигнут конец файла класть очередную строку в переменную (st)
            // ss - это объект stringstream, который ссылается на строку st.
            stringstream ss(st);
            if (st.find("pipe") != string::npos)
            {
                int index = 0;
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
                pipe.length = atof(a1[1].c_str());
                pipe.diameter = atof(a1[2].c_str());
                pipe.isRepair = stoi(a1[3]);
                int id = stoi(a1[4]);
                pipe.GetReplaceId(id);
                AllPipe[id] = pipe;
                Pipe::MaxId = max(stoi(a1[4]) + 1, pipe.MaxId);
            }
        }
        fin.close();
    }

    return pipe;
};

// сохранение данных в файл
void SaveStation(Station s, ofstream &fout)
{
    int id = s.GetId();
    fout << "station:" << ' ' << s.name << ";" << to_string(s.countAll) << ";" << to_string(s.countWork) << ";" << s.effect << ";" << to_string(id) << endl;
};
void SavePipe(Pipe p, ofstream &fout)
{
    int id = p.GetId();
    fout << "pipe:" << ' ' << p.name << ";" << to_string(p.length) << ";" << to_string(p.diameter) << ";" << to_string(p.isRepair) << ";" << to_string(id) << endl;
}

void SaveStationPipe(MapStation &AllStation, MapPipe &AllPipe, bool isStation, bool isPipe, string nameFile)
{
    // объект файлового потока вывода
    ofstream fout;
    // запись в файл
    fout.open(nameFile+".txt");
    if (fout.is_open())
    {
        if (isStation)
        {
            for (auto &i : AllStation)
            {
                SaveStation(i.second, fout);
            }
        }
        if (isPipe)
        {
            for (auto &i : AllPipe)
            {
                SavePipe(i.second, fout);
            }
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
         << "Удалить станцию по id: 8" << endl
         << "Удалить трубу по id: 9" << endl
         << "Фильтрация станций по названию: 10" << endl
         << "Фильтрация труб по признаку в ремонте: 11" << endl
         << "Фильтрация труб по названию: 12" << endl
         << "Фильтрация станций по проценту незадействованных цехов: 13" << endl
         << "Пакетное удаление труб: 14" << endl
         << "Пакетное редактирование труб по признаку в ремонте: 15" << endl
         << "Выход: 0" << endl;
};

int main()
{
    ofstream fin;
    fin.open("log.txt");
    MapStation AllStation;
    MapPipe AllPipe;
    Station station;
    Pipe pipe;
    bool isStation = false;
    bool isPipe = false;
    while (1)
    {
        PrintMenu();
        int i = 0;
        do
        {
            if (cin.fail() || i > 8)
            {
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin >> i;
            fin << i<<endl;
        } while (cin.fail() || i > 15);
        switch (i)
        {
        case 1:
        {
            cin >> pipe;
            fin << pipe<<endl;
            int id = pipe.GetChangeId();
            AllPipe[id] = pipe;
            isPipe = true;
            break;
        }
        case 2:
        {
            cin >> station;
            fin << station<<endl;
            int id = station.GetChangeId();
            AllStation[id] = station;
            isStation = true;
            break;
        }
        case 3:
        {
            if (AllStation.size() > 0)
            {
                for (auto &i : AllStation)
                {
                    cout << i.second;
                }
            }
            if (AllPipe.size() > 0)
            {
                for (auto &i : AllPipe)
                {
                    cout << i.second;
                }
            }
            break;
        }
        case 4:
        {
            if (AllPipe.size() > 0)
            {
                EditPipe(AllPipe, fin);
            }
            else
            {
                cout << "Трубы не существует" << endl;
            }
            break;
        }
        case 5:
        {
            if (AllStation.size() > 0)
            {
                EditStation(AllStation, fin);
            }
            else
            {
                cout << "Станции не существует" << endl;
            }
            break;
        }
        case 6:
        {
            string nameFile;
            do
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Введите название файла: ";
                getline(cin, nameFile);
                fin<<nameFile<<endl;
            } while (nameFile == "");
            SaveStationPipe(AllStation, AllPipe, isStation, isPipe, nameFile);
            break;
        }
        case 7:
        {
            string nameFile;
            do
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Введите название файла: ";
                getline(cin, nameFile);
                fin<<nameFile<<endl;
            } while (nameFile == "");
            LoadStation(AllStation, nameFile);
            LoadPipe(AllPipe, nameFile);

            for (auto &i : AllStation)
            {
                cout << i.second;
            }
            for (auto &i : AllPipe)
            {
                cout << i.second;
            }
            break;
        }
        case 8:
        {
            DeleteStation(AllStation, fin);
            break;
        }
        case 9:
        {
            DeletePipe(AllPipe, fin);
            break;
        }
        case 10:
        {
            MapStation FilterNameStation;
            string name;
            do
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Type name: ";
                getline(cin, name);
                fin<<name<<endl;
            } while (name == "");
            FilterNameStation = FindStationByName(AllStation, name);
            if (FilterNameStation.size() == 0)
            {
                cout << "Такой станции не существует" << endl;
            }
            else
            {
                for (auto &i : FilterNameStation)
                {
                    cout << i.second;
                }
            }

            break;
        }
        case 11:
        {
            MapPipe FilterIsRepairPipe;
            bool isRepair;
            do
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Type in repair (1=in repair, 0=not in repair): ";
                cin >> isRepair;
                fin<<isRepair<<endl;
            } while (cin.fail());
            FilterIsRepairPipe = FindPipeByIsRepair(AllPipe, isRepair);
            if (FilterIsRepairPipe.size() == 0)
            {
                cout << "Такой трубы не существует" << endl;
            }
            else
            {
                for (auto &i : FilterIsRepairPipe)
                {
                    cout << i.second;
                }
            }

            break;
        }
        case 12:
        {
            MapPipe FilterNamePipe;
            string name;
            do
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Type name: ";
                getline(cin, name);
                fin<<name<<endl;
            } while (name == "");
            FilterNamePipe = FindPipeByName(AllPipe, name);
            if (FilterNamePipe.size() == 0)
            {
                cout << "Такой трубы не существует" << endl;
            }
            else
            {
                for (auto &i : FilterNamePipe)
                {
                    cout << i.second;
                }
            }

            break;
        }
        case 13:
        {
            MapStation FilterWorkShopStation;
            float percent;
        do
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Введите процент незадействованных цехов: ";
                cin>>percent;
                fin<<percent<<endl;
            } while (cin.fail());
            FilterWorkShopStation=FindStationByWorkShop(AllStation,percent);
            if (FilterWorkShopStation.size() == 0)
            {
                cout << "Такой станции не существует" << endl;
            }
            else
            {
                for (auto &i : FilterWorkShopStation)
                {
                    cout << i.second;
                }
            }
            break;
        }
        case 14:
        {
            int num;
            do
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Введите 1 или 2 (1 - удаление всех труб; 2 - удаление труб по id): ";
                cin >> num;
                fin<<num<<endl;
            } while (num != 1 && num != 2 || cin.fail());
            if (num == 1)
            {
                AllPipe.clear();
                cout << "Все трубы удалены" << endl;
            }
            else
            {
                DeleteListPipes(AllPipe, fin);
                cout << "Оставшиеся трубы" << endl;
                if (AllPipe.size() > 0)
                {
                    for (auto &i : AllPipe)
                    {
                        cout << i.second;
                    }
                }
            }
            break;
        }
        case 15:
        {
            int num;
            do
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Введите 1 или 2 (1 - редактирование всех труб; 2 - редактирование труб по id): ";
                cin >> num;
                fin<<num<<endl;
            } while (num != 1 && num != 2 || cin.fail());
            if (num == 1)
            {
                EditAllPipe(AllPipe);
                cout << "Все трубы отредактированы" << endl;
            }
            else
            {
                EditListPipes(AllPipe, fin);
                if (AllPipe.size() > 0)
                {
                    for (auto &i : AllPipe)
                    {
                        cout << i.second;
                    }
                }
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
    fin.close();
    return 0;
}

// https://iq.opengenus.org/istringstream-in-cpp/
// https://stackoverflow.com/questions/5781597/incomplete-type-is-not-allowed-stringstream
// https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
// https://favtutor.com/blogs/split-string-cpp
// https://stackoverflow.com/questions/392981/how-can-i-convert-string-to-double-in-c