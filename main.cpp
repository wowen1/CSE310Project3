//Will Owen Project3 CSE310-Syrotiuk
#include <iostream>
#include <string>
#include "util.h"
#include "graph.h"
#include "heap.h"
#include "main.h"

using namespace std;

int main(int argc, char *argv[])
{
    string val,s1,s2,s3;
    string del = " ";
    int delLoc,i,u,v,w,src,targ,flag,error;
    int num,nVertices,nEdges;

    getline(cin,val);  //reads number of vertices and edges as a string

    delLoc = val.find(del);
    s1 = val.substr(0,delLoc);
    nVertices =  stoi(s1,nullptr,10); //cuts the string at the first space to convert the value to an int for nVertices.

    s1 = val.substr(delLoc+1,val.length());
    nEdges = stoi(s1,nullptr,10);//converts the second half into an int for nEdges

    adjList** adjlist = new adjList*[nVertices]; //dynamically allocates an array of adjList pointers.

    for(i = 0; i < nEdges; i++)
    {
        getline(cin,val);

        delLoc = val.find(del);
        s1 = val.substr(0,delLoc);
        u = stoi(s1,nullptr,10);  //parses the first vertex value

        s1 = val.substr(delLoc+1, val.length());
        delLoc = s1.find(del);
        s2 = s1.substr(0,delLoc);
        v = stoi(s2,nullptr,10); //parses the second vertex value

        s1 = s1.substr(delLoc+1,val.length());
        w = stoi(s1,nullptr,10); //parses the weight value

        adjListInsertion(adjlist,u,v,w); //inserts it into the adjList.

    }
    do
    {
        getline(cin, val);

        if (val == "stop")
        {
            cout << "Command: stop" << endl;
        }
        else if (val == "write")
        {
            cout << "Command: write" << endl;
            writeGraph(adjlist,nVertices,nEdges);
        }
        else
        {
            delLoc = val.find(del);
            s1 = val.substr(0,delLoc);
            if(s1 == "find")
            {
                s2 = val.substr(delLoc+1,val.length());  //parses the values of the find command
                delLoc = s2.find(del);
                s1 = s2.substr(0,delLoc);
                src = stoi(s1,nullptr,10);
                s3 = s2.substr(delLoc+1,val.length());
                delLoc = s3.find(del);
                s1 = s3.substr(0,delLoc);
                targ = stoi(s1,nullptr,10);
                s2 = s3.substr(delLoc+1,val.length());
                flag = stoi(s2,nullptr,10);         //end of parse

                cout<<"Command: find "<<src<<" "<<targ<<" "<<flag<<endl;
                error = 0;

                if(((src) < 1||(src)>nVertices) || ((targ)<1 || (targ)>nVertices)) //checks for valid nodes
                {
                    cout<<"Error: one or more invalid nodes"<<endl;
                    error = 1;
                }
                if(flag!= 0 && flag != 1) //checks for valid flags
                {
                    cout<<"Error: invalid flag value"<<endl;
                    error = 1;
                }
                if(error == 0) //if no errors, proceed
                {

                    heapNodes* distances; //array of heapnodes to hold vertices and shortest distances.

                    distances = dijkstra(adjlist,src-1,nVertices);
                    if(distances[targ-1].distance == 9001)//check if node is unreachable.
                    {
                        cout<<"Error: node "<<targ<<" not reachable from node "<<src<<endl;
                    }
                    else
                    {
                        if (flag == 1)
                        {
                            cout << "Length: " << distances[targ - 1].distance << endl;
                        } else
                        {
                            cout << "Path: ";
                            predVertices(distances, targ - 1);
                            cout << endl;
                        }
                    }
                }

            }

        }
    }while(val != "stop");

    return 0;
}
/**
 * Method: dijkstra
 *      Implementation of dijkstra's algorithm to find the shortest path.
 * @param list
 * @param source
 * @param nVertices
 * @return d (array of heapnodes containing shortest distance to each node)
 */
heapNodes* dijkstra(adjList** list, int source,int nVertices)
{
    heapNodes* d = new heapNodes[nVertices];
    int visited[nVertices];


    heapNodes v;
    int i,sum,j;
    adjList* temp;

    heap q(nVertices);
    d[source].distance = 0;
    d[source].vertex = source;
    d[source].predecessor = -1;

    for(i=0;i<nVertices;i++)
    {
        visited[i] = 0;
        if(i != source)
        {

            d[i].distance = 9001;
            d[i].vertex = i;
            d[i].predecessor = -1;
        }
        q.insert(d[i]);
    }
    while(q.isEmpty() == 0)
    {
        v = q.extractMin();

        j = v.vertex;
        visited[j] = 1;

        temp = list[j];
        while(temp != nullptr)
        {

            if(visited[temp->vertex-1] == 0)
            {
                sum = v.distance + temp->weight;

                if(sum < d[temp->vertex-1].distance)
                {
                    q.decreaseKey(sum,temp->vertex-1);
                    d[temp->vertex-1].distance = sum;
                    d[temp->vertex-1].predecessor = v.vertex;

                }
            }
            temp = temp->next;

        }
    }

    return d;
}
