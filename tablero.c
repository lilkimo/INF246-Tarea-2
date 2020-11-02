#include "tablero.h"

/*
Nombre:  mover
Recibe:
         jugador: El jugador que se desea mover.
         cantidad de casillas: La cantidad de casillas que se desea mover el jugador.
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
Retorna: El tipo de casilla en la que "cayó" el jugador.
Hace:    Mueve al jugador indicado en el tablero la cantidad de casillas indicada.
*/
casilla mover(const jugador jugador, const int cantidadCasillas, const casilla *tablero, int *posiciones) {
    int destino = posiciones[jugador] + cantidadCasillas;
    if (destino < 0)
        destino = 0;
    else if (destino >= CANTIDADCASILLAS)
        destino = CANTIDADCASILLAS - 1;
    
    posiciones[jugador] = destino;
    return tablero[destino];
}
/*
Nombre:  _1_1
Recibe:
         jugador: El jugador que ha ejecutado el efecto.
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
         sentido: Indica en qué dirección se mueven las piezas en el tablero.
         cola de turnos: Indica el orden en el que juegan los jugadores.
Retorna: Nada.
Hace:    Ejecuta el efecto: "El jugador retrocede una cuadrícula (La cuadrícula de inicio es lo máximo que puede retroceder)."
*/
void _1_1(const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos) {
    mover(jugadorActual, -*sentido, tablero, posiciones);
}

/*
Nombre:  _1_2
Recibe:
         jugador: El jugador que ha ejecutado el efecto.
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
         sentido: Indica en qué dirección se mueven las piezas en el tablero.
         cola de turnos: Indica el orden en el que juegan los jugadores.
Retorna: Nada.
Hace:    Ejecuta el efecto: "Los demás jugadores retroceden una cuadrícula (La cuadrícula de inicio es lo máximo que pueden retroceder)."
*/
void _1_2(const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos) {
    for (int i = 0; i < CANTIDADJUGADORES; i++) {
        if (i != jugadorActual)
            mover(i, -*sentido, tablero, posiciones);
    }
}

/*
Nombre:  _1_3
Recibe:
         jugador: El jugador que ha ejecutado el efecto.
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
         sentido: Indica en qué dirección se mueven las piezas en el tablero.
         cola de turnos: Indica el orden en el que juegan los jugadores.
Retorna: Nada.
Hace:    Ejecuta el efecto: "El jugador avanza una cuadrícula (si llega la cuadrícula de fin, este gana el juego)."
*/
void _1_3(const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos) {
    mover(jugadorActual, *sentido, tablero, posiciones);
}

/*
Nombre:  _1_4
Recibe:
         jugador: El jugador que ha ejecutado el efecto.
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
         sentido: Indica en qué dirección se mueven las piezas en el tablero.
         cola de turnos: Indica el orden en el que juegan los jugadores.
Retorna: Nada.
Hace:    Ejecuta el efecto: "El siguiente jugador no puede jugar su turno."
*/
void _1_4(const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos) {
    jugador siguienteJugador = dequeue(colaTurnos);
    enqueue(colaTurnos, siguienteJugador);
}

/*
Nombre:  _1_5
Recibe:
         jugador: El jugador que ha ejecutado el efecto.
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
         sentido: Indica en qué dirección se mueven las piezas en el tablero.
         cola de turnos: Indica el orden en el que juegan los jugadores.
Retorna: Nada.
Hace:    Ejecuta el efecto: "Cambio en el sentido de los turnos (si van del jugador 1 al 4, ahora sera del 4 al 1)"
*/
void _1_5(const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos) {
    // Siendo el turno del jugador 1, la cola de turnos nos queda [1,4,3,2]
    int colaActual[CANTIDADJUGADORES - 1];
    for (int i = 0; i < CANTIDADJUGADORES - 1; i++)
        colaActual[i] = dequeue(colaTurnos);
    for (int i = CANTIDADJUGADORES - 2; i >= 0; i--)
        enqueue(colaTurnos, colaActual[i]);
    // Al invertirla, obtenemos la cola [4,3,2,1], entonces, en el siguiente turno, volvería a ser turno del jugador 1.
    _1_4(jugadorActual, tablero, posiciones, sentido, colaTurnos); // Entonces lo saltamos.
}

/*
Nombre:  _2_1
Recibe:
         jugador: El jugador que ha ejecutado el efecto.
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
         sentido: Indica en qué dirección se mueven las piezas en el tablero.
         cola de turnos: Indica el orden en el que juegan los jugadores.
Retorna: Nada.
Hace:    Ejecuta el efecto: "Todos los jugadores retroceden 2 cuadrículas (La cuadrícula de inicio es lo máximo que puede retroceder)."
*/
void _2_1(const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos) {
    for (int i = 0; i < CANTIDADJUGADORES; i++)
        mover(i, *sentido * -2, tablero, posiciones);
}

/*
Nombre:  _2_2
Recibe:
         jugador: El jugador que ha ejecutado el efecto.
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
         sentido: Indica en qué dirección se mueven las piezas en el tablero.
         cola de turnos: Indica el orden en el que juegan los jugadores.
Retorna: Nada.
Hace:    Ejecuta el efecto: "Los demás jugadores avanzan hasta su próxima cuadrícula blanca (si no hay más cuadrículas blancas hacia
                            adelante, esto no tendrá efecto)."
*/
void _2_2(const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos) {
    for (int i = 0; i < CANTIDADJUGADORES; i++)
        if (jugadorActual != i) {
            if (*sentido == 1) {
                for (int j = posiciones[i] + 1; j < CANTIDADCASILLAS - 1; j++)
                    if (tablero[j] == 0) {
                        posiciones[i] = j;
                        break;
                    }
            }
            else {
                for (int j = posiciones[i] - 1; j > 0; j--)
                    if (tablero[j] == 0) {
                        posiciones[i] = j;
                        break;
                    }
            }
        }
}

/*
Nombre:  _2_3
Recibe:
         jugador: El jugador que ha ejecutado el efecto.
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
         sentido: Indica en qué dirección se mueven las piezas en el tablero.
         cola de turnos: Indica el orden en el que juegan los jugadores.
Retorna: Nada.
Hace:    Ejecuta el efecto: "El jugador cambia de posición con el jugador que va en ultimo lugar (si es el último, no produce efectos)."
*/
void _2_3(const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos) {
    jugador ultimoJugador = jugadorActual;
    casilla ultimoLugar = posiciones[jugadorActual];

    for (int i = 0; i < CANTIDADJUGADORES; i++)
        if (*sentido * posiciones[i] < *sentido * ultimoLugar) {
            ultimoLugar = posiciones[i];
            ultimoJugador = i;
        }
    posiciones[ultimoJugador] = posiciones[jugadorActual];
    posiciones[jugadorActual] = ultimoLugar;
}

/*
Nombre:  _2_4
Recibe:
         jugador: El jugador que ha ejecutado el efecto.
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
         sentido: Indica en qué dirección se mueven las piezas en el tablero.
         cola de turnos: Indica el orden en el que juegan los jugadores.
Retorna: Nada.
Hace:    Ejecuta el efecto: "El jugador cambia de posición con el jugador que va en primer lugar (si es el primero, no produce efectos)."
*/
void _2_4(const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos) {
    int sentidoInverso = -*sentido;
    _2_3(jugadorActual, tablero, posiciones, &sentidoInverso, colaTurnos);
}

/*
Nombre:  _2_5
Recibe:
         jugador: El jugador que ha ejecutado el efecto.
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
         sentido: Indica en qué dirección se mueven las piezas en el tablero.
         cola de turnos: Indica el orden en el que juegan los jugadores.
Retorna: Nada.
Hace:    Ejecuta el efecto: "Cambio en el sentido del tablero (Lo que era el inicio pasa a ser el final, y el final pasa a ser el inicio) y cambio
                            de tipo cuadrículas, las cuadrículas de tipo ”?” serán de tipo ”??”, mientras que las tipo ”??” serán tipo ”?”."
*/
void _2_5(const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos) {
    *sentido = -*sentido;
    for (int i = 0; i < CANTIDADCASILLAS; i++) {
        if (tablero[i] == 1)
            tablero[i] = 2;
        else if (tablero[i] == 2)
            tablero[i] = 1;
    }
}

efecto vectorEfectos1[] = {&_1_1, &_1_2, &_1_3, &_1_4, &_1_5};
efecto vectorEfectos2[] = {&_2_1, &_2_1, &_2_1, &_2_2, &_2_2, &_2_3, &_2_3, &_2_4, &_2_4, &_2_5};

/*
Nombre:  ejecutarEfecto
Recibe:
         tipo de casilla: Indica el tipo de casilla (? ó ??).
         jugador actual: El jugador que ha ejecutado el efecto.
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
         sentido: Indica en qué dirección se mueven las piezas en el tablero.
         cola de turnos: Indica el orden en el que juegan los jugadores.
Retorna: Nada.
Hace:    Ejecuta un efecto al azar del tipo de casilla indicado.
*/
void ejecutarEfecto(casilla tipoCasilla, const jugador jugadorActual, casilla *tablero, int *posiciones, int *sentido, queue *colaTurnos) {
    int efecto;
    if (tipoCasilla == 1) {
        efecto = rand()%5;
        vectorEfectos1[efecto](jugadorActual, tablero, posiciones, sentido, colaTurnos);
        printf("Se ejecutó el efecto 1.%d\n", efecto+1);
    }
    else if (tipoCasilla == 2) {
        efecto = rand()%10;
        vectorEfectos2[efecto](jugadorActual, tablero, posiciones, sentido, colaTurnos);
        
        if (efecto < 3)
            efecto = 1;
        else if (efecto < 5)
            efecto = 2;
        else if (efecto < 7)
            efecto = 3;
        else if (efecto < 9)
            efecto = 4;
        else
            efecto = 5;
        printf("Se ejecutó el efecto 2.%d\n", efecto);
    }
    else {
        printf("%d no es un tipo de casilla válido\n", tipoCasilla);
        exit(1);
    }
}

typedef struct posicion {
    int posicion;
    int cantidadJugadores;
    jugador jugadores[CANTIDADJUGADORES];
} posicion;

/*
Nombre:  cmpposicion
Recibe:
         a: El primer elemento.
         b: El segundo elemento.
Retorna: La diferencia entre a y b.
Hace:    Indica si un elemento del tipo posicion es mayor que otro.
*/
int cmpposicion (const void * a, const void * b) {
   return ( (*(posicion *)a).posicion - (*(posicion *)b).posicion );
}

/*
Nombre:  printtablero
Recibe:
         tablero: El tablero donde se juega.
         posiciones: Posiciones de todos los jugadores en el tablero.
         sentido: Indica en qué dirección se mueven las piezas en el tablero.
Retorna: Nada.
Hace:    Muestra el tablero en pantalla, indicando las posiciones de los jugadores en él.
*/
void printtablero(const casilla *tablero, const int *posiciones, const int sentido) {
    // BEGIN posiciones de los jugadores.
    posicion _posiciones[CANTIDADJUGADORES];
    int largo = 0, maxCantidadJugadores = 0;
    for (int i = 0, existe; i < CANTIDADJUGADORES; i++) {
        existe = 0;
        for (int j = 0; j < largo; j++) {
            if (posiciones[i] == _posiciones[j].posicion) {
                existe = 1;
                
                _posiciones[j].jugadores[_posiciones[j].cantidadJugadores++] = i;
                if (_posiciones[j].cantidadJugadores > maxCantidadJugadores)
                    maxCantidadJugadores = _posiciones[j].cantidadJugadores;
                
                break;
            }
        }
        if (!existe) {
            _posiciones[largo].posicion = posiciones[i];
            
            _posiciones[largo].cantidadJugadores = 0;
            _posiciones[largo].jugadores[_posiciones[largo].cantidadJugadores++] = i;
            if (_posiciones[largo].cantidadJugadores > maxCantidadJugadores)
                maxCantidadJugadores = _posiciones[largo].cantidadJugadores;
            largo++;
        }
    }
    qsort(_posiciones, largo, sizeof(posicion), cmpposicion);
    // END posiciones de los jugadores.

    int posicionActual;
    char *casilla;
    printf("[ I]");
    if (sentido == 1) {
        for (int i = 1; i < CANTIDADCASILLAS-1; i++) {
            if (tablero[i] == 0)
                casilla = "  ";
            else if (tablero[i] == 1)
                casilla = " ?";
            else if (tablero[i] == 2)
                casilla = "??";
            else
                casilla = " u"; // u de Unknown
            printf("[%s]", casilla);
        }
        printf("[ F]\n");
        posicionActual = 0;
        for (int i = 0; i < CANTIDADCASILLAS; i++) {
            if (_posiciones[posicionActual].posicion == i) {
                printf(" ^^ ");
                if (++posicionActual == largo)
                    break;
            }
            else
                printf("    ");
        }
        printf("\n");
        for (int i = 0; i < maxCantidadJugadores; i++) {
            posicionActual = 0;
            for (int j = 0; j < CANTIDADCASILLAS; j++) {
                if (_posiciones[posicionActual].posicion == j && _posiciones[posicionActual].cantidadJugadores > i) {
                    if (_posiciones[posicionActual].jugadores[i] == 0)
                        printf("jgdr");
                    else
                        printf("bot%d", _posiciones[posicionActual].jugadores[i]);
                    if (++posicionActual == largo)
                        break;
                }
                else
                    printf("    ");
            }
            printf("\n");
        }
    }
    // Esto es lo mismo que arriba pero con algúnos - por ahí.
    else if (sentido == -1) {
        for (int i = CANTIDADCASILLAS-2; i > 0; i--) {
            if (tablero[i] == 0)
                casilla = "  ";
            else if (tablero[i] == 1)
                casilla = " ?";
            else if (tablero[i] == 2)
                casilla = "??";
            else
                casilla = " u"; // u de Unknown
            printf("[%s]", casilla);
        }
        printf("[ F]\n");
        posicionActual = largo-1;
        for (int i = CANTIDADCASILLAS-1; i >= 0; i--) {
            if (_posiciones[posicionActual].posicion == i) {
                printf(" ^^ ");
                if (posicionActual-- == 0)
                    break;
            }
            else
                printf("    ");
        }
        printf("\n");
        for (int i = 0; i < maxCantidadJugadores; i++) {
            posicionActual = largo-1;
            for (int j = CANTIDADCASILLAS-1; j >= 0; j--) {
                if (_posiciones[posicionActual].posicion == j && _posiciones[posicionActual].cantidadJugadores > i) {
                    if (_posiciones[posicionActual].jugadores[i] == 0)
                        printf("jgdr");
                    else
                        printf("bot%d", _posiciones[posicionActual].jugadores[i]);
                    if (posicionActual-- == 0)
                        break;
                }
                else
                    printf("    ");
            }
            printf("\n");
        }
    }
}
