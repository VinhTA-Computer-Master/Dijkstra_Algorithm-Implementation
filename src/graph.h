/*
   Name: Vinh TA
   Project 2: Dijkstra's Shortest Path Algorithm
   File: graph.h
*/

#pragma once
#include "Heap.h"
#include "util.h"

using namespace std;

class Heap;
class Element;
class util;

class Edge{
 public:
  int v;
  int w;

  Edge(int vi, int wi){
    v = vi;
    w = wi;
  }
};


class Graph{
 public:
  int edge;
  int vertex;
  Heap* Q;
  util* utl;

  Graph(void);
  Graph(int,int);
  void readGraph(Graph*,Element*,int,int);
  void writeGraph(void);
  Graph* Dijkstra(Graph*,int,int);
};
