#include "Station.h"
#include <iostream>
#include "samples.h"
#include <cfloat>
using namespace std;
int Station::MaxId = 0;

Station::Station()
{
    name = "Noname";
    countAll = 0;
    countWork = 0;
    effect = 0;
}

int Station::GetChangeId()
{
    id = MaxId++;
    return id;
}
int Station::GetId()
{
    return id;
}

// вывод в консоль станции
ostream &operator<<(ostream &out, const Station &s)
{
    out << "Station" << endl;
    out << "Name: " << s.name
        << "\tCountAll: " << s.countAll
        << "\tCountWork: " << s.countWork
        << "\tEffectiveness: " << s.effect
        << "\tId: " << s.id << endl;
    return out;
}

// оперотор ввода станции
istream &operator>>(istream &in, Station &station)
{

    cout << "Type name: ";
    station.name = get_str();
    cout << "Number of workshops: ";
    station.countAll = get_correct_value<int>(1, INT_MAX);
    cout << "Number of workshops in operation: ";
    station.countWork = get_correct_value<int>(1, station.countAll);
    cout << "Type effectiveness: ";
    station.effect = get_correct_value<double>(0.0, DBL_MAX);
    return in;
}

// сохранение данных в файл
void Station::SaveStation(ofstream& out) {
	if (out.is_open()) {
		out << "station"<< '\n';
		out << id << '\n';
		out << name << '\n';
		out << countAll << '\n';
		out << countWork << '\n';
		out << effect << '\n';
	}
	else {
		cout << "Îøèáêà!";
	}
}

void Station::download(ifstream& read) {
	if (read.is_open()) {
		read >> id;
        MaxId=max(MaxId, id);
		getline(read>>ws, name);
		read >> countAll;
		read >> countWork;
		read >> effect;
	}
	else {
		cout << "Îøèáêà!";
	}
}
