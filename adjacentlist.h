/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   adjacentlist.h
 * Author: mcarroll
 *
 * Created on October 14, 2017, 2:05 PM
 */

#ifndef ADJACENTLIST_H
#define ADJACENTLIST_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct list{
    int vertex;
    struct list* n;
}List;

typedef struct array{
    int vertex;
    int distance;
    int totalVert;
    int found;
    struct list* n;
}Array;

// typedef struct graph{
//     int vert;
//     struct array* arr;
// }Graph;

typedef struct queue{
    int data;
    struct queue* next;
}Queue;

Queue* rear = NULL;

Array* create(int verticies);
void addEdge(Array* arr, char* string, int vert);
Array* read(char* ifile);
void print(Array* arr);
//void free(Graph* graph);
int parseHolder(char* string);
void BFS(Array* arr, char* ofile);
//int* init_Queue(Graph* graph);
Queue* enqueue(Queue* queue, int num);
Queue* dequeue(Queue* queue);
void printQueue(Queue* queue);
// int qIsEmpty(Queue* queue);

#endif /* ADJACENTLIST_H */
