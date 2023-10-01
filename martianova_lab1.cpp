#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;
struct Pipe
{
    string name;
    double length;
    double diameter;
    bool isRepair;
};

struct Station
{
    string name;
    int countAll;
    int countWork;
    string effect;
};
// функция ввода трубы
Pipe InputPipe(bool &isPipe)
{
    Pipe pipe;
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
    } while (cin.fail());
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type diameter: ";
        cin >> pipe.diameter;
    } while (cin.fail());
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type in repair (1=in repair, 0=not in repair): ";
        cin >> pipe.isRepair;
    } while (cin.fail());
    isPipe = true;
    return pipe;
};

// редактирование трубы
void EditPipe(Pipe &pipe)
{
    if (pipe.isRepair == 1)
    {
        pipe.isRepair = 0;
    }
    else
    {
        pipe.isRepair = 1;
    }
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
    } while (cin.fail());
};

// вывод трубы в консоль
void PrintPipe(const Pipe &p)
{
    cout << "Pipe" << endl;
    cout << "Name: " << p.name
         << "\tLength: " << p.length
         << "\tDiameter: " << p.diameter
         << "\tIsRepair: " << p.isRepair << endl;
};

// чтение данных из файла о станции
Station LoadStation()
{
    ifstream fin;
    string st, s;
    Station station;
    string listData[4];
    int index = 0;
    // окрываем файл
    fin.open("data.txt");
    // проверка на открытие файла
    if (fin.is_open())
    {
        while (getline(fin, st))
        { // пока не достигнут конец файла класть очередную строку в переменную (st)
            // ss - это объект stringstream, который ссылается на строку st.
            stringstream ss(st);
            if (st.find("station") != string::npos)
            {
                while (getline(ss, s, ','))
                {
                    if (index == 0)
                    {
                        // c_str () возвращает указатель на символьный массив, который содержит строку объекта стринг (string) в том виде, в котором она размещалась бы, во встроенном строковом типе
                        listData[index] = s.substr(9, strlen(s.c_str()));
                    }
                    else
                    {
                        listData[index] = s;
                    }
                    index += 1;
                }
                station.name = listData[0];
                // преобрзование строки в число
                station.countAll = stoi(listData[1]);
                station.countWork = stoi(listData[2]);
                station.effect = listData[3];
            }
        }
        fin.close();
    }

    return station;
};

// чтение данных из файла о трубе
Pipe LoadPipe()
{
    ifstream fin;
    string st, s;
    Pipe pipe;
    string a1[4];
    int index = 0;
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
                while (getline(ss, s, ','))
                {
                    if (index == 0)
                    {
                        // c_str () возвращает указатель на символьный массив, который содержит строку объекта стринг (string) в том виде, в котором она размещалась бы, во встроенном строковом типе
                        a1[index] = s.substr(6, strlen(s.c_str()));
                    }
                    else
                    {
                        a1[index] = s;
                    }
                    index += 1;
                }
                pipe.name = a1[0];
                // преобрзование строки в число
                pipe.length = stoi(a1[1]);
                pipe.diameter = stoi(a1[2]);
                pipe.isRepair = stoi(a1[3]);
            }
        }
        fin.close();
    }

    return pipe;
};
// функция ввода станции
Station InputStation(bool &isStation)
{
    Station station;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type name: ";
        getline(cin, station.name);
    } while (station.name == "");
    do
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Number of workshops: ";
        cin >> station.countAll;
    } while (cin.fail());
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Number of workshops in operation: ";
        cin >> station.countWork;
    } while (cin.fail());
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type effectiveness: ";
        cin >> station.effect;
    } while (cin.fail());
    isStation = true;
    return station;
};

// обновление значения станции, передача данных по ссылке
void PrintStation(const Station &s)
{
    cout << "Station" << endl;
    cout << "Name: " << s.name
         << "\tCountAll: " << s.countAll
         << "\tCountWork: " << s.countWork
         << "\tEffectiveness: " << s.effect << endl;
};

// сохранение данных в файл
void SaveStationPipe(const Station &s, const Pipe p, bool isStation, bool isPipe)
{
    // объект файлового потока вывода
    ofstream fout;
    // запись в файл
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        if (isStation)
        {
            fout << "station:" << ' ' << s.name << "," << to_string(s.countAll) << "," << to_string(s.countWork) << "," << s.effect << endl;
        }
        if (isPipe)
        {
            fout << "pipe:" << ' ' << p.name << "," << to_string(p.length) << "," << to_string(p.diameter) << "," << to_string(p.isRepair) << endl;
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
    Station station;
    Pipe pipe;
    bool isStation = false;
    bool isPipe = false;
    while (1)
    {
        PrintMenu();
        int i = 0;
        cin >> i;
        switch (i)
        {
        case 1:
        {
            pipe = InputPipe(isPipe);
            break;
        }
        case 2:
        {
            station = InputStation(isStation);
            break;
        }
        case 3:
        {
            if (isStation)
            {
                PrintStation(station);
            }
            if (isPipe)
            {
                PrintPipe(pipe);
            }
            break;
        }
        case 4:
        {
            if (isPipe)
            {
                EditPipe(pipe);
                PrintPipe(pipe);
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
                PrintStation(station);
            }
            else
            {
                cout << "Станции не существует" << endl;
            }
            break;
        }
        case 6:
        {
            SaveStationPipe(station, pipe, isStation, isPipe);
            break;
        }
        case 7:
        {
            PrintStation(LoadStation());
            PrintPipe(LoadPipe());
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