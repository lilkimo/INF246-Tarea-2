#include <stdlib.h>
#include <stdio.h>

#define CANTIDADJUGADORES 4
#define CANTIDADCASILLAS 29

typedef int jugador; // 0: Jugador, {1, 2, 3}: Bot.
typedef int casilla; // 0: Blanco, 1: ?, 2: ??, 3: Inicio, 4: Final.

casilla tablero[/*CANTIDADCASILLAS*/] = {3, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 0, 0, 0, 0, 1, 2, 1, 2, 1, 2, 1, 4};
int posiciones[/*CANTIDADJUGADORES*/] = {0, 0, 0, 0}; // Posiciones de los Jugadores.
int sentido = 0; // 0: Normal, 1: Inverso.

//Cola turnos.

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

int main() {
    return 0;
}