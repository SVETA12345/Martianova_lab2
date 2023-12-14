#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include "Pipe.h"
#include "Pipe.cpp"
#include "Station.cpp"
#include "Station.h"
class Network
{
    unordered_map<int, Station> AllStation;
    unordered_map<int, Pipe> AllPipe;
    public:
        void AddPipe(int id, Pipe pipe);
};