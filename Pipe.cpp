#pragma once
#include "Pipe.h"
#include <iostream>
#include <string>
#include "samples.h"
using namespace std;

int Pipe::MaxId=0;
Pipe::Pipe()
{
    name="Noname";
    length=0;
    diameter=0;
    isRepair=false;
}

int Pipe::GetChangeId(){
    id=MaxId++;
    return id;
}
int Pipe::GetId(){
    return id;
}
//вывод в консоль трубы
ostream& operator << (ostream& out, const Pipe& p){
    out << "Pipe" << endl;
    out << "Name: " << p.name
         << "\tLength: " << p.length
         << "\tDiameter: " << p.diameter
         << "\tIsRepair: " << p.isRepair
         <<"\tId: "<<p.id<< endl;
    return out;
}

// оперотор ввода трубы
istream& operator >> (istream& in, Pipe& pipe){
    cout << "Type name: ";
	pipe.name = get_str();
	cout << "Type length: ";
	pipe.length = get_correct_value<double>(1, INT_MAX);
	cout << "Type diameter: ";
	pipe.diameter = get_correct_value<double>(1, INT_MAX);
	cout << "Type in repair (1=in repair, 0=not in repair): ";
	pipe.isRepair = get_correct_value<bool>(0, 1);
    return in;
}

void Pipe::download(ifstream& read) {
	if (read.is_open()) {
		read >> id;
        MaxId=max(MaxId, id);
	    getline(read>>ws, name);
		read >> length;
		read >> diameter;
		read >> isRepair;

	}
	else {
		cout << "Îøèáêà!";
	}
}
void Pipe::SavePipe(ofstream& out) {
	if (out.is_open()) {
		out << "pipe" << '\n';
		out << id << '\n';
		out << name << '\n';
		out << length << '\n';
		out << diameter << '\n';
		out << isRepair << '\n';
	}
	else {
		cout << "Îøèáêà!";
	}
}

string Pipe::GetName(){
    return name;
}