#include "Station.h"
#include <iostream>
using namespace std;
int Station::MaxId=0;
Station::Station()
{
    name="Noname";
    countAll=0;
    countWork=0;
    effect="0";
}

int Station::GetChangeId(){
    id=MaxId++;
    return id;
}
int Station::GetId(){
    return id;
}
void Station::GetReplaceId(int id){
    this->id=id;
}
//вывод в консоль станции
ostream& operator << (ostream& out, const Station& s){
    out << "Station" << endl;
    out << "Name: " << s.name
         << "\tCountAll: " << s.countAll
         << "\tCountWork: " << s.countWork
         << "\tEffectiveness: " << s.effect 
         <<"\tId: "<<s.id<<endl;
    return out;
}

// оперотор ввода станции
istream& operator >> (istream& in, Station& station){
    do
    {
        in.clear();
        in.ignore(10000, '\n');
        cout << "Type name: ";
        getline(in, station.name);
    } while (station.name == "");
    do
    {
        if (in.fail())
        {
            in.clear();
            in.ignore(10000, '\n');
        }
        cout << "Number of workshops: ";
        in >> station.countAll;
    } while (in.fail());
    do
    {
        in.clear();
        in.ignore(10000, '\n');
        cout << "Number of workshops in operation: ";
        in >> station.countWork;
    } while (in.fail());
    do
    {
        in.clear();
        in.ignore(10000, '\n');
      cout << "Type effectiveness: ";
        in >> station.effect;
    } while (in.fail());
    return in;
}

