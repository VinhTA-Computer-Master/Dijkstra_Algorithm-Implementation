/* 
   Name: Vinh TA
   Project 2: Dijkstra's Shortest Path Algorithm
   File: Heap.cpp
*/

#pragma once
#include "Heap.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>



using namespace std;

int parent(int i){
  return (i/2);
}

int left(int i){
  return (2*i);
}

int right(int i){
  return (2*i+1);
}

void Heap::MinHeapify(Heap A,int i){
  int l = left(i);
  int r = right(i); 
  int smallest=0;
  if(l<=Heap::size && Heap::H[l].key < Heap::H[i].key)
    smallest = l;
  else
    smallest = i;
  if(r<=Heap::size && Heap::H[r].key < Heap::H[smallest].key)
    smallest = r;
  if(smallest != i){
    Element temp = Heap::H[i];
    Heap::H[i] = Heap::H[smallest];
    Heap::H[smallest] = temp;
    Heap::MinHeapify(A,smallest);
  }
}

Heap::Heap(int n){
  Heap::size = 0;
  Heap::capacity = n;
  Heap::H = new Element[n+1];
  for(int i=1; i<=n; i++){
    srand(time(NULL));
    Heap::H[i].id = abs(rand()*i);
  }
}

Heap Heap::Initialize(int n){
  Heap ret(n);
  return ret;
}

void Heap::BuildHeap(Heap heap, Element* A, int n){
  if(n > Heap::capacity){
    cout << "Sorry!!! It cannot be done. Please increase the capacity of heap first." << endl;
    return;
  }

  for(int i=1; i<=n; i++){
    Heap::size++;
    Heap::H[i].key = A[i].key;
  }

  for(int i=n/2; i>0; i--){
    Heap::MinHeapify(heap,i);
  }
  return;
}


void Heap::Insert(Heap heap, int flag, int k){
  if(Heap::size >= Heap::capacity){
    Heap::capacity = Heap::capacity*2;
  }

  if(flag==2){
    Heap::printHeap(heap);
  }

  Heap::size++;
  Heap::H[size].key = k;
  int i=Heap::size;
  while(i>1 && Heap::H[parent(i)].key > Heap::H[i].key){
    int temp = Heap::H[parent(i)].key;
    Heap::H[parent(i)].key = Heap::H[i].key;
    Heap::H[i].key = temp;
    i=parent(i);
  }

  if(flag==2){
    Heap::printHeap(heap);
  }
  return;
}

Element Heap::DeleteMin(Heap heap, int flag){
  if(heap.size <1){
    cout << "There are no elements in heap to delete." << endl;
    Element ret(999999);
    return ret;
  }

  if(flag==2){
    Heap::printHeap(heap);
  }

  Element min = heap.H[1];
  Heap::H[1] = heap.H[heap.size];
  Heap::size--;
  MinHeapify(heap,1);
  if(flag==2){
    Heap::printHeap(heap);
  }
  return min;
}

Heap Heap::DecreaseKey(Heap heap, int flag, int index, int value){
  if(index > heap.size){
    cout << "There are only " << heap.size << " elements in the heap. Hence this operation cannot be completed." << endl;
    return NULL;
  }

  if(value >= heap.H[index].key){
    cout << "Decreasing value cannot be larger than current value." << endl;
    return NULL;
  }

  if(flag ==2){
    Heap::printHeap(heap);
  }

  heap.H[index].key = value;
  while(index>1 && heap.H[parent(index)].key > heap.H[index].key){
    Element temp = heap.H[parent(index)];
    heap.H[parent(index)] = heap.H[index];
    heap.H[index] = temp;
    index=parent(index);
  }

  if(flag ==2){
    Heap::printHeap(heap);
  }
  return heap;
}

void Heap::printHeap(Heap heap){
  cout << "The capacity is " << Heap::capacity << ".\nSize is " << Heap::size << endl;
  for(int i=1; i<=Heap::size; i++){
    cout << Heap::H[i].key << endl;
  }
}
