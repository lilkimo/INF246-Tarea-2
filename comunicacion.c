#include "comunicacion.h"

int pipeJ0_P[2];
int pipeJ1_P[2];
int pipeJ2_P[2];
int pipeJ3_P[2];
int pipeP_J0[2];
int pipeP_J1[2];
int pipeP_J2[2];
int pipeP_J3[2];

Pipe *vectorPipesJx_P[] = {pipeJ0_P, pipeJ1_P, pipeJ2_P, pipeJ3_P};
Pipe *vectorPipesP_Jx[] = {pipeP_J0, pipeP_J1, pipeP_J2, pipeP_J3};

/*
Nombre:  crearMemoriaCompartida
Recibe:
         size: Tamaño de la memoria compartida.
Retorna: void.
Hace:    crea una region en la memoria compartida de tamaño size.
*/

void* crearMemoriaCompartida(size_t size){
    int protection = PROT_READ | PROT_WRITE;
    int visibilty = MAP_SHARED | MAP_ANONYMOUS;
    return mmap(NULL, size, protection, visibilty, -1, 0);
}

/*
Nombre:  crearPipes
Recibe: nada
Retorna: nada.
Hace: Crea las pipes para que se comuniquen los procesos, en total son 8, 2 entre cada proceso padre-hijo.
*/

void crearPipes(){
    for (int i = 0; i < 4; i++){
        pipe(vectorPipesJx_P[i]);
    }
    for (int i = 0; i < 4; i++){
        pipe(vectorPipesP_Jx[i]);
    }
}

/*
Nombre:  manejoPipes
Recibe:
        id_jugador: ID del jugador que llama a la funcion.
Retorna: void.
Hace: Cierra el fd[READ] o fd[WRITE], dependiendo si el proceso los ocupa o no (ya que las pipes son unidireccionales).
*/

void manejoPipes(int id_jugador){
    if (id_jugador == -1){
        for(int i = 0; i < 4; i++){
            close(vectorPipesJx_P[i][WRITE]);
            close(vectorPipesP_Jx[i][READ]);
        }
    }
    else if(id_jugador == 0){
        close(pipeJ0_P[READ]);
        close(pipeP_J0[WRITE]);
    }
    else if(id_jugador == 1){
        close(pipeJ1_P[READ]);
        close(pipeP_J1[WRITE]);
    }
    else if(id_jugador == 2){
        close(pipeJ2_P[READ]);
        close(pipeP_J2[WRITE]);
    }
    else if(id_jugador == 3){
        close(pipeJ3_P[READ]);
        close(pipeP_J3[WRITE]);
    }
}

/*
Nombre:  cerrarPipes
Recibe:
         idJugador: ID del jugador que llama la funcion.
Hace: cierra las pipes restantes, para que no queden en memoria.
*/

void cerrarPipes(int idJugador){
    if (idJugador == -1){
        for(int i = 0; i < 4; i++){
            close(vectorPipesJx_P[i][READ]);
            close(vectorPipesP_Jx[i][WRITE]);
        }
    }
    else if (idJugador == 0){
        close(pipeJ0_P[WRITE]);
        close(pipeP_J0[READ]);
    }
    else if (idJugador == 1){
        close(pipeJ1_P[WRITE]);
        close(pipeP_J1[READ]);
    }
    else if (idJugador == 2){
        close(pipeJ2_P[WRITE]);
        close(pipeP_J2[READ]);
    }
    else if (idJugador == 3){
        close(pipeJ3_P[WRITE]);
        close(pipeP_J3[READ]);
    }
}

/*
Nombre:  
Recibe:
        *id: Puntero que indica la id con la que se creara el hijo.
Retorna: void
Hace: Crea los 4 hijos (jugadores), cada uno con una id distinta.
*/

void crearHijos(int *id){
    for(int i = 0; i < 4; i++){
        if (fork() == 0){
            *id = i;
            break;
        }
    }
}