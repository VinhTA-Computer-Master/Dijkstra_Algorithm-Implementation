/*
  Name: Vinh TA
  Project 2: Dijkstra's Shortest Path Algorithm
  File: util.cpp
*/

#pragma once 
#include "util.h"
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

int util::getSource(string input){  // get source from input string
  int j=0;
  for(unsigned i=2; i<input.length(); i++){
    input[j] = input[i];
    j++;
  }
  int ret = atoi(input.c_str());

  return ret;
}


int util::getDest(string input, int s){
  int j=0;

  if(s < 100){
    for(unsigned i=4; i<=input.length(); i++){
      input[j] = input[i];
      j++;
    }
  } else {
    for(unsigned i=6; i<=input.length(); i++){
      input[j] = input[i];
      j++;
    }
  }
  int ret = atoi(input.c_str());
  
  return ret;
}

int util::findIndex(Heap* Q, Element u, int size){
  for(int i=1; i<=size; i++){
    if(u.id == Q->H[i].id)
      return i;
  }
  return -1;
}

int util::findIndex(Heap Q, Element u, int size){
  for(int i=1; i<=size; i++){
    if(u.id == Q.H[i].id)
      return i;
  }
  return -1;
}


int util::findIndex(Heap* Q, int id, int size){
  for(int i=1; i<=size; i++){
    if(id == Q->H[i].id)
      return i;
  }
  return -1;
}


void util::copyGraph(Graph* G, Graph* ret){
  ret->Q = new Heap(G->vertex);
  
  for(int i=1; i<=G->vertex; i++){
    ret->Q->H[i].key = G->Q->H[i].key;
    ret->Q->H[i].id = G->Q->H[i].id;
    ret->Q->H[i].sizeEdge = G->Q->H[i].sizeEdge;
    ret->Q->H[i].edge = new Edge*[(G->Q->H[i].sizeEdge)+1];
    for(int j=1; j<=G->Q->H[i].sizeEdge; j++){
      ret->Q->H[i].edge[j] = new Edge(G->Q->H[i].edge[j]->v, G->Q->H[i].edge[j]->w);
    }
  }
  return;
}

Heap util::graphToHeap(Graph* G, Element* A){
  Heap ret = Heap(G->vertex);
    
  for(int i=1; i<=G->vertex; i++){
    ret.H[i].id = G->Q->H[i].id;
  }
  
  ret.BuildHeap(ret,A,G->vertex);

  return ret;  
}


void util::getLength(Graph* G, int s, int t, int f){
  int length = G->Q->H[t].key;
  if(!f){
    if(!(abs(length) <= 2000000000 || length > 0)){
      cout << "Sorry, node " << t << " is not reachable from node " << s << ".\n";
      return;
    }
    cout << "LENGTH: " << length << endl;
    return;
  }else{
    if(!(abs(length) <= 2000000000 || length >= 0)){
      cout << "Sorry, node " << t << " is not reachable from node " << s << ".\n";
      return;
    }
    int pointer = G->Q->H[t].id;
    int* list = new int[G->vertex+1];
    int listSize = 1;
    for(int i=1; i<=G->vertex; i++){
      if(G->Q->H[s].id == pointer)
	break;
      int ind = G->utl->findIndex(G->Q, pointer, G->vertex);
      pointer = G->Q->H[ind].pi;
      list[i] = ind;
      listSize++;
    }
    
    list[listSize] = s;
    cout << "PATH: ";
    for(int i=listSize; i>0; i--){
      cout << list[i] << ", ";
    }
    cout << endl;
    return;
  }
}


Element* util::edgeToVertex(int** buff, int vertex, int edge){
  Element* ret = new Element[vertex+1];

  int* tempEdgeSize = new int[vertex+1];

  // initialize tempEdgeSize
  for(int i=1; i<=vertex; i++){
    tempEdgeSize[i] = 0;
  }

  for(int i=1; i<=edge; i++){
    tempEdgeSize[buff[i][1]]++;  // sizeEdge at each vertex
  }

  // initialize each element
  for(int i=1; i<=vertex; i++){
    ret[i] = Element(0, tempEdgeSize[i]);
  }


  // reset tempEdgeSize for edge position of each vertex
  tempEdgeSize = new int[edge+1];
  for(int i=1; i<=edge; i++){
    tempEdgeSize[i] = 1;
  }

  // copy edges to elements
  for(int i=1; i<=edge; i++){
    ret[buff[i][1]].edge[tempEdgeSize[buff[i][1]]] = new Edge(buff[i][2],buff[i][3]);
    tempEdgeSize[buff[i][1]]++;
  }

  return ret;
}
