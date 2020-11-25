//Author: Will Owen, CSE310-Syrotiuk

#include "heap.h"
#include <iostream>
using namespace std;

//Constructor for heap class
heap::heap(int num)
{
        heapSize = 0;
        size = num;
        nodes = new heapNodes[size];
}
/**
 * Method: display()
 * This method displays the heap on the screen.
 */
void heap::display()
{
    int i;
    for(i=0;i<heapSize;i++)
    {
        cout<<"Nodes["<<i<<"]="<<nodes[i].distance<<".  V: "<<nodes[i].vertex<<endl;

    }
}
/**
 * Method: hasNode
 * This method checks the heap for the given key
 * @param key
 * @return
 */
int heap::hasNode(int key)
{
    int i, contains;
    contains = 0;//0=does not contain
    for(i=0; i<heapSize; i++)
    {
        if(nodes[i].vertex = key)
        {
            contains = 1;//1 = DOES contain
        }
    }
    return contains;
}
/**
 * Method: isEmpty
 * This method checks if the heap is empty.
 * @return
 */
int heap::isEmpty()
{
    int flag;
    if(heapSize == 0)
    {
        flag = 1; //1 = empty
    }
    else
    {
        flag = 0;//0 = NOT empty
    }
    return flag;
}
/**
 * Method: insert
 * This method inserts a node into the heap and then maintains the heap properties.
 * @param key
 */
void heap::insert(heapNodes key)
{
    int index;
    heapNodes temp;
    heapSize = heapSize + 1;
    index = heapSize - 1;
    nodes[index].distance = key.distance;
    nodes[index].vertex = key.vertex;
    nodes[index].predecessor = key.predecessor;

    while(index != 0 && nodes[getParent(index)].distance > nodes[index].distance)
    {
        temp = nodes[getParent(index)];
        nodes[getParent(index)] = nodes[index];
        nodes[index] = temp;
        index = getParent(index);
    }
}
/**
 * Method: getParent
 * This method returns the parent node of a node.
 * @param i
 * @return
 */
int heap::getParent(int i)
{
    int parent;
    parent = (i-1)/2;
    return parent;
}
/**
 * Method: decreaseKey
 * This method decreases the key value of a given node then maintains the heap properties.
 * @param val
 * @param index
 */
void heap::decreaseKey(int val,int index)
{
    int i,j;
    for(j=0;j<heapSize;j++)
    {
        if(nodes[j].vertex == index)
        {
            nodes[j].distance = val;
            i = j;
        }
    }

    heapNodes temp;

    while(i != 0 && nodes[getParent(i)].distance > nodes[i].distance)
    {
        temp = nodes[getParent(i)];
        nodes[getParent(i)] =  nodes[i];
        nodes[i]=temp;
        i = getParent(i);
    }
}
/**
 * Method: extractMin
 * This method extracts the minimum value from the heap then maintains the heap properties.
 * @return
 */
heapNodes heap::extractMin()
{
    heapNodes min;
    min = nodes[0];
    nodes[0] = nodes[heapSize-1];
    heapSize = heapSize - 1;
    heapify(0);

    return min;
}
/**
 * Method: minHeapSort()
 * (UNUSED)
 * This method sorts a given array into a min heap.
 */
void heap::minHeapSort()
{
    int i;

    for(i = (heapSize / 2); i >= 0; i--)
    {
        heapify(i);
    }

}
/**
 * Method: heapify
 * This method maintains the heap property.
 * @param rootIndex
 */
void heap::heapify(int rootIndex)
{
    int left, right;
    int minimum = rootIndex;
    heapNodes temp;

    left = (2 * rootIndex) + 1;
    right = (2 * rootIndex) + 2;

    if(left < heapSize && nodes[left].distance < nodes[minimum].distance)
    {
        minimum = left;
    }

    if(right < heapSize && nodes[right].distance < nodes[minimum].distance)
    {
        minimum = right;
    }

    if(minimum != rootIndex)
    {
        temp = nodes[rootIndex];
        nodes[rootIndex] = nodes[minimum];
        nodes[minimum] = temp;
        heapify(minimum);
    }

}


