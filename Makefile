all: programa
	./programa

programa: main.o comunicacion.o queue.o tablero.o
	gcc -o programa main.o comunicacion.o tablero.o queue.o

main.o: main.c
	gcc -c main.c

comunicacion.o: comunicacion.c comunicacion.h
	gcc -c comunicacion.c -o comunicacion.o

tablero.o: tablero.c tablero.h
	gcc -c tablero.c -o tablero.o

queue.o: queue.c queue.h
	gcc -c queue.c -o queue.o

clean:
	rm -f programa main.o comunicacion.o tablero.o queue.o