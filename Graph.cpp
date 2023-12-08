#pragma once
#include "Graph.h"
#include <iostream>
#include <string>
#include "samples.h"
using namespace std;

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
  
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
  
// Рекурсивная функция, используемая topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[], 
                                stack<int> &Stack)
{
    // Помечаем текущий узел как посещенный
    visited[v] = true;
  
    // Рекурсивно вызываем функцию для всех смежных вершин
    list<int> i;

    for (auto &i : adj[v])
        //if (!visited[&i])
            //topologicalSortUtil(&i, visited, Stack);
  
    // Добавляем текущую вершину в стек с результатом
    Stack.push(v);
}
  
// Функция для поиска топологической сортировки. 
// Рекурсивно использует topologicalSortUtil()
void Graph::topologicalSort()
{
    stack<int> Stack;
  
    // Помечаем все вершины как непосещенные
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
  
    // Вызываем рекурсивную вспомогательную функцию 
    // для поиска топологической сортировки для каждой вершины
    for (int i = 0; i < V; i++)
      if (visited[i] == false)
        topologicalSortUtil(i, visited, Stack);
  
    // Выводим содержимое стека
    while (Stack.empty() == false)
    {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}