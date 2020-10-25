#include <unistd.h>
#include <stdio.h>



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

int main(){
    crearHijos();
    return 0;
}

