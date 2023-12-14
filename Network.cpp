#pragma once
#include "Network.h"
#include <iostream>
#include <string>
#include "samples.h"
using namespace std;

void Network::AddPipe(int id, Pipe pipe){
    AllPipe[id] = pipe;
}