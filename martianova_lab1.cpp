#include <iostream>
#include <vector>
#include <string>

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
void PrintPipe(Pipe p){
    cout << "Name: " << p.name
    << "\tLength: " << p.length
    << "\tDiameter: " << p.diameter
    << "\tSign: " << p.sign<< endl;
};
void PrintStation(Station s){
    cout << "Name: " << s.name
    << "\tCountAll: " << s.countAll
    << "\tCountWork: " << s.countWork
    << "\tEffectiveness: " << s.effect<< endl;
};
int main()
{
    Pipe pipe = InputPipe();
    PrintPipe(pipe);
    Station station=InputStation();
    PrintStation(station);
    return 0;
}