#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>


typedef struct Carta {
    int numero;
    char nipe;
}carta;

typedef struct Pilha {
    struct Carta cartas[54];
    int topo;
}pilha;

typedef struct elemento{//estruct para definição do elemento
    carta carta;
    struct elemento* anterior;
    struct elemento* prox;
}elemento;

typedef struct pilha_dinamica{//pilha dinamica para representar cada monte de um jogador jogador
    elemento* topo;
}pilha_dinamica;

typedef struct{
    carta cartas[54];
    int inicio;
    int num_de_cartas;
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
    l->inicio = 0;
    l->num_de_cartas = 0;
    if(l->inicio==0)
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
        int j = rand() % 54;
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
    l->cartas[l->inicio] = c;
    l->inicio++;
    l->num_de_cartas++;
    return 1 ;
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

int verificacao(carta* c1, carta* c2){
    if(c1->numero == c2->numero)
        return 1;
    else 
        return 0;
}


void retirar_carta_lista(lista* lista, int indice) {
    indice = indice-1;
    if (indice < 0 || indice >= lista->num_de_cartas) {
        printf("Índice inválido.\n");
        return;
    }

    for (int i = indice; i < lista->num_de_cartas - 1; i++) {
        lista->cartas[i] = lista->cartas[i + 1];
    }

    lista->num_de_cartas--;
}


carta retirar_carta_monte(jogador* j) {

    elemento* carta_retirada = j->monte.topo;
    carta c = carta_retirada->carta;
    j->monte.topo = carta_retirada->anterior;
    free(carta_retirada);
    j->numero_de_cartas--;
    return c;
}



void roubar_monte(jogador* jogador_atual, jogador* jogador_alvo) {
    carta carta_retirada;
    int control = jogador_alvo->numero_de_cartas;

   for(int i=0; i<control; i++){
        carta_retirada = retirar_carta_monte(jogador_alvo);
        insere_monte_jogador(jogador_atual, carta_retirada);
   }

    return;
}








////////////////////////////////////
//print



void print_lista(lista* l){
    printf("-------AS CARTAS DA MESA SAO-------\n");
    for(int i = 0; i<l->num_de_cartas; i++){
        printf("%d- || %d %c ||   ", i+1, l->cartas[i].numero, l->cartas[i].nipe);
    }
    return;
}


void print_montes(jogador* j, int k){
    elemento* aux = j->monte.topo;
    if(j->numero_de_cartas == 0){
        printf("%d - Monte do jogador %sNao possui cartas\n", k , j->nome);
        return;
      }else{
        printf("%d - Monte do jogador %s|| %d %c ||\n", k , j->nome, aux->carta.numero, aux->carta.nipe);
        printf("Numero de cartas: %d\n", j->numero_de_cartas);
        return;
    }
}

