#include <stddef.h>
#include "graph_adt.h"
#include "priority_quee.h"
#include "mfset.h"
Graph* kruskal_mst(Graph* g){
  int n =g->N;      //sets n as number of vertices
  p_node* pquee=NULL;
  node* temp=NULL;
  edges* edg=NULL;
  for(int i=0;i<n;i++){
      temp = find_node(g,i+1);
      for(int j=i+1;j<=n;j++){
          edg = find_edge(temp,j);
          if(edg!=NULL){
            //insert all edges to the priorityQ in the vertex order
            insert_pnode(&pquee,temp->key,edg->key,edg->cost);    
          }
      }
  }
  int** mfset=new int*[n];
  for(int i=0;i<n;i++)
    mfset[i]=new int[n];
  initialize(mfset,n);
  //declare a new Graph object T to store MST  
  Graph* T=new Graph;   
  int total_cost=0;
  T->N = n;
  for(int i=0;i<n;i++)
    insert_node(T,i+1); 
  p_node* temp2 = pquee;
  while(temp2!=NULL){
      int u = find(mfset,temp2->src_key);   //src_key as start vertex u 
      int v = find(mfset,temp2->dest_key);  //dest_key as end vertex v
      if(u!=v){
        merge(mfset,temp2->src_key,temp2->dest_key);
        //if the vertex u and v doesn't belong to same set, 
        //it means adding the edge(u,v) doesn't form a cycle, thus the edge is added to MST T
        create_edge(T,temp2->src_key,temp2->dest_key,temp2->priority);
        create_edge(T,temp2->dest_key,temp2->src_key,temp2->priority);
        total_cost += temp2->priority;  //calculates cost of MST T
      }
      temp2=temp2->next;
  }
  T->cost = total_cost;
  return T;   //returns the MST as a graph
}

