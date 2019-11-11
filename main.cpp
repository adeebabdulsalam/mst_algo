#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono; 
#include "kruskal_mst.h"
#include "prims_mst.h"
#include <fstream>


int main(){
    int n,cost,total_cost;
    char ch;
    string filename;
    Graph* g=new Graph;
    n=total_cost=0;
    cout<<"Enter input filename: ";
    cin>>filename;
    ifstream fin(filename.c_str());
    if(!fin)
        cout<<"Couldn't Open file";

    while(1)
    {
        fin.get(ch);
        if(ch=='\n')
            break;
        else if(ch!=' '&&ch!='-')
        n++;
    }
    g->N = n;
    fin.seekg (0, fin.beg);
    for(int i=0;i<n;i++){
        insert_node(g,i+1);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            fin>>cost;
            if(cost>0){
                create_edge(g,i+1,j+1,cost);
                total_cost += cost;
            }
        }
    }
    g->cost = total_cost;
    Graph* T = NULL;
    auto start = high_resolution_clock::now();
    T = kruskal_mst(g);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    print_graph(T,"Prim's algorithm MST",duration.count());
    start = high_resolution_clock::now();
    T = prims_mst(g);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    print_graph(T,"Kruskal's algorithm MST",duration.count());
    return 0;
}