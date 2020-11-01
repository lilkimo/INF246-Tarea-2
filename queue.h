#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h> 
#include <stdlib.h>

typedef struct { 
    unsigned int front, rear, length, size;
    int *content;
} queue;

queue * newqueue(unsigned int size);
void enqueue(queue *q, int k);
int dequeue(queue *q);
void printqueue(queue *q);

#endif
