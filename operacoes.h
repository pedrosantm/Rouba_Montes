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
    elemento* inicio;
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
    l->inicio = NULL;
    l->num_de_cartas = 0;
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
   l->num_de_cartas++;

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

int verificacao(carta* c1, carta* c2){
    if(c1->numero == c2->numero)
        return 1;
    else 
        return 0;
}


carta pesquisa_indice(lista*l, int index){//função para retornar carna no indice indicado
    elemento* aux = l->inicio;
    int i = 0;
    while( i < index && aux != NULL){
        aux = aux->prox;
        i++; 
    }
    if(aux!= NULL){
    return aux->carta;
    }
}


void retirar_carta_lista(lista* l, int index) {
    printf("Teste");
    if (index < 0 || l->num_de_cartas <= 0) {
        printf("Indice invalido ou lista vazia\n");
        return;
    }

    printf("Indice recebido: %d\n", index);

    if (index == 0) {
        elemento* aux = l->inicio;
        l->inicio = l->inicio->prox;
        free(aux);
        l->num_de_cartas--;
        printf("Elemento removido do inicio da lista\n");
        if(l->num_de_cartas>0){
            l->inicio = l->inicio->prox;
        }
        return;
    }

    elemento* aux_anterior = NULL;
    elemento* aux_atual = l->inicio;
    int i = 0;
    while (i < index && aux_atual != NULL) {
        aux_anterior = aux_atual;
        aux_atual = aux_atual->prox;
        i++;
    }

    if (aux_atual == NULL) {
        printf("Indice inexistente\n");
        return;
    }

    printf("Elemento antes da remocao: %d %c\n", aux_atual->carta.numero, aux_atual->carta.nipe);

    aux_anterior->prox = aux_atual->prox;
    free(aux_atual);
    l->num_de_cartas--;
    printf("Elemento removido do indice %d\n", index);
}



void retirar_carta_monte(jogador* j) {

    elemento* carta_retirada = j->monte.topo;
    carta c = carta_retirada->carta;
    j->monte.topo = carta_retirada->anterior;
    free(carta_retirada);
    j->numero_de_cartas--;
    return c;
}



void roubar_monte(jogador* jogador_atual, jogador* jogador_alvo) {
    elemento* carta_transferida = jogador_alvo->monte.topo;
    
    if (carta_transferida == NULL) 
        return;
    

    while (carta_transferida != NULL) {
        carta c = carta_transferida->carta;
        insere_monte_jogador(jogador_atual, c); // Insere a carta no monte do jogador atual
        if(jogador_alvo->monte.topo == NULL)
            return;
        retirar_carta_monte(&jogador_alvo); // Remove a carta do monte do jogador alvo
        carta_transferida = jogador_alvo->monte.topo;
    }

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

