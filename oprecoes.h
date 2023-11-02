#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>


typedef struct Carta {
    int numero;
    char nipe;
}carta;

typedef struct Pilha {
    struct Carta cartas[52];
    int topo;
}pilha;

typedef struct elemento{//estruct para definição do elemento
    carta carta;
    struct elemento* anterior;
}elemento;

typedef struct pilha_dinamica{//pilha dinamica para representar cada monte de um jogador jogador
    elemento* topo;
}pilha_dinamica;

typedef struct{
    elemento* inicio;
}lista;

typedef struct jogador{
    char nome[50];
    pilha_dinamica monte;
    lista cartas_jogaveis;
    int numero_de_cartas;
}jogador;



///////////////////////////////


void inicializarPilha(pilha *baralho) {
    baralho->topo = -1;
    return; // Inicializa a pilha vazia
}



void embaralharPilha(pilha *baralho) {
    
    srand(time(NULL));
    
    // Embaralha a pilha 
    for (int i = baralho->topo - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        carta temp = baralho->cartas[i];
        baralho->cartas[i] = baralho->cartas[j];
        baralho->cartas[j] = temp;
    }
    return;
}


void empilhar_baralho(pilha *baralho, carta carta) {
    if (baralho->topo < 52 - 1) {
        baralho->cartas[++(baralho->topo)] = carta;
    }
    return ;
}

