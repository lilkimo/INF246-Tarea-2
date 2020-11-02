#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tablero.h"
#include "comunicacion.h"

/*
Nombre:  tirarDado
Recibe:  void.
Retorna: int dado.   
Hace:    lanza un dado de 6 caras, retorna la cara que salio.
*/

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

    printf("Ingrese el lugar en el que quiere ingresar:\n");
    scanf("%d", &posJugador);
    posJugador = posJugador - 1; 
    for (int i = 0, j = 1; i < CANTIDADJUGADORES; i++) {
        if (i == posJugador)
            enqueue(colaTurnos, 0);
        else
            enqueue(colaTurnos, j++);
    }

    crearPipes();
    crearHijos(&idProceso);
    manejoPipes(idProceso);

    if (idProceso == -1)
        for (int i = 0; i < CANTIDADJUGADORES; i++)
            write(vectorPipesP_Jx[i][WRITE], &vectorMensajesP_Jx[i], 1);
    else 
        write(vectorPipesJx_P[idProceso][WRITE], &vectorMensajesJx_P[idProceso], 1);
    
    while (*ptrFlag) {
        if (idProceso == -1) {
            jugadorActual = dequeue(colaTurnos);
            if (jugadorActual == 0)
                printf("¡Es tu turno!\n");
            else
                printf("¡Es turno del bot %d!\n", jugadorActual);
            enqueue(colaTurnos, jugadorActual);

            int turnoEnEjecucion = 1;

            vectorMensajesP_Jx[jugadorActual] = 1;
            write(vectorPipesP_Jx[jugadorActual][WRITE], &vectorMensajesP_Jx[jugadorActual], 1);
            
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
            printtablero(ptrTablero, ptrPosiciones, *ptrSentido);
            int final = CANTIDADCASILLAS - 1;
            if (*ptrSentido == -1){
                int final = 0;
            }

            for (int i = 0; i < CANTIDADJUGADORES; i++){
                if (ptrPosiciones[i] == final) {
                    if (i == 0)
                        printf("¡Has ganado el juego!\n");
                    else
                        printf("¡El bot %d ha ganado el juego!\n", i);
                    *ptrFlag = 0;
                    break;
                }
            }
            printf("====================================================================================================================\n");

        }
        else {
            int esperandoTurno = 1;
            while(esperandoTurno){
                read(vectorPipesP_Jx[idProceso][READ], &vectorMensajesP_Jx[idProceso], 1);
                if (vectorMensajesP_Jx[idProceso] == 1){
                    esperandoTurno = 0;
                }
            }

            vectorMensajesJx_P[idProceso] = 1;
            write(vectorPipesJx_P[idProceso][WRITE], &vectorMensajesJx_P[idProceso], 1);

            int dado = tirarDado();
            if (idProceso == 0)
                printf("Has sacado un %d\n", dado);
            else
                printf("El Bot %d saco un: %d\n", idProceso, dado);
            
            casilla casilla = mover(idProceso, dado*(*ptrSentido), ptrTablero, ptrPosiciones);
            if (casilla) {
                if (idProceso == 0) {
                    char opcion[3];
                    printf("Ha caido en una casilla especial, ¿Desea ejecutar el efecto [si/no]?\n");
                    scanf("%s", opcion);
                    if (strcmp(opcion, "si") == 0)
                        ejecutarEfecto(casilla, idProceso, ptrTablero, ptrPosiciones, ptrSentido, colaTurnos);
                    else if (strcmp(opcion, "no") == 0)
                        printf("No se ha ejecutado el efecto\n");
                    else {
                        printf("Respuesta inválida, cerrando el programa...\n");
                        exit(1);
                    }
                }
                else
                    ejecutarEfecto(casilla, idProceso, ptrTablero, ptrPosiciones, ptrSentido, colaTurnos);
            }
            vectorMensajesJx_P[idProceso] = 0;
            write(vectorPipesJx_P[idProceso][WRITE], &vectorMensajesJx_P[idProceso], 1);
            
        }
    }
    return 0;
}
