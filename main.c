#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tablero.c" //cambiar por tablero.h
#include "comunicacion.h"

int tirarDado() {
    srand(getpid());
    return (rand()%6) + 1;
}



casilla tablero[] = {0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 0, 0, 0, 0, 1, 2, 1, 2, 1, 2, 1, 0};
int posiciones[] = {0, 0, 0, 0}; // Posiciones de los Jugadores.
int sentido = 1; // -1: Inverso, 1: Normal.

int main() {

    mensaje vectorMensajesP_Jx[] = {0, 0, 0, 0};
    mensaje vectorMensajesJx_P[] = {0, 0, 0, 0};

    int idProceso = -1;
    int jugadorActual;
    int posJugador;
    int flag = 1;
    queue *colaTurnos = newqueue(CANTIDADJUGADORES);

    casilla *ptrTablero = crearMemoriaCompartida(sizeof(tablero));
    int *ptrPosiciones = crearMemoriaCompartida(sizeof(posiciones));
    int *ptrSentido = crearMemoriaCompartida(sizeof(sentido));
    int *ptrFlag = crearMemoriaCompartida(sizeof(flag));

    memcpy(ptrTablero, tablero, sizeof(tablero));
    memcpy(ptrPosiciones, posiciones, sizeof(posiciones));
    *ptrSentido = sentido;
    *ptrFlag = flag;

    printf("Ingrese el lugar en el que quiere ingresar: \n");
    scanf("%d", &posJugador);
    posJugador = posJugador - 1; 
    for (int i = 0, j = 1; i < CANTIDADJUGADORES; i++) {
        if (i == posJugador)
            enqueue(colaTurnos, 0);
        else
            enqueue(colaTurnos, j++);
    }
    
    printqueue(colaTurnos);

    crearPipes();
    crearHijos(&idProceso);
    manejoPipes(idProceso);

    if (idProceso == -1){
        for (int i = 0; i < CANTIDADJUGADORES; i++){
            write(vectorPipesP_Jx[i][WRITE], &vectorMensajesP_Jx[i], 1);
        }
    }
    else {
        write(vectorPipesJx_P[idProceso][WRITE], &vectorMensajesJx_P[idProceso], 1);
    }
    //printf("[%d, %d, %d, %d]\n",vectorMensajesP_Jx[0],vectorMensajesP_Jx[1],vectorMensajesP_Jx[2],vectorMensajesP_Jx[3]);
    //printf("[%d, %d, %d, %d]\n",vectorMensajesJx_P[0],vectorMensajesJx_P[1],vectorMensajesJx_P[2],vectorMensajesJx_P[3]);
    
    while(*ptrFlag){
        if (idProceso == -1) {
            jugadorActual = dequeue(colaTurnos);
            enqueue(colaTurnos, jugadorActual);

            int turnoEnEjecucion = 1;

            vectorMensajesP_Jx[jugadorActual] = 1;
            write(vectorPipesP_Jx[jugadorActual][WRITE], &vectorMensajesP_Jx[jugadorActual], 1);
            //printf("VM1:[%d, %d, %d, %d]\n",vectorMensajesP_Jx[0],vectorMensajesP_Jx[1],vectorMensajesP_Jx[2],vectorMensajesP_Jx[3]); //borrar
            while (turnoEnEjecucion){
                read(vectorPipesJx_P[jugadorActual][READ], &vectorMensajesJx_P[jugadorActual], 1);
                if (vectorMensajesJx_P[jugadorActual] == 1) {
                    while (turnoEnEjecucion){
                        read(vectorPipesJx_P[jugadorActual][READ], &vectorMensajesJx_P[jugadorActual], 1);
                        turnoEnEjecucion = 0;
                    }
                    vectorMensajesP_Jx[jugadorActual] = 0;
                    write(vectorPipesP_Jx[jugadorActual][WRITE], &vectorMensajesP_Jx, 1);
                }
            }
            int final = CANTIDADCASILLAS - 1;
            if (*ptrSentido == -1){
                int final = 0;
            }

            for (int i = 0; i < CANTIDADJUGADORES; i++){
                if (ptrPosiciones[i] == final){
                    printf("El ganador del juego es %d\n", i);
                    *ptrFlag = 0;
                    break;
                }
            }

        }
        else{
            int esperandoTurno = 1;
            while(esperandoTurno){
                read(vectorPipesP_Jx[idProceso][READ], &vectorMensajesP_Jx[idProceso], 1);
                if (vectorMensajesP_Jx[idProceso] == 1){
                    esperandoTurno = 0;
                }
            }

            vectorMensajesJx_P[idProceso] = 1;
            write(vectorPipesJx_P[idProceso][WRITE], &vectorMensajesJx_P[idProceso], 1);


            casilla casilla = mover(idProceso, tirarDado()*(*ptrSentido), ptrTablero, ptrPosiciones);
            if (casilla){
                ejecutarEfecto(casilla, idProceso, ptrTablero, ptrPosiciones, ptrSentido, colaTurnos);
            }
            vectorMensajesJx_P[idProceso] = 0;
            write(vectorPipesJx_P[idProceso][WRITE], &vectorMensajesJx_P[idProceso], 1);
        }
    }




    /*cerrarPipes(idProceso);
    if (idProceso == 0 || idProceso == 1 || idProceso == 2 || idProceso == 3)
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
    printf("El juego ha terminado, el ganador es el jugador numero %d\n", ganador);*/
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