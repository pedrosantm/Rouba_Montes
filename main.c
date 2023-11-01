#include <stdio.H>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "oprecoes_pilha.h"


typedef struct Carta {
    int numero;
    char nipe;
}carta;

typedef struct Pilha {
    struct Carta cartas[52];
    int topo;
}pilha;


typedef struct jogador{
    char nome[50];
    int numero_de_cartas;
}jogador;







int main() {
    
    return 0;
}
