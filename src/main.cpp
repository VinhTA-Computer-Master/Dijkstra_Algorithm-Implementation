/*
  Name: Vinh TA
  Project 2: Dijkstra's Shortest Path Algorithm
  File: main.cpp
*/

#include "Heap.h"
#include "graph.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

int main(int argv, char** argc){
  
  ifstream filein("Ginput.txt");  // input from file Ginput.txt
  if(filein.fail()){
    cout << "Ginput.txt not found!" << endl;
    return 0;
  }

  char c;  // letter command variable
  string input;  // input as string type from keyboard
  int ini = 0;  // variable for determining whether initialized or not

  Graph* G;

  do{
    cout << "Input command: " << endl;
    getline(cin, input);
    c = tolower(input[0]);
    cout << "Command: " << input << endl;
  
    if(c == 'i'){
      ini = 1;

      ifstream filein("Ginput.txt");
      int vertex =0;
      filein >> vertex;
      int edge =0;
      filein >> edge;

      G = new Graph(vertex,edge);

      int ** buff = new int*[edge+1];

      int err = 0;
      for(int i=1; i<=edge; i++){
	buff[i] = new int[4];
	filein >> buff[i][1];  // input u
	filein >> buff[i][2];  // input v
	filein >> buff[i][3];  // input w
	if(filein.fail()){
	  cout << "Error:  The number of edges is less than as specified in the beginning of the file.\n";
	  err = 1;
	  ini = 0;
	  break;
	}
      }

      if(err)
	continue;

      Element* inputVertex;
      inputVertex = G->utl->edgeToVertex(buff, vertex, edge);

      G->readGraph(G, inputVertex, vertex, edge);
    }

    else if(c == 'w'){
      if(!ini){
	cout << "Error: There is no graph to print\n";
	continue;
      }
      
      G->writeGraph();
    }

    else if(c == 'c'){
      if(!ini){
	cout << "Error:  There is no graph to run Dijkstra’s algorithm on.\n";
	continue;
      }

      int source = G->utl->getSource(input);
      int dest = G->utl->getDest(input,source);
      input[0] = input[input.length()-1];
      int flag = atoi(input.c_str());

      if(!(flag == 0 || flag == 1)){
	cout << "Error: Invalid flag value\n";
	continue;
      }

      if(!(source <= G->vertex && dest <= G->vertex)){
	cout << "Error: One or more of the nodes is invalid.\n";
	continue;
      }

      Graph* Dijk;
      Dijk = G->Dijkstra(G, source, dest);
      Dijk->utl->getLength(Dijk,source,dest,flag);

    } else if(c != 'e'){
      cout << "Invalid command\n";
    }
  }while(c != 'e');

  cout << "The program terminated.\n";

  return 0;
} // end of program
