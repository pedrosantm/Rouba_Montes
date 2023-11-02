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

void embaralharPilha(pilha *baralho) {
    
    srand(time(NULL));
    
    // Embaralha a pilha 
    for (int i = baralho->topo; i > 0; i--) {
        int j = rand() % (i + 1);
        carta temp = baralho->cartas[i];
        baralho->cartas[i] = baralho->cartas[j];
        baralho->cartas[j] = temp;
    }
}

void printPilha(pilha *baralho, int max) {

    int aux = baralho->topo;

    for(int i = 0; i < max; i++){
        printf("|| %d %c||\n", baralho->cartas->numero[aux], baralho->cartas->nipe);
        aux--;
    }

    return ;
}