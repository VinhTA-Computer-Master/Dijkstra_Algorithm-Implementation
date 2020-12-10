/*
   Name: Vinh TA
   Project 2: Dijkstra's Shortest Path Algorithm
   File: graph.cpp
*/

#pragma once
#include "graph.h"
#include <iostream>


Heap initialize(Graph* G, int s){
  Heap ret = Heap(G->vertex);
  Element* temp = new Element[G->vertex+1];
 
  // copy Heap to return
  for(int i=1; i<=G->vertex; i++){
    G->Q->H[i].key = 2147483647;  // inf
    G->Q->H[i].pi = 0;
    ret.H[i].sizeEdge = G->Q->H[i].sizeEdge;
    ret.H[i].edge = new Edge*[G->Q->H[i].sizeEdge];
    ret.H[i].id = G->Q->H[i].id;
    temp[i] = Element(2147483647);
    for(int j=1; j<=G->Q->H[i].sizeEdge; j++){
      ret.H[i].edge[j] = new Edge(G->Q->H[i].edge[j]->v,G->Q->H[i].edge[j]->w);
    }
  }

  ret.BuildHeap(ret,temp,G->vertex);

  G->Q->H[s].key = 0;
  ret.DecreaseKey(ret,1,s,0);

  return ret;
}

Heap relax(Graph* G, Heap Q, int u, Edge* e){
  
  Heap ret = Heap(G->vertex);
  ret.size = Q.size;

  // Copy Heap to return
  for(int i=1; i<=Q.size; i++){
    ret.H[i].id = Q.H[i].id;
    ret.H[i].key = Q.H[i].key;
    ret.H[i].sizeEdge = Q.H[i].sizeEdge;
    ret.H[i].edge = new Edge*[Q.H[i].sizeEdge];
    for(int j=1; j<=Q.H[i].sizeEdge; j++){
      ret.H[i].edge[j] = new Edge(Q.H[i].edge[j]->v,Q.H[i].edge[j]->w);
    }
  }


  // Relaxing...
  if(G->Q->H[e->v].key > (G->Q->H[u].key + e->w)){
    int indv = G->utl->findIndex(ret,G->Q->H[e->v],Q.size);  // find index of G in Heap
    ret = ret.DecreaseKey(ret,1,indv,(G->Q->H[u].key + e->w));
    ret.H[indv].pi = G->Q->H[u].id;
    G->Q->H[e->v].key = G->Q->H[u].key + e->w;
    G->Q->H[e->v].pi = G->Q->H[u].id;
  }

  return ret;
}


Graph::Graph(void){
  Graph::vertex = 0;
  Graph::Q = new Heap(0);
  return;
}


Graph::Graph(int sizeVertex, int sizeEdge){
  Graph::edge = sizeEdge;
  Graph::vertex = sizeVertex;
  Graph::Q = new Heap(sizeVertex);
  return;
}


void Graph::readGraph(Graph* G, Element* element, int size, int sizeEdge){
  Graph::edge=0;
  
  for(int i=1; i<=size; i++){
    Graph::Q->H[i].key = element[i].key;
    Graph::Q->H[i].pi = 0;
    Graph::Q->H[i].sizeEdge = element[i].sizeEdge;
    Graph::Q->H[i].edge = new Edge*[element[i].sizeEdge];
    for(int j=1; j<=element[i].sizeEdge; j++){
      Graph::Q->H[i].edge[j] = new Edge(element[i].edge[j]->v, element[i].edge[j]->w);
      Graph::edge++;
    }
  }
  return;
}


void Graph::writeGraph(void){
  cout << Graph::vertex << " " << Graph::edge << endl;
  for(int i=1; i<=vertex; i++){
    cout << i << ":  ";
    for(int j=1; j<= Graph::Q->H[i].sizeEdge; j++){
      cout <<"(" << Graph::Q->H[i].edge[j]->v << ", " << Graph::Q->H[i].edge[j]->w << "); ";
    } cout << endl;
  }
  cout << endl;
  return;
}


Graph* Graph::Dijkstra(Graph* graph, int s, int t){
  Graph* G;

  G = new Graph(graph->vertex, graph->edge);
  Heap tempQ = Heap(graph->vertex);
  
  Graph::utl->copyGraph(graph,G);  // COPY weigths and edge pointers and ids
  tempQ = Graph::utl->graphToHeap(G,G->Q->H);

  tempQ = initialize(G,s);

  Element* S = new Element[Graph::vertex+1];
  
  int j=1;
  while(tempQ.size >0){
    Element u = tempQ.DeleteMin(tempQ,1);
    
    S[j] = u;
    j++;
    int indu = Graph::utl->findIndex(G->Q,u,G->vertex);

    for(int i=1; i<=u.sizeEdge; i++){
      tempQ = relax(G,tempQ,indu,u.edge[i]);
    }

    if(G->Q->H[t].id == u.id)
      break;  // stop when destination reached
  }

  return G;
}
