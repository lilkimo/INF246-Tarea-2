#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <stdint.h>

#include <sys/mman.h>

#define PAGESIZE 4096

int v = 5;

uint8_t *crearMemoria(int tamano){
    return mmap(NULL, tamano, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

int main() {
    //uint8_t *shared_memory = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    uint8_t *bloque1 = crearMemoria(PAGESIZE);
    uint8_t *bloque2 = crearMemoria(PAGESIZE);
    uint8_t *bloque3 = crearMemoria(PAGESIZE);
    *bloque1 = 34;
    *bloque2 = 35;
    *bloque3 = 36;

    if (fork() == 0) {
        v = 80;
    }
    else {
        *bloque1 = 40;
        wait(NULL);
    }
    printf("Not shared. %d\n", v);
    printf("Shared. %d %d %d\n", *bloque1, *bloque2, *bloque3);
}