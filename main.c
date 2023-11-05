#include <stdio.H>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "operacoes.h"




int main() {
    
    int num_jogadores = 0;
    int num_baralhos = 0;
    //int retorno_empilhamento;
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
        setbuf(stdin, NULL);
        fgets(jogadores[i].nome, 50, stdin);
        jogadores[i].numero_de_cartas = 0; //número de cartas de cada jogador
    }

    for (int i = 0; i < num_jogadores; i++) {//inicialização dos montes e cartas jogaveis 
        
        int retorno_cria_monte = cria_monte(&jogadores[i].monte);
        int retorno_num_de_cartas = inicializacao_num_de_cartas(&jogadores[i]);
         if(retorno_cria_monte == 0 && retorno_num_de_cartas == 0)
            printf("Erro na inicializacao\n");
         else{
            int retorno_cria_lista = inicializa_lista(&jogadores[i].cartas_jogaveis);
            if(retorno_cria_lista == 0)
                printf("Erro na inicializacao\n");
         }
    }


    
    // preenche o baralho com os numeros e os nipes , usando o controlador numero de baralhos para repetir
    // processo a qauntidade de vezes nescessarias
    for(int i = 0; i < num_baralhos; i++) {
        for (int numero = 1; numero <= 13; numero++) {
            for (char nipe = 'P'; nipe <= 'E'; nipe++) {
                carta carta = {numero, nipe};
                 empilhar_baralho(&baralho_principal, carta, num_baralhos);//empilha as cartas no baralho principal
            }
        }
}

    embaralharPilha(&baralho_principal);//baralho embaralhado

    printf("Tudo pronto, vamos ao jogo!\n");



///////////////////////////////////////////////


    while(baralho_principal.topo - 1 > 0){

        if(baralho_principal.topo - 1 == 4)
            printf("Ultima rodada\n");
        else
            printf("Numero de cartas no baralho: %d\n", baralho_principal.topo - 1);



            for(int i = 0; i<num_jogadores; i++){

                printf("\nAs cartas comunitarias da mesa sao:\n");
                for(int k = 0; k < 4; k++){//desempilhamento do baralho e atribuição as cartas comunitarias da mesa
                    retorno_desempilhamento = desempilhar_baralho(&baralho_principal);
                    insere_lista(cartas_mesa, retorno_desempilhamento);
                }

                print_lista(cartas_mesa);

                    //distribuição das cartas jogaveis aos jogadores
                    printf("\nAs cartas do jogador %d sao: \n", i+1);
                    for(int k = 0; k<4; k++){
                        carta retorno_desempilhamento = desempilhar_baralho(&baralho_principal);
                        insere_lista(&jogadores[k].cartas_jogaveis, retorno_desempilhamento);           
                    }
                    print_lista(&jogadores[i].cartas_jogaveis);

                    for(int l = 0; l<num_jogadores; l++){
                        if(l != i){
                            print_montes(&jogadores[l], l);
                        }
                        
                    }
                
        }
  }
    return 0;
}
