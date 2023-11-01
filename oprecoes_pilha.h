#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>



void inicializarPilha(pilha *baralho) {
    baralho->topo = -1;  // Inicializa a pilha vazia
}

void empilhar(pilha *baralho, carta carta) {
    if (baralho->topo < 52 - 1) {
        baralho->cartas[++(baralho->topo)] = carta;
    }
}

