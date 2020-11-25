//Author: Will Owen, CSE310-Syrotiuk

#include "graph.h"
#include <iostream>
using namespace std;

/**
 * method: predVertices
 * This method outputs the predecessor vertices from the given vertex.
 * @param d
 * @param tar
 */
void predVertices(heapNodes* d,int tar)
{
    int pred,i;
    pred = d[tar].predecessor;
    if(pred == -1)
    {
        cout<<tar+1;
    }
    else
    {
        predVertices(d,pred);
        cout<<";"<<tar+1;
    }

}
/**
 * Method: writeGraph
 * This method takes the adjacency list of a graph and outputs it on the screen.
 * @param list
 * @param nVertices
 * @param nEdges
 */
void writeGraph(adjList** list,int nVertices, int nEdges)//insert into graph.cpp
{
    int k;
    adjList* temp;

    cout << nVertices << " " << nEdges << endl;
    for(k = 0; k < nVertices; k++)
    {
        temp = list[k];
        cout<<k+1<<" : ";
        while(temp != nullptr)
        {
            if(temp->next == nullptr)
            {
                cout<<"("<<temp->vertex<<"; "<<temp->weight<<")";
            }
            else
            {
                cout << "(" << temp->vertex << "; " << temp->weight << "); ";
            }
            temp = temp->next;
        }
        cout<<endl;
    }
}