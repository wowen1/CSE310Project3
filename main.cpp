#include <iostream>
#include <string>

using namespace std;


struct adjList
{
    int vertex;
    int weight;
    adjList* next;
};

void adjListInsertion (adjList** list,int vertex1,int vertex2, int weight); //insert into utils
void writeGraph(adjList** list,int nVertices, int nEdges);//insert into graph.cpp


int main(int argc, char *argv[])
{
    string val,s1,s2,s3;
    string del = " ";
    int delLoc,i,u,v,w;
    int num,nVertices,nEdges;

    getline(cin,val);  //reads number of vertices and edges as a string

    delLoc = val.find(del);
    s1 = val.substr(0,delLoc);
    nVertices =  stoi(s1,nullptr,10); //cuts the string at the first space to convert the value to an int for nVertices.

    s1 = val.substr(delLoc+1,val.length());
    nEdges = stoi(s1,nullptr,10);//converts the second half into an int for nEdges

    cout<<nVertices<<nEdges<<endl;

    adjList** adjlist = new adjList*[nVertices]; //dynamically allocates an array of adjList pointers.

    for(i = 0; i < nEdges; i++)
    {
        getline(cin,val);

        delLoc = val.find(del);
        s1 = val.substr(0,delLoc);
        u = stoi(s1,nullptr,10);  //parses the first vertex value

        cout<< "u= "<<u<<endl;

        s1 = val.substr(delLoc+1, val.length());
        delLoc = s1.find(del);
        s2 = s1.substr(0,delLoc);
        v = stoi(s2,nullptr,10); //parses the second vertex value

        cout<<"v= "<<v<<endl;

        s1 = s1.substr(delLoc+1,val.length());
        w = stoi(s1,nullptr,10); //parses the weight value

        cout<<"w= "<<w<<endl;

        adjListInsertion(adjlist,u,v,w); //inserts it into the adjList.
        cout<<"asdfas="<<adjlist[u-1]->vertex<<endl;

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
        }
    }while(val != "stop");



    cout << "Hello, World!" <<endl;
    return 0;
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
            cout<<"("<<temp->vertex<<";"<<temp->weight<<"); ";
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