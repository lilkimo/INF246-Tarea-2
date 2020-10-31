#include <stdlib.h>
#include <stdio.h>
#include "queue.c"

#define CANTIDADJUGADORES 4
#define CANTIDADCASILLAS 29

typedef int jugador; // 0: Jugador, {1, 2, 3}: Bot.
typedef int casilla; // 0: Blanco, 1: ?, 2: ??.

casilla tablero[] = {0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 0, 0, 0, 0, 1, 2, 1, 2, 1, 2, 1, 0};
int posiciones[] = {0, 0, 0, 0}; // Posiciones de los Jugadores.
int sentido = 0; // 0: Inverso, 1: Normal.
queue *colaTurnos/* = newqueue()*/;

// Devuelve el tipo de casilla en la que "cayó" la ficha.
casilla mover(const jugador jugador, const casilla *tablero, const int cantidadCasillas) {
    int destino = posiciones[jugador] + cantidadCasillas;
    if (destino < 0)
        destino = 0;
    else if (destino >= CANTIDADCASILLAS)
        destino = CANTIDADCASILLAS - 1;
    
    posiciones[jugador] = destino;
    return tablero[destino];
}

int tirarDado() {
    return (rand()%6) + 1;
}

int main() {
    srand(2);
    return 0;
}