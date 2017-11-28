#ifndef ADJACENTLIST_H
#define ADJACENTLIST_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// #include "heaps.h"
#include "input_error.h"

//This is the struct for the list actually coming off the array of verticies
typedef struct list{
    int vertex;
    //weight variable is the weight of the edge (added to accomidate for weighted graph)
    int weight;
    struct list* n;
}List;


//This is the array of verticies
typedef struct array{
    int vertex;
    int distance;
    int totalVert;
    int found;
    //Had to add for u.pi (keep track of predecessor in path)
    struct array* predecessor;
    struct list* n;
}Array;

//Queue used for Implementation of BFS
typedef struct queue{
    int data;
    struct queue* next;
}Queue;


//CUT FROM HEAPS.H

typedef struct heapVertex{
  int vertex;
  int distance;
  struct list* n;
  // int predecessor;
  // struct heap* right;
  // struct heap* left;
}vertex;

// void addToHeap(vertex* root, vertex toBeAdded);
// vertex* addToTree(vertex* head, vertex* added);
void minHeapify(vertex holder[], int total, int i);
void buildMinHeap(vertex holder[], int total);
vertex extractMin(vertex holder[], int heapSize);
void updateHeap(vertex holder[], vertex v);

//END CUT

//Pointer for easier access of the end of the rear of the queue
// Queue* rear = NULL;


Array* create(int verticies);
void addEdge(Array* arr, char* string, int vert);
Array* read(char* ifile);
void print(Array* arr);
int parseHolder(char* string);
void BFS(Array* arr, char* ofile);
Queue* enqueue(Queue* queue, int num);
Queue* dequeue(Queue* queue);
void printQueue(Queue* queue);
void dijkstras(Array* arr, char* ofile);
vertex* initSingleSource(Array* arr, vertex holder[]);
void relax(vertex u, vertex v, int weight, vertex holder[]);

#endif
