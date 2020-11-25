//Author: Will Owen, CSE310-Syrotiuk

#ifndef PROJECT3_HEAP_H
#define PROJECT3_HEAP_H
struct heapNodes //Struct for a heap node
{
    int vertex;
    int predecessor;
    int distance;
};

class heap
{
public:
    heapNodes* nodes;
    int heapSize;
    int size;

    heap(int num);
    void display();
    int hasNode(int key);
    int isEmpty();
    void insert(heapNodes key);
    int getParent(int i);
    void decreaseKey(int val,int index);
    heapNodes extractMin();
    void minHeapSort();
    void heapify(int rootIndex);
};


#endif //PROJECT3_HEAP_H
