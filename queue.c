#include "queue.h"

_queueNode * _newQueueNode(int k) {
    _queueNode *temp = (_queueNode *)malloc(sizeof(_queueNode)); 
    temp->key = k; 
    temp->next = NULL; 
    return temp; 
}

queue* newqueue() { 
    queue *q = (queue *)malloc(sizeof(queue)); 
    q->front = q->rear = NULL; 
    return q; 
} 

void enqueue(queue *q, int k) { 
    _queueNode *temp = _newQueueNode(k); 
    
    if (q->rear == NULL) { 
        q->front = q->rear = temp;
    }
    else {
        q->rear->next = temp; 
        q->rear = temp;
    }

    q->length++;
} 

int dequeue(queue *q) { 
    if (q->front == NULL) 
        return -1; 
    
    _queueNode *temp = q->front; 
    int value = temp->key;

    q->front = q->front->next; 

    if (q->front == NULL) 
        q->rear = NULL; 
    
    free(temp);
    q->length--;

    return value;
}

void clearqueue(queue *q) {
    while (q->length != 0)
        dequeue(q);
}

void _printqueue(_queueNode *prev, _queueNode *rear) {
    if (prev != rear)
        _printqueue(prev->next, rear);
    printf("%d, ", prev->key);
}

void printqueue(queue *q) {
    if (q->length <= 0)
        return;
    
    printf("[");
    if (q->front != q->rear)
        _printqueue(q->front->next, q->rear);
    printf("%d]\n", q->front->key);
}