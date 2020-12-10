/*
  Name: Vinh TA
  Project 2: Dijkstra's Shortest Path Algorithm
  File: util.h
*/

#pragma once
#include <string>
#include "graph.h"
#include "Heap.h"

class Element;
class Heap;
class Graph;

using namespace std;

class util{
 public:
  util(void);
  int getSource(string);
  int getDest(string,int);
  int findIndex(Heap*,Element,int);
  int findIndex(Heap,Element,int);
  int findIndex(Heap*,int,int);
  void copyGraph(Graph* , Graph*);
  Heap graphToHeap(Graph*, Element*);
  void getLength(Graph*, int, int, int);
  Element* edgeToVertex(int**, int, int);
}; 
