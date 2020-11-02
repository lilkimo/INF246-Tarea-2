#include "comunicacion.c" // Cambiar por comunicacion.h
#include "queue.h"

/*
Nombre:  newqueue
Recibe:  size: Indica el tamaño del buffer de la cola.
Retorna: Un puntero a la cola.   
Hace:    Inicializa la cola.
*/
queue *newqueue(unsigned int size) {
    queue *q = crearMemoriaCompartida(sizeof(queue));
    q->content = crearMemoriaCompartida(sizeof(int)*size);
    q->front = q->rear = -1;
    q->length = 0;
    q->size = size;
    return q;
}

/*
Nombre:  enqueue
Recibe:
         q: La cola en dónde insertar el elemento.
         k: El elemento que se desea insertar.
Retorna: Nada.   
Hace:    Inserta un elemento a la cola.
*/
void enqueue(queue *q, int k) {
    if (q->length == q->size)
        return;
    
    q->rear = (q->rear+1)%q->size;
    q->content[q->rear] = k;
    q->length++;
    
    if (q->length == 1)
        q->front = q->rear;
}

/*
Nombre:  dequeue
Recibe:  q: La cola en dónde se desea remover un elemento.
Retorna: El elemento que se desencoló.   
Hace:    Desencola un elemento de la cola.
*/
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

/*
Nombre:  enqueue
Recibe:  q: La cola que se desea mostrar en pantalla.
Retorna: Nada.   
Hace:    Muestra en pantalla la cola, donde el elemento de más a la derecha es el próximo a desencolar.
*/
void printqueue(queue *q) {
    int i, j;
    printf("[");
    for (i = 0, j = q->rear; i < q->length-1; i++) {
        printf("%d, ", q->content[j]);
        j = (j-1)%q->size;
    }
    printf("%d]\n", q->content[j]);
}
