#pragma once
#include <string>
#include <string>
using namespace std;
class Pipe
{
    int id;
    public:
        static int MaxId;
        string name;
        double length;
        double diameter;
        bool isRepair;
        Pipe();
        int GetChangeId();
        int GetId();
        void GetReplaceId(int id);
  /// ~Station();
        friend ostream& operator <<(ostream& out, const Pipe& p);
        friend istream& operator >>(istream& in, const Pipe& p);
};