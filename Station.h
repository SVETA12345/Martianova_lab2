#ifndef STATION_H
#define STATION_H

#pragma once
#include <string>
using namespace std;
class Station
{
    int id;
    static int MaxId;
    
public:
    double effect;
    string name;
    int countAll;
    int countWork;
   Station();
   int GetChangeId();
   int GetId();
   void SaveStation(ofstream &fout);
   void download(ifstream& read);
  /// ~Station();
    friend ostream& operator <<(ostream& out, const Station& s);
    friend istream& operator >>(istream& in, const Station& s);
};

#endif