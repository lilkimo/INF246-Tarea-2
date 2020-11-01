#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>

#define PAGESIZE 4096

int v = 5;

void *crearMemoria(int tamano){
    return mmap(NULL, tamano, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

int main() {
    //uint8_t *shared_memory = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int *bloque1 = crearMemoria(sizeof(int)*4);
    uint8_t *bloque2 = crearMemoria(PAGESIZE);
    uint8_t *bloque3 = crearMemoria(PAGESIZE);
    int arreglo[] = {1,2,3,4};
    memcpy(bloque1,arreglo,sizeof(int)*4);
    *bloque2 = 35;
    *bloque3 = 36;

    if (fork() == 0) {
        v = 80;
        for (int i = 0; i<4; i++) {
            //printf("%d\n",bloque1[i]);
        }
        bloque1[1] = 4;
    }
    else {
        wait(NULL);
        for (int i = 0; i<4; i++) {
            printf("%d\n",bloque1[i]);
        }
    }
    //printf("Not shared. %d\n", v);
    //printf("Shared. %d %d\n", *bloque2, *bloque3);    
}