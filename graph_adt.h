#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>

using namespace std;

struct edges{
    int key; //key represent the end vertex(v) of an edge
    int cost; //cost of the edge
    edges* next_edge;
};

struct node{
    int key; //key represent the start vertex(u) of an edge
    edges* adjnode=NULL; //links to list of adjacent edges
    node* next; //links to list of all vertex in the graph
    bool t=false; //t is set to true if the vertex(u) is added to prims_mstree
};

struct Graph{
    int N; //number of nodes or vertices
    int cost=0; //Total cost of the graph
    node* graph_head=NULL;
};

//function to insert vertex with key as index(u): has a Timecomplexity T : O(1)
void insert_node(Graph *g,int key){
    node* newnode = new node;
    newnode->key = key;
    newnode->next = g->graph_head;
    g->graph_head = newnode;       
}

//function which returns a vertex node,when given it's index(u) as key: has a Timecomplexity T: O(N)
node* find_node(Graph *g,int key){
 node* temp = g->graph_head;
 while(temp!=NULL){
     if(temp->key == key){
         return temp;
     }
     temp = temp->next;
 }
 return NULL;
}

//given the start vertex(src_key) & end vertex(dest_key) of an edge along with it's cost,an edge is created
// This newly created edge is added to adjecancy list of starte vertex(src_key)
void create_edge(Graph *g,int src_key, int dest_key, int cost){
    node* src_node = find_node(g,src_key);      //T: O(N)
    edges* newedge = new edges;
    newedge->cost = cost;
    newedge->key = dest_key;
    newedge->next_edge = src_node->adjnode;
    src_node->adjnode = newedge;
}

//given a vertex(u), and vertex(v) as key,
//the function returns the edge between these two vertex from the adjacency list of vertex(u)
edges* find_edge(node* u,int key){
    edges* temp = u->adjnode;
    while(temp!=NULL){
        if(temp->key == key){
            return temp;
        }
        temp = temp->next_edge;
    }
    return NULL;
}

void print_graph(Graph* g,string title,long duration){
  cout<<title<<" (total cost: "<<g->cost<<"; runtime: "<<duration<<"ms)"<<endl;
  int n =g->N;
  node* temp=NULL;
  edges* edg=NULL;
  for(int i=0;i<n;i++){
      temp = find_node(g,i+1);
      for(int j=i+1;j<=n;j++){
        if(temp!=NULL){
          edg = find_edge(temp,j);
          if(edg!=NULL){
              cout<<"("<<temp->key<<","<<edg->key<<")"<<endl;
          }
        }
      }
  }
}

#endif