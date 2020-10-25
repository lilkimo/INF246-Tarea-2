#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h> 
#include <stdlib.h>

typedef struct queueNode { 
    int key; 
    struct queueNode *next; 
} _queueNode; 

typedef struct { 
    _queueNode *front, *rear;
    int length;
} queue; 

_queueNode * _newQueueNode(int k);
queue * newqueue();
void enqueue(queue *q, int k);
int dequeue(queue *q);
void clearqueue(queue *q);
void printqueue(queue *q);

#endif