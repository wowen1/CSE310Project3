#include <iostream>
#include <string>

using namespace std;


struct adjList
{
    int vertex;
    int weight;
    adjList* next;
};

struct heapNodes
{
    int vertex;
    int predecessor;
    int distance;
};
class MINHEAP
{
public:
    heapNodes* nodes;
    int heapSize;
    int size;

    MINHEAP(int num)
    {
        heapSize = 0;
        size = num;
        nodes = new heapNodes[size];
    }
    void display()
    {
        int i;
        for(i=0;i<heapSize;i++)
        {
            cout<<"Nodes["<<i<<"]="<<nodes[i].distance<<".  V: "<<nodes[i].vertex<<endl;
            //cout<<"vertex["<<i<<"]="<<nodes[i].vertex<<endl;
        }
    }
    int hasNode(int key)
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
    int isEmpty()
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
    void insert(heapNodes key)
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

    int getParent(int i)
    {
        int parent;
        parent = (i-1)/2;
        return parent;
    }

    void decreaseKey(int val,int index)
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
        //nodes[index].distance = val;
        heapNodes temp;
        //i = index;
        while(i != 0 && nodes[getParent(i)].distance > nodes[i].distance)
        {
            temp = nodes[getParent(i)];
            nodes[getParent(i)] =  nodes[i];
            nodes[i]=temp;
            i = getParent(i);
        }
    }
    heapNodes extractMin()
    {
        heapNodes min;
        min = nodes[0];
        nodes[0] = nodes[heapSize-1];
        heapSize = heapSize - 1;
        heapify(0);

        return min;
    }

    void minHeapSort()
    {
        int i;

        for(i = (heapSize / 2); i >= 0; i--)
        {
            heapify(i);
        }

    }

    void heapify(int rootIndex)
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

};

void adjListInsertion (adjList** list,int vertex1,int vertex2, int weight); //insert into utils
void writeGraph(adjList** list,int nVertices, int nEdges);//insert into graph.cpp
//void heapify(heapNodes* minHeap, int heapSize, int rootIndex);
//void minHeapSort(heapNodes* minHeap, int heapSize);
//heapNodes extractMin(heapNodes* minHeap,int& heapSize);
//int getParent(int i);
//void decreaseKey(heapNodes* minHeap,int val,int index);
heapNodes* dijkstra(adjList** list, int source,int nVertices);
void predVertices(heapNodes* d,int tar);


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

    //cout<<nVertices<<nEdges<<endl;

    adjList** adjlist = new adjList*[nVertices]; //dynamically allocates an array of adjList pointers.

    for(i = 0; i < nEdges; i++)
    {
        getline(cin,val);

        delLoc = val.find(del);
        s1 = val.substr(0,delLoc);
        u = stoi(s1,nullptr,10);  //parses the first vertex value

        //cout<< "u= "<<u<<endl;

        s1 = val.substr(delLoc+1, val.length());
        delLoc = s1.find(del);
        s2 = s1.substr(0,delLoc);
        v = stoi(s2,nullptr,10); //parses the second vertex value

        //cout<<"v= "<<v<<endl;

        s1 = s1.substr(delLoc+1,val.length());
        w = stoi(s1,nullptr,10); //parses the weight value

        //cout<<"w= "<<w<<endl;

        adjListInsertion(adjlist,u,v,w); //inserts it into the adjList.
        //cout<<"asdfas="<<adjlist[u-1]->vertex<<endl;

    }
    do
    {
        getline(cin, val);

        if (val == "stop")
        {
            //stop
            cout << "Command: stop" << endl;
        } else if (val == "write")
        {
            //do write stuff
            cout << "Command: write" << endl;
            writeGraph(adjlist,nVertices,nEdges);
        } else
        {
            //weeeee
            delLoc = val.find(del);
            s1 = val.substr(0,delLoc);
            if(s1 == "find")
            {
                s2 = val.substr(delLoc+1,val.length());
                delLoc = s2.find(del);
                s1 = s2.substr(0,delLoc);
                src = stoi(s1,nullptr,10);
                s3 = s2.substr(delLoc+1,val.length());
                delLoc = s3.find(del);
                s1 = s3.substr(0,delLoc);
                targ = stoi(s1,nullptr,10);
                s2 = s3.substr(delLoc+1,val.length());
                flag = stoi(s2,nullptr,10);

                cout<<"Command: find "<<src<<" "<<targ<<" "<<flag<<endl;
                error = 0;
                int srcValid, tarValid;
                //srcValid = validNode(adjlist,src-1);
                //tarValid = validNode(adjlist,targ-1);
                if(((src) < 1||(src)>nVertices) || ((targ)<1 || (targ)>nVertices))
                {
                    cout<<"Error: one or more invalid nodes"<<endl;
                    error = 1;
                }
                if(flag!= 0 && flag != 1)
                {
                    cout<<"Error: invalid flag value"<<endl;
                    error = 1;
                }
                if(error == 0)
                {

                    heapNodes* distances;// = new heapNodes[nVertices];

                    distances = dijkstra(adjlist,src-1,nVertices);
                    if(distances[targ-1].distance == 9001)
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
        //return pred;
    }

}
heapNodes* dijkstra(adjList** list, int source,int nVertices)
{
    heapNodes* d = new heapNodes[nVertices];
    int visited[nVertices];


    heapNodes v;
    int i,sum,j;
    adjList* temp;

    MINHEAP q(nVertices); //= new MINHEAP(nVertices);
    //d[source] = *new heapNodes();
    d[source].distance = 0;
    d[source].vertex = source;
    d[source].predecessor = -1;

    for(i=0;i<nVertices;i++)
    {
        visited[i] = 0;
        if(i != source)
        {
            //d[i] = *new heapNodes();
            d[i].distance = 9001;
            d[i].vertex = i;
            d[i].predecessor = -1;
        }
        q.insert(d[i]);
    }
    while(q.isEmpty() == 0)
    {
        v = q.extractMin();
        //cout<<"v.vertex=="<<v.vertex<<endl;
        j = v.vertex;
        visited[j] = 1;
        //cout<<"J == " <<j<<endl;
        //cout<<"heapsize= " << q.heapSize<<endl;

        temp = list[j];
        while(temp != nullptr)
        {
           // cout<<"temp->vertex -1 ="<<temp->vertex-1<<endl;
           //cout<<"\t\t\thasVisted ="<<visited[temp->vertex-1]<<endl;
            if(visited[temp->vertex-1] == 0)
            {
                sum = v.distance + temp->weight;
                //cout<<"vdist= "<<v.distance<<endl;
                //cout<<"tempweight3232= "<<temp->weight<<endl;
                if(sum < d[temp->vertex-1].distance)
                {
                    q.decreaseKey(sum,temp->vertex-1);
                    d[temp->vertex-1].distance = sum;
                    d[temp->vertex-1].predecessor = v.vertex;

                    //q.display();
                    int ok;
                   /* for(ok = 0;ok<nVertices;ok++)
                    {
                        cout<<"dist=:"<<ok<<":"<<d[ok].distance<<" pred = "<<d[ok].predecessor<<endl;
                    }*/
                }
            }
            temp = temp->next;

        }
    }
    //cout<<"ok i guess"<<endl;
    //q.display();
    int o;

    return d;
}

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

void adjListInsertion (adjList** list,int vertex1,int vertex2, int weight) //insert into util.cpp
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