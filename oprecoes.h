#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


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



///////////////////////////////


void inicializarPilha(pilha *baralho) {
    baralho->topo = -1;  // Inicializa a pilha vazia
}

void empilhar(pilha *baralho, carta carta) {
    if (baralho->topo < 52 - 1) {
        baralho->cartas[++(baralho->topo)] = carta;
    }
}

