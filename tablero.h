#ifndef __TABLERO_H__
#define __TABLERO_H__

#include "queue.c" //cambiar por queue.h

#define CANTIDADJUGADORES 4
#define CANTIDADCASILLAS 29

typedef int jugador; // 0: Jugador, {1, 2, 3}: Bot.
typedef int casilla; // 0: Blanco, 1: ?, 2: ??.
typedef void (*efecto)(jugador, casilla *, int *, int *, queue *);

efecto vectorEfectos1[]; // Efectos de las casillas tipo ?.
efecto vectorEfectos2[]; // Efectos de las casillas tipo ??.

casilla mover(const jugador jugador, const int cantidadCasillas, const casilla *tablero, int *posiciones);
void printtablero(const casilla *tablero, const int *posiciones, const int sentido);
void ejecutarEfecto(const casilla tipoCasilla, const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos);

#endif