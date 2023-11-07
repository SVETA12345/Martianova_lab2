#ifndef STATION_H
#define STATION_H

#pragma once
#include <string>
using namespace std;
class Station
{
    int id;
public:
    static int MaxId;
    string name;
    int countAll;
    int countWork;
    string effect;

   Station();
   int GetChangeId();
   int GetId();
   void GetReplaceId(int id);
  /// ~Station();
    friend ostream& operator <<(ostream& out, const Station& s);
    friend istream& operator >>(istream& in, const Station& s);
};

#endif