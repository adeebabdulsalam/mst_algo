
#include <limits>
#include "graph_adt.h"

//returns the edge with minimum cost from the adjacency list of vertex u
edges* find_min_edge(Graph* g,node* u){
    edges* v = u->adjnode;
    int min_cost=std::numeric_limits<int>::max();   //set minimum cost to a very large integer
    edges* min_v = NULL;
    while(v!=NULL){
        if (!(find_node(g,v->key)->t) && (v->cost <= min_cost))
        {
            min_cost = v->cost;
            min_v = v;
        }
        v = v->next_edge;
    }
    return min_v;
}

//returns true if all of the vertex of graph is added to MST T
bool all_true(Graph* g){
    node* temp = g->graph_head;
    while(temp!=NULL){
        if(!temp->t)        //bool variable t will be set to true if the vertex is in MST already
            return false;
        temp = temp->next;    
    }
    return true;
}

Graph* prims_mst(Graph* g){
    Graph *T = new Graph; //Final MST will be returned as a graph Data structure
    int total_cost=0;
    T->N = g->N;
    g->graph_head->t = true; //Initialize first node as part of T
    insert_node(T,g->graph_head->key); //adds first node to MST T
    while(!all_true(g)){
       node* u = g->graph_head;
       edges* v = NULL;
       node* min_u = NULL;
       node* min_v = NULL;
       edges* min_uv = NULL;
       int min_cost = std::numeric_limits<int>::max();
       //loops through all vertices
       while(u!=NULL){
        if(u->t){ 
           v = find_min_edge(g,u);
           if(v && v->cost < min_cost){
               min_uv = v;
               min_u = u;
               min_v = find_node(g,v->key);
               min_cost = v->cost;      //minimum cost of edges whose any one vertex belongs to MST set
           }
        }
        u = u->next;
       }
       //adds the edge with lowest cost to MST,whose one vertex belongs to MST and other vertex doesn't.
       insert_node(T,min_v->key);
       create_edge(T,min_u->key,min_v->key,min_cost);
       create_edge(T,min_v->key,min_u->key,min_cost);
       min_v->t = true;     //now both the vertex of edge belongs to MST set
       total_cost += min_cost;  //adds the cost of this edge to total cost of MST T
    }
    T->cost = total_cost; 
    return T;
}