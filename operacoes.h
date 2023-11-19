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
    struct elementto* prox;
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
    int numero_de_cartas;
}jogador;



///////////////////////////////
//inicialização


int inicializa_monte(pilha_dinamica* p){//cria o monte dos jogadores
    p->topo=0;
    if(p->topo==0)
        return 1;
    else
        return 0;
}

int inicializa_baralho(pilha *p){//cria o monte para o baralho
    p->topo=0;
    if(p->topo==0){
        return 1;
    }else
        return 0;
}

int inicializa_lista(lista* l){
    l->inicio = NULL;
    if(l->inicio==NULL)
        return 1;
    else 
        return 0;
}

int inicializa_num_de_cartas(jogador* j){
    j->numero_de_cartas = 0;
    if(j->numero_de_cartas == 0)
        return 1;
    else   
        return 0;
}




////////////////////////////////
///manipulações nas listas e pilhas


void embaralharPilha(pilha *baralho) {
    
    srand(time(NULL));
    
    // Embaralha a pilha 
    for (int i = baralho->topo - 1; i > 0; i--) {
        int j = rand() % 52;
        carta aux = baralho->cartas[i];
        baralho->cartas[i] = baralho->cartas[j];
        baralho->cartas[j] = aux;
    }
    return;
}


void empilhar_baralho(pilha *baralho, carta carta) {
        baralho->cartas[baralho->topo] = carta;
        baralho->topo++;
    return ;
}


carta desempilhar_baralho(pilha *baralho){
    baralho->topo--;
    return baralho->cartas[baralho->topo];
}

int insere_lista(lista* l, carta c){
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

    return 1;
}


void insere_monte_jogador(jogador* j, carta c){
    elemento* novo = (elemento*)malloc(sizeof(elemento));//ponteiro para novo elemento
    if(novo!=NULL){
        novo->carta = c;//a parte carta do novo elemento recebendo o valor passado por paramentro na função
        novo->anterior = j->monte.topo;//parte anterior do novo elemento recebe o antigo topo do monte
        j->monte.topo= novo;//o topo é atualizado recebendo o novo elemento
        j->numero_de_cartas++;
    }
    return;
}


carta pesquisa_indice(lista*l, int index){//função para retornar carna no indice indicado
    elemento* aux = l->inicio;
    int i = 0;
    while( i < index){
        aux = aux->anterior;
        i++; 
    }
     return aux->carta;
}

int verificacao(carta* c1, carta* c2){
    if(c1->numero == c2->numero)
        return 1;
    else 
        return 0;
}

void retirar_indice(lista* l, int index){
    elemento* aux_atual = l->inicio;
    elemento* aux_anterior = NULL;
    int i = 0;
    while(i <index){
            aux_anterior = aux_atual;
            aux_atual = aux_atual->prox;
            i++;
        }

        aux_anterior->prox = NULL;
        free(aux_atual);
        return;
}





////////////////////////////////////
//print



void print_lista(lista* cartas){
    elemento* aux = cartas->inicio;
    int i = 1;
    printf("As cartas da mesa sao:\n");
     while(aux != NULL){
            printf("%d - || %d   %c ||       ",i , aux->carta.numero, aux->carta.nipe);
            aux = aux->anterior;
            i++;
    }
    return;
}


void print_montes(jogador* j){
    elemento* aux = j->monte.topo;
    if(j->numero_de_cartas == 0){
        printf("Monte do jogador %sNao possui cartas\n", j->nome);
        return;
      }else{
        printf("Monte do jogador %s|| %d %c ||\n", j->nome, aux->carta.numero, aux->carta.nipe);
        printf("Numero de cartas: %d\n", j->numero_de_cartas);
        return;
    }
}

