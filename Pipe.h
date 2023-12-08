#pragma once
#include <string>
#include <fstream>
using namespace std;
class Pipe
{
    int id;
        double diameter;
        double length;
        static int MaxId;
    public:
        string name;
        bool isRepair;
        Pipe();
        int GetChangeId();
        int GetId();
        double GetDiameter();
        string GetName();
        void download(ifstream& read);
  /// ~Station();
        friend ostream& operator <<(ostream& out, const Pipe& p);
        friend istream& operator >>(istream& in, Pipe& p);
        void SavePipe(ofstream &fout);      
};