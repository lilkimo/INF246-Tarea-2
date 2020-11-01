#include "comunicacion.h"

int pipeJ0_P[2];
int pipeJ1_P[2];
int pipeJ2_P[2];
int pipeJ3_P[2];
int pipeP_J0[2];
int pipeP_J1[2];
int pipeP_J2[2];
int pipeP_J3[2];    

void* crearMemoriaCompartida(size_t size){
    int protection = PROT_READ | PROT_WRITE;
    int visibilty = MAP_SHARED | MAP_ANONYMOUS;
    return mmap(NULL, size, protection, visibilty, -1, 0);
}

void crearPipes(){
    pipe(pipeJ0_P);
    pipe(pipeJ1_P);
    pipe(pipeJ2_P);
    pipe(pipeJ3_P);
    pipe(pipeP_J0);
    pipe(pipeP_J1);
    pipe(pipeP_J2);
    pipe(pipeP_J3);
}

void manejoPipes(int id_jugador){
    if (id_jugador == -1){
        close(pipeJ0_P[WRITE]);
        close(pipeJ1_P[WRITE]);
        close(pipeJ2_P[WRITE]);
        close(pipeJ3_P[WRITE]);
        close(pipeP_J0[READ]);
        close(pipeP_J1[READ]);
        close(pipeP_J2[READ]);
        close(pipeP_J3[READ]);
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

void crearHijos(int *id){

    for(int i = 0; i < 4; i++){
        if (fork() == 0){
            *id = i;
            printf("hijo %d creado\n",*id);
            break;
        }
    }
}