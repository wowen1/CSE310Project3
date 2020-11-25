//Author: Will Owen, CSE310-Syrotiuk

#include "util.h"
#include <iostream>

/**
 * Method: adjListInsertion
 * This method inserts a link into a singly linked list.
 * It creates a link using the parameters then inserts in the front of the list
 * @param list
 * @param vertex1
 * @param vertex2
 * @param weight
 */
void adjListInsertion (adjList** list,int vertex1,int vertex2, int weight)
{
    adjList* newEntry = new adjList;
    newEntry->vertex = vertex2;
    newEntry->weight = weight;
    if(list[vertex1 - 1] == nullptr)
    {
        newEntry->next = nullptr;
        list[vertex1 - 1] = newEntry;
    }
    else
    {
        newEntry->next = list[vertex1 - 1];
        list[vertex1 -1] = newEntry;
    }
}