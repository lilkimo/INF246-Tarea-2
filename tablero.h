#ifndef __TABLERO_H__
#define __TABLERO_H__

#include "queue.c" //cambiar por queue.h

#define CANTIDADJUGADORES 4
#define CANTIDADCASILLAS 29

typedef int jugador; // 0: Jugador, {1, 2, 3}: Bot.
typedef int casilla; // 0: Blanco, 1: ?, 2: ??.

casilla mover(const jugador jugador, const int cantidadCasillas, const casilla *tablero, int *posiciones);

typedef void (*efecto)(jugador, casilla *, int *, int *, queue *);
efecto vectorEfectos1[];
efecto vectorEfectos2[];

void ejecutarEfecto(const casilla tipoCasilla, const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos);
void printtablero(const casilla *tablero, const int *posiciones, const int sentido);

#endif