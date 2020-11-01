#include "comunicacion.c" // Cambiar por comunicacion.h
#include "queue.h"

queue *newqueue(unsigned int size) {
    queue *q = crearMemoriaCompartida(sizeof(queue));
    q->content = crearMemoriaCompartida(sizeof(int)*size);
    q->front = q->rear = -1;
    q->length = 0;
    q->size = size;
    return q;
}

void enqueue(queue *q, int k) {
    if (q->length == q->size)
        return;
    
    q->rear = (q->rear+1)%q->size;
    q->content[q->rear] = k;
    q->length++;
    
    if (q->length == 1)
        q->front = q->rear;
}

int dequeue(queue *q) {
    if (q->length < 1)
        return -1;
    
    int k = q->content[q->front];
    q->front = (q->front+1)%q->size;
    q->length--;

    if (q->length == 0)
        q->front = q->rear = -1;

    return k;
}

void printqueue(queue *q) {
    int i, j;
    printf("[");
    for (i = 0, j = q->rear; i < q->length-1; i++) {
        printf("%d, ", q->content[j]);
        j = (j-1)%q->size;
    }
    printf("%d]\n", q->content[j]);
}

int main() {
    int pop;
    queue *q = newqueue(4);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    printqueue(q);
    pop = dequeue(q);
    printf("%d popped\n", pop);
    printqueue(q);
    pop = dequeue(q);
    printf("%d popped\n", pop);
    printqueue(q);
    pop = dequeue(q);
    printf("%d popped\n", pop);
    printqueue(q);
}