#include <stdio.H>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "oprecoes.h"




int main() {
    
    int num_jogadores = 0;
    int num_baralhos = 0;
    int retorno_empilhamento;
    carta retorno_desempilhamento;


    printf("Jogo rouba montes\n");

    printf("Digite o numero de jogadores: ");
    scanf("%d", &num_jogadores);

    
    printf("Digite a quantidade de baralhos: ");
    scanf("%d", &num_baralhos);

    pilha baralho_principal;//o baralho prinicpal é de estrutura pilha
    jogador *jogadores = (jogador *)malloc(num_jogadores * sizeof(jogador));//cria um array dinamico com o numero de jogadores selecionado
    lista *cartas_mesa = (lista *)malloc(sizeof(lista));

    // nome dos jogadores
    for (int i = 0; i < num_jogadores; i++) {
        printf("Digite o nome do Jogador %d: ", i + 1);
        scanf("%s", jogadores[i].nome);
        jogadores[i].numero_de_cartas = 0; //número de cartas de cada jogador
    }


    printf("Tudo pronto, vamos ao jogo!\n");

    // preenche o baralho com os numeros e os nipes , usando o controlador numero de baralhos para repetir
    // processo a qauntidade de vezes nescessarias
    for(int i = 0; i < num_baralhos; i++) {
        for (int numero = 1; numero <= 13; numero++) {
            for (char nipe = 'P'; nipe <= 'E'; nipe++) {
                carta carta = {numero, nipe};
                 empilhar_baralho(&baralho_principal, carta);//empilha as cartas no baralho principal
            }
        }
}

    embaralharPilha(&baralho_principal);//baralho embaralhado

    printf("\nAs cartas comunitarias da mesa sao:\n");
    for(int i = 0; i < 4; i++){//desempilhamento do baralho e atribuição as cartas comunitarias da mesa
        retorno_desempilhamento = desempilhar_baralho(&baralho_principal);
        insere_lista(cartas_mesa, retorno_desempilhamento);
    }

    print_lista(cartas_mesa);

    for(int i = 0; i<num_jogadores; i++){
        printf("As cartas do jogador %d sao: \n", i+1);
        for(int i = 0; i<4; i++){
             retorno_desempilhamento = desempilhar_baralho(&baralho_principal);
             insere_lista(jogadores[i].cartas_jogaveis, retorno_desempilhamento);           
        }
        print_lista(jogadores[i].cartas_jogaveis);
    }
    return 0;
}
