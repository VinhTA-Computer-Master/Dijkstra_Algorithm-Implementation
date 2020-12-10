/* 
   Name: Vinh TA
   Project 2: Dijkstra's Shortest Path Algorithm
   File: Heap.h
*/

#pragma once
#include <stdlib.h>
#include <time.h>
#include "graph.h"

using namespace std;

class Edge;
class Graph;

class Element{
 public:
  int key;
  int id; 
  int sizeEdge;
  int pi;    // parent pointer
  Edge** edge;   // array pointer
  Element(void){
    key = 0;
    pi = 0;
    edge = NULL;
  }
  Element(int k){
    key = k;
    pi = 0;
    edge = NULL;
  }
  Element(int k, int e){
    key = k;
    sizeEdge = e;
    pi = 0;
    edge = new Edge*[e+1];
  }
};

class Heap{
 private:
  void MinHeapify(Heap,int);
  
 public:
  int capacity;
  int size;

  Element* H;

  Heap(int);
  Heap Initialize(int);
  void BuildHeap(Heap, Element*, int);
  void Insert(Heap, int, int);
  Element DeleteMin(Heap, int);
  Heap DecreaseKey(Heap, int, int, int);
  void printHeap(Heap);
};
