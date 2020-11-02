
# Integrantes
Camilo Gonzalez, 201873550-7

Zarko Kuljis, 201823523-7
# Uso
Ejecute el comando make all. Para manejar el programa escriba el turno en el que quiera comenzar, luego, el juego comenzara y se detendra para preguntar si quiere ejecutar el efecto. En cada turno se imprimira el tablero, las posiciones y la cola. Al finalizar el juego, se mostrara al ganador.
# Consideraciones
Se asume que el orden de los bots siempre sera el mismo, no importa el juego.

# Implementacion de la comunicacion.
Usamos Pipes para avisar a un proceso hijo que es su turno, y avisar de vuelta al GameMaster (proceso padre) que el turno de un jugador termino.
Usamos memoria compartida para guardar 4 variables:
1. El tablero, para que todos los procesos supieran que efecto activar o no.
2. Las posiciones de los jugadores, para que el jugador que esta jugando realizara los efectos necesarios sobre los demas jugadores.
3. El sentido, para que los jugadores supieran en que direccion moverse.
4. El termino del juego.
