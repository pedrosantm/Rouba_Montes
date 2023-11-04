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
        baralho->cartas[baralho->topo] = carta;
        baralho->topo++;
    }
    return ;
}


carta desempilhar_baralho(pilha *baralho){
    baralho->topo--;
    return baralho->cartas[baralho->topo];
}

void insere_lista(lista* l, carta c){
    elemento* novo = (elemento*)malloc(sizeof(elemento));
    novo->carta = c;    
    novo->anterior = NULL;
    if(l->inicio == NULL) 
        l->inicio = novo;
    else{
        elemento* aux = l->inicio;
        while (aux->anterior != NULL) {
            aux = aux->anterior;
    }
    aux->anterior = novo;
   }
   return;
}

void insere_monte_jogador(jogador* j, carta c){
    elemento* novo = (elemento*)malloc(sizeof(elemento));//ponteiro para novo elemento
    if(novo!=NULL){
        novo->carta = c;//a parte carta do novo elemento recebendo o valor passado por paramentro na função
        novo->anterior = j->monte.topo;//parte anterior do novo elemento recebe o antigo topo do monte
        j->monte.topo= novo;//o topo é atualizado recebendo o novo elemento
    }
    return;
}


void print_lista(lista* cartas_mesa){
    elemento* aux = cartas_mesa->inicio;
     while(aux != NULL){
            printf("|| %d   %c ||  ", aux->carta.numero, aux->carta.nipe);
            aux = aux->anterior;
    }
    return;
}

