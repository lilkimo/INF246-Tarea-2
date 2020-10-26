#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//para la creacion de hijos
#include <unistd.h> 

//para el manejo de memoria compartida
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>          

#define CANTIDADJUGADORES 4
#define CANTIDADCASILLAS 29
#define KEY 1200
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

void crearHijos(){
    int id_jugador;

    for(int i = 0; i < 4; i++){
        if (fork() == 0){
            id_jugador = i;
            printf("hijo %d creado\n",id_jugador);
            break;
        }
    }
}

int main() {

    int fd_tablero, fd_posiciones, status;
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
    memcpy(ptr_posiciones, posiciones, sizeof(posiciones));

    crearHijos();   




    close(fd_tablero);
    close(fd_posiciones);
    return 0;
}