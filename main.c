#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>

#include "tablero.c" //cambiar por tablero.h

int tirarDado() {
    return (rand()%6) + 1;
}

void crearHijos(){
    int idJugador;

    for(int i = 0; i < 4; i++) {
        if (fork() == 0) {
            idJugador = i;
            printf("hijo %d creado\n",idJugador);
            break;
        }
    }
}

int main() {
    // BEGIN ejemplo
    casilla tablero[] = {0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 0, 0, 0, 0, 1, 2, 1, 2, 1, 2, 1, 0};
    int posiciones[] = {0, 0, 0, 0}; // Posiciones de los Jugadores.
    int sentido = 1; // -1: Inverso, 1: Normal.
    
    queue *colaTurnos = newqueue();
    enqueue(colaTurnos, 0);
    enqueue(colaTurnos, 1);
    enqueue(colaTurnos, 2);
    enqueue(colaTurnos, 3);

    jugador jugadorActual = 0;

    printqueue(colaTurnos);
    ejecutarEfecto(1, jugadorActual, tablero, posiciones, &sentido, colaTurnos);
    printqueue(colaTurnos);
    // END ejemplo

    return 0;
}