#pragma once
#include <string>
#include<iostream>
#include <list>
#include <stack>
using namespace std;
class Graph
{
    int V;	// Количество вершин
  
    //  Указатель на массив, содержащий список смежности
    list<int> *adj;
    // Функция, используемая topologicalSort
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
    public:
    Graph(int V);   // Конструктор
  
     // Функция для добавления ребра в граф
    void addEdge(int v, int w);
  
    // Выводит топологическую сортировку графа
    void topologicalSort();
};