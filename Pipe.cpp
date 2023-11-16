#include "Pipe.h"
#include <iostream>
#pragma once
#include <string>
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
void Pipe::GetReplaceId(int id){
    this->id=id;
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
    do
    {
        // очищает флаг ошибки
        in.clear();
        // переходит к следующей новой строке
        in.ignore(10000, '\n');
        cout << "Type name: ";
        getline(in, pipe.name);
    } while (pipe.name == "");
    do
    {
        if (in.fail())
        {
            in.clear();
            in.ignore(10000, '\n');
        }
        cout << "Type length: ";
        in >> pipe.length;
    } while (in.fail() || pipe.length < 0);
    do
    {
        in.clear();
        in.ignore(10000, '\n');
        cout << "Type diameter: ";
        in >> pipe.diameter;
    } while (in.fail() || pipe.diameter < 0);
    do
    {
        in.clear();
        in.ignore(10000, '\n');
        cout << "Type in repair (1=in repair, 0=not in repair): ";
        in >> pipe.isRepair;
    } while (in.fail());
    return in;
}
