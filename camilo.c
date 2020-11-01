#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

void pipesCreation(){
    pipe(pipeJ0_P);
    pipe(pipeJ1_P);
    pipe(pipeJ2_P);
    pipe(pipeJ3_P);
    pipe(pipeP_J0);
    pipe(pipeP_J1);
    pipe(pipeP_J2);
    pipe(pipeP_J3);
}

void pipesManagement(int id_jugador){
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

int main(){
    char mensaje[255];
    int flag = 1;
    int id_jugador = -1;
    int bytes = 0;
    crearHijos(&id_jugador);
    pipesCreation();
    pipesManagement(id_jugador);
    if (id_jugador > 0){
        exit(0);
    }
    printf("ID: %d\n", id_jugador);
    if (id_jugador == -1){
        while(bytes == 0){
            bytes = read(pipeJ0_P[READ], mensaje, sizeof(mensaje));
        }
        printf("el mensaje es: %s\n",mensaje);
    }
    printf("ID2: %d\n",id_jugador);
    if(id_jugador == 0){
        printf("AAA");
        write(pipeJ0_P[WRITE],"abcde", 6);
    }
    return 0;
}

