#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tablero.c" //cambiar por tablero.h
#include "comunicacion.h"

int tirarDado() {
    srand(getpid());
    return (rand()%6) + 1;
}

int ejecutarTurno(int jugadorActual, casilla *ptrTablero, int *ptrPosiciones, int *ptrSentido, queue *colaTurnos) {
    int flag;
    int mensaje;
    int dado;
    char decision[2];
    casilla casilla;
    //write(pipeJ0_P[WRITE], 2, 1);*
    mensaje = 2;
    write(vectorPipesJx_P[jugadorActual][WRITE], &mensaje, 1);
    dado = tirarDado();
    printf("Salio un %d\n", dado);
    casilla = mover(jugadorActual, dado, ptrTablero, ptrPosiciones);
    if (*ptrSentido == 1) {
        if (ptrPosiciones[jugadorActual] == CANTIDADCASILLAS)
            flag = 0;
        else {
            if (casilla == 0) {
                //write(pipeJ0_P[WRITE], 1, 0);
                mensaje = 1;
                write(vectorPipesJx_P[jugadorActual][WRITE], &mensaje, 0);
            }
            else {
                if (jugadorActual == 0) {
                    printf("Desea ejecutar el efecto? Escriba 'Si' o 'No' \n");
                    scanf("%s", decision);
                    if (strcmp(decision,"Si") == 0)
                        ejecutarEfecto(casilla, jugadorActual, ptrTablero, ptrPosiciones, ptrSentido, colaTurnos);
                    else{
                        mensaje = 1;
                        write(vectorPipesJx_P[jugadorActual][WRITE], &mensaje, 1);
                    }
                }
                else {
                    mensaje = 1;
                    ejecutarEfecto(casilla, jugadorActual, ptrTablero, ptrPosiciones, ptrSentido, colaTurnos);
                    write(vectorPipesJx_P[jugadorActual][WRITE], &mensaje, 1);
                }
            }
        }
    }
    else {
        if (ptrPosiciones[jugadorActual] == 0)
            flag = 0;
        else {
            if (casilla == 0){
                //write(pipeJ0_P[WRITE], 1, 0);
                mensaje = 1;
                write(vectorPipesJx_P[jugadorActual][WRITE], &mensaje, 0);
            }
            else {
                printf("Desea ejecutar el efecto? Escriba 'Si' o 'No'. \n");
                scanf("%s", decision);
                if (strcmp(decision,"Si") == 0)
                    ejecutarEfecto(casilla, jugadorActual, ptrTablero, ptrPosiciones, ptrSentido, colaTurnos);
                else {
                    mensaje = 1;
                    write(vectorPipesJx_P[jugadorActual][WRITE], &mensaje, 1);
                }
            }
        }
    }
    return flag;
}

casilla tablero[] = {0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 0, 0, 0, 0, 1, 2, 1, 2, 1, 2, 1, 0};
int posiciones[] = {0, 0, 0, 0}; // Posiciones de los Jugadores.
int sentido = 1; // -1: Inverso, 1: Normal.

int main() {

    mensaje mensajeP_J0 = -1;
    mensaje mensajeP_J1 = -1;
    mensaje mensajeP_J2 = -1;
    mensaje mensajeP_J3 = -1;
    mensaje mensajeJ0_P = -1;
    mensaje mensajeJ1_P = -1;
    mensaje mensajeJ2_P = -1;
    mensaje mensajeJ3_P = -1;

    mensaje vectorMensajesP_Jx[] = {mensajeP_J0, mensajeP_J1, mensajeP_J2, mensajeP_J3};
    mensaje vectorMensajesJx_P[] = {mensajeJ0_P, mensajeJ1_P, mensajeJ2_P, mensajeJ3_P};

    int idJugador = -1;
    int jugadorActual;
    int posJugador;
    int flag = 1;
    queue *colaTurnos = newqueue(4);

    casilla *ptrTablero = crearMemoriaCompartida(sizeof(tablero));
    int *ptrPosiciones = crearMemoriaCompartida(sizeof(posiciones));
    int *ptrSentido = crearMemoriaCompartida(sizeof(sentido));
    int *ptrFlag = crearMemoriaCompartida(sizeof(flag));

    memcpy(ptrTablero, tablero, sizeof(tablero));
    memcpy(ptrPosiciones, posiciones, sizeof(posiciones));
    *ptrSentido = sentido;
    *ptrFlag = flag;

    printf("Ingrese el lugar en el que quiere ingresar: ");
    scanf("%d", &posJugador);
    switch (posJugador)
    {
    case 1:
        enqueue(colaTurnos, 0);
        enqueue(colaTurnos, 1);
        enqueue(colaTurnos, 2);
        enqueue(colaTurnos, 3);
        break;
    case 2:
        enqueue(colaTurnos, 1);
        enqueue(colaTurnos, 0);
        enqueue(colaTurnos, 2);
        enqueue(colaTurnos, 3);
        break;
    case 3:
        enqueue(colaTurnos, 1);
        enqueue(colaTurnos, 2);
        enqueue(colaTurnos, 0);
        enqueue(colaTurnos, 3);
        break;
    case 4:
        enqueue(colaTurnos, 1);
        enqueue(colaTurnos, 2);
        enqueue(colaTurnos, 3);
        enqueue(colaTurnos, 0);
        break;
    
    default:
        printf("error, solo puede ser < 4");
        exit(0);
        break;
    }

    crearPipes();
    crearHijos(&idJugador);
    manejoPipes(idJugador);

    if (idJugador == -1){
        printf("La cola de turnos: ");
        printqueue(colaTurnos);
        jugadorActual = dequeue(colaTurnos);
        enqueue(colaTurnos, jugadorActual);
        if (jugadorActual == 0)
            printf("Es tu turno\n");
        else {
            printf("Es el turno del bot %d\n", jugadorActual);
        }
    }

    while (*ptrFlag) {
        if (idJugador == -1) {
            for (int i = 0; i < 4; i++) {
                read(vectorPipesJx_P[i][READ], &vectorMensajesJx_P[i], 1);
            }
            /*read(pipeJ0_P[READ], &mensajeJ0_P, 1);
            read(pipeJ0_P[READ], &mensajeJ1_P, 1);
            read(pipeJ0_P[READ], &mensajeJ2_P, 1);
            read(pipeJ0_P[READ], &mensajeJ3_P, 1);*/
            if (mensajeJ0_P == 1 || mensajeJ1_P == 1 || mensajeJ2_P == 1 || mensajeJ3_P == 1) {
                jugadorActual = dequeue(colaTurnos);
                enqueue(colaTurnos, jugadorActual);
                printf("Es el turno del jugador %d\n", jugadorActual+1);
            }
            if (jugadorActual == 0) {
                for (int i = 0; i < 4; i++){
                    if (i == jugadorActual) {
                        vectorMensajesP_Jx[i] = 1;
                        write(vectorPipesP_Jx[i][WRITE], &vectorMensajesP_Jx[i], 1);
                    }
                    else {
                        vectorMensajesP_Jx[i] = 0;
                        write(vectorPipesP_Jx[i][WRITE], &vectorMensajesP_Jx[i], 1);
                    }
                }
                /*write(pipeP_J0[WRITE], 1, 1);
                write(pipeP_J1[WRITE], 0, 1);
                write(pipeP_J2[WRITE], 0, 1);
                write(pipeP_J3[WRITE], 0, 1);*/
            }
            else if (jugadorActual == 1) {
                for (int i = 0; i < 4; i++){
                    if (i == jugadorActual) {
                        vectorMensajesP_Jx[i] = 1;
                        write(vectorPipesP_Jx[i][WRITE], &vectorMensajesP_Jx[i], 1);
                    }
                    else {
                        vectorMensajesP_Jx[i] = 0;
                        write(vectorPipesP_Jx[i][WRITE], &vectorMensajesP_Jx[i], 1);
                    }
                }
                /*write(pipeP_J0[WRITE],0 , 1);
                write(pipeP_J1[WRITE],1 , 1);
                write(pipeP_J2[WRITE],0 , 1);
                write(pipeP_J3[WRITE],0 , 1);*/
            }
            else if (jugadorActual == 2) {
                for (int i = 0; i < 4; i++){
                    if (i == jugadorActual) {
                        vectorMensajesP_Jx[i] = 1;
                        write(vectorPipesP_Jx[i][WRITE], &vectorMensajesP_Jx[i], 1);
                    }
                    else {
                        vectorMensajesP_Jx[i] = 0;
                        write(vectorPipesP_Jx[i][WRITE], &vectorMensajesP_Jx[i], 1);
                    }
                }
                /*write(pipeP_J0[WRITE],0 , 1);
                write(pipeP_J1[WRITE],0 , 1);
                write(pipeP_J2[WRITE],1 , 1);
                write(pipeP_J3[WRITE],0 , 1);*/
            }
            else {
                for (int i = 0; i < 4; i++){
                    if (i == jugadorActual) {
                        vectorMensajesP_Jx[i] = 1;
                        write(vectorPipesP_Jx[i][WRITE], &vectorMensajesP_Jx[i], 1);
                    }
                    else {
                        vectorMensajesP_Jx[i] = 0;
                        write(vectorPipesP_Jx[i][WRITE], &vectorMensajesP_Jx[i], 1);
                    }
                }
                /*write(pipeP_J0[WRITE],0 , 1);
                write(pipeP_J1[WRITE],0 , 1);
                write(pipeP_J2[WRITE],0 , 1);
                write(pipeP_J3[WRITE],1 , 1);*/
            }
        }
        else if (idJugador == 0) {
            read(pipeP_J0[READ], &mensajeP_J0, 1);
            if (mensajeJ0_P == 1) {
                *ptrFlag = ejecutarTurno(jugadorActual, ptrTablero, ptrPosiciones, ptrSentido, colaTurnos);
            }
            else {
                vectorMensajesJx_P[jugadorActual] = 0;
                write(pipeJ0_P[WRITE], &vectorMensajesJx_P[jugadorActual], 1);
            }
            printf("El jugador %d ha terminado su turno\n",jugadorActual+1);
            printf("La cola de turnos: ");
            printqueue(colaTurnos);
        }
        else if (idJugador == 1) {
            read(pipeJ1_P[READ], &mensajeJ1_P, 1);
            if (mensajeJ1_P == 1) {
                *ptrFlag = ejecutarTurno(jugadorActual, ptrTablero, ptrPosiciones, ptrSentido, colaTurnos);
            }
            else {
                vectorMensajesJx_P[jugadorActual] = 0;
                write(pipeJ1_P[WRITE], &vectorMensajesJx_P[jugadorActual], 1);
            }
            printf("El jugador %d ha terminado su turno\n",jugadorActual+1);
            printf("La cola de turnos: ");
            printqueue(colaTurnos);
        }
        else if (idJugador == 2) {
            read(pipeJ2_P[READ], &mensajeJ2_P, 1);
            if (mensajeJ0_P == 1) {
                *ptrFlag = ejecutarTurno(jugadorActual, ptrTablero, ptrPosiciones, ptrSentido, colaTurnos);
            }
            else {
                vectorMensajesJx_P[jugadorActual] = 0;
                write(pipeJ2_P[WRITE], &vectorMensajesJx_P[jugadorActual], 1);
            }
            printf("El jugador %d ha terminado su turno\n",jugadorActual+1);
            printf("La cola de turnos: ");
            printqueue(colaTurnos);
        }
        else if (idJugador == 3) {
            read(pipeJ3_P[READ], &mensajeJ3_P, 1);
            if (mensajeJ3_P == 1) {
                *ptrFlag = ejecutarTurno(jugadorActual, ptrTablero, ptrPosiciones, ptrSentido, colaTurnos);
            }
            else {
                vectorMensajesJx_P[jugadorActual] = 0;
                write(pipeJ3_P[WRITE], &vectorMensajesJx_P[jugadorActual], 1);
            }
            printf("El jugador %d ha terminado su turno\n",jugadorActual+1);
            printf("La cola de turnos: ");
            printqueue(colaTurnos);
        }
    }
    cerrarPipes(idJugador);
    if (idJugador == 0 || idJugador == 1 || idJugador == 2 || idJugador == 3)
        exit(1);
    jugador ganador;
    for (int i = 0; i < CANTIDADJUGADORES; i++){
        if (*ptrSentido == 1){
            if (ptrPosiciones[i] == CANTIDADCASILLAS) {
                ganador = i+1;
                break;
            }
        }
        else {
            if (ptrPosiciones[i] == 0) {
                ganador = i+1;
                break;  
            }
        }
    }
    printf("El juego ha terminado, el ganador es el jugador numero %d", ganador);
    /*// BEGIN ejemplo*
    
    queue *colaTurnos = newqueue(4);
    enqueue(colaTurnos, 0);
    enqueue(colaTurnos, 1);
    enqueue(colaTurnos, 2);
    enqueue(colaTurnos, 3);

    jugador jugadorActual = 0;

    printqueue(colaTurnos);
    ejecutarEfecto(1, jugadorActual, tablero, posiciones, &sentido, colaTurnos);
    printqueue(colaTurnos);
    //END ejemplo */

    return 0;
}