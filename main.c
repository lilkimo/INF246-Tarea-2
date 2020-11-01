#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>

#include "tablero.c" //cambiar por tablero.h

int tirarDado() {
    return (rand()%6) + 1;
}

void crearHijos(){
    int idJugador = -1;

    for(int i = 0; i < 4; i++) {
        if (fork() == 0) {
            idJugador = i;
            printf("hijo %d creado\n",idJugador);
            break;
        }
    }
}

int main() {
    srand(2);
    int id_jugador = -1;

    casilla *ptr_tablero = create_shared_memory(sizeof(tablero));
    int *ptr_posiciones = create_shared_memory(sizeof(posiciones));
    int *ptr_sentido = create_shared_memory(sizeof(sentido));

    *ptr_tablero = *tablero;
    *ptr_posiciones = *posiciones;
    *ptr_sentido = sentido;

    crearPipes();
    crearHijos(&id_jugador);
    sleep(1);
    manejoPipes(id_jugador);

    printf("ID: %d, SENTIDO = %d\n", id_jugador, ptr_tablero[1]);
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