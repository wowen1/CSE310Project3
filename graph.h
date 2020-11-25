//Author: Will Owen, CSE310-Syrotiuk

#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H
#include "heap.h"
struct adjList //Struct for an singly linked list
{
    int vertex;
    int weight;
    adjList* next;
};

    void predVertices(heapNodes* d,int tar);
    void writeGraph(adjList** list,int nVertices, int nEdges);



#endif //PROJECT3_GRAPH_H
