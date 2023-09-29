#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
struct Pipe{
    string name;
    double length;
    double diameter;
    string sign;
};

struct Station
{
    string name;
    int countAll;
    int countWork;
    string effect;
};
Pipe InputPipe(){
    Pipe pipe;
    cout << "Type name: ";
    cin >> pipe.name;
    cout << "Type length: ";
    cin >> pipe.length;
    cout << "Type diameter: ";
    cin >> pipe.diameter;
    cout << "Type sign: ";
    cin >> pipe.sign;
    return pipe;
};

//чтение данных из файла о станции
Station LoadStation(){
    ifstream fin;
    // окрываем файл для чтения
    fin.open("data.txt");
    Station station;
    fin >> station.name;
    fin >> station.countAll;
    fin >> station.countWork;
    fin >> station.effect;
    fin.close();
    return station;
};

Station InputStation(){
    Station station;
    cout << "Type name: ";
    cin >> station.name;
    cout << "Number of workshops: ";
    cin >> station.countAll;
    cout << "Number of workshops in operation: ";
    cin >> station.countWork;
    cout << "Type effectiveness: ";
    cin >> station.effect;
    return station;
};

// обновление значения трубы, передача данных по ссылке
void EditPipe(Pipe & pipe){

}
void PrintPipe(const Pipe& p){
    cout << "Name: " << p.name
    << "\tLength: " << p.length
    << "\tDiameter: " << p.diameter
    << "\tSign: " << p.sign<< endl;
};

void PrintStation(const Station& s){
    cout << "Name: " << s.name
    << "\tCountAll: " << s.countAll
    << "\tCountWork: " << s.countWork
    << "\tEffectiveness: " << s.effect<< endl;
};

//сохранение данных о станции в файл
void SaveStation(const Station& s){
    //объект файлового потока вывода
    ofstream fout;
    //запись в файл
    fout.open("data.txt");
    fout  << s.name << endl
    << s.countAll <<endl
    << s.countWork << endl
    << s.effect<< endl;
    fout.close();
};
int main()
{
    Pipe pipe = InputPipe();
    //PrintPipe(pipe);
    //Station station=InputStation();
    //PrintStation(station);
    //SaveStation(station);
    PrintStation(LoadStation());
    return 0;
}