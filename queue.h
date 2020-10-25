#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h> 
#include <stdlib.h>

typedef struct { 
    int key; 
    queueNode *next; 
} queueNode; 

typedef struct { 
    queueNode *front, *rear; 
} queue; 

queue * createQueue();
void enqueue(queue *q, int k);
void dequeue(queue *q);
void clear(queue *q);

#endif