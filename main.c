#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//para la creacion de hijos
#include <unistd.h> 

//para el manejo de memoria compartida
#include <sys/stat.h>
#include <sys/mman.h>
#include <wait.h>      

#include "queue.c"

#define CANTIDADJUGADORES 4
#define CANTIDADCASILLAS 29
#define READ 0
#define WRITE 1

int pipeJ0_P[2];
int pipeJ1_P[2];
int pipeJ2_P[2];
int pipeJ3_P[2];
int pipeP_J0[2];
int pipeP_J1[2];
int pipeP_J2[2];
int pipeP_J3[2]; 

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

int main() {
    srand(2);
    int id_jugador = -1;

    /*int fd_tablero, fd_posiciones, status;
    int *ptr_tablero, *ptr_posiciones;
    
    fd_tablero = shmget(ftok("/bin/cat", KEY), sizeof(tablero), 0777 | IPC_CREAT);
    fd_posiciones = shmget(ftok("/bin/chmod", KEY), sizeof(posiciones), 0777 | IPC_CREAT);
    if (fd_tablero == -1 || fd_posiciones == -1){
        printf("Error, memoria compartida no pudo ser creada\n");
    }

    ptr_tablero = shmat(fd_tablero, 0, 0);
    ptr_posiciones = shmat(fd_posiciones, 0, 0);
    if (ptr_tablero == NULL || ptr_posiciones == NULL){
        printf("ERROR AL MAPEAR LA S.M.");
    }

    memcpy(ptr_tablero, tablero, sizeof(tablero));
    memcpy(ptr_posiciones, posiciones, sizeof(posiciones));*/

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


    //close(fd_tablero);
    //close(fd_posiciones);
    return 0;
}