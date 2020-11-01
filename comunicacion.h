#ifndef __COMUNICACION_H__
#define __COMUNICACION_H__

#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

#define READ 0
#define WRITE 1

typedef int Pipe;

void *crearMemoriaCompartida(size_t size);
void crearPipes();
void manejoPipes(int id_jugador);
void crearHijos(int *id);
void cerrarPipes(int idJugador);

#endif