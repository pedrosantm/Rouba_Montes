#include <stdio.H>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "operacoes.h"




int main() {
    
    int num_jogadores = 0;
    int num_baralhos = 0;
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
        
        int retorno_cria_monte = inicializa_monte(&jogadores[i].monte);
        int retorno_num_de_cartas = inicializa_num_de_cartas(&jogadores[i]);
    }


    



     // preenche o baralho com os numeros e os nipes , usando o controlador numero de baralhos para repetir
    // processo a qauntidade de vezes nescessarias
    char np[4] = {'P', 'C', 'E', 'O'};
    int retorno_inicializa_baralho = inicializa_baralho(&baralho_principal);
    if(retorno_inicializa_baralho==0){
        printf("Erro inicializacao de baralho");
        return 0;
    }else{
    for(int i = 0; i < num_baralhos; i++) {
        for (int numero = 1; numero <= 13; numero++) {
            for (int j = 0; j<4; j++) {
                carta c;
                c.numero = numero;
                c.nipe = np[j];
                empilhar_baralho(&baralho_principal, c);//empilha as cartas no baralho principal
            }
        }
   }
 }







    embaralharPilha(&baralho_principal);//baralho embaralhado

    printf("Tudo pronto, vamos ao jogo!\n");



///////////////////////////////////////////////


   int retorno_inicializa_cartas_comunitarias = inicializa_lista(&cartas_mesa);
   if(retorno_inicializa_cartas_comunitarias == 0)
    printf("Erro inicializacao lista");
   else{
    carta carta_desempilhada = desempilhar_baralho(&baralho_principal);
    insere_lista(&cartas_mesa, carta_desempilhada);
    print_lista(&cartas_mesa);



    carta carta_mao;
    char enter;
    while(baralho_principal.topo > 0) {



        if(baralho_principal.topo == 1)
                printf("\nUltima rodada\n");
            else
                printf("\nCartas no baralho: %d\n", baralho_principal.topo);


        for(int i=0; i<num_jogadores; i++){


            printf("\nJogada jogador %sAperte qualquere tecla para iniciar ", jogadores[i].nome);
            getchar();

            carta_mao = desempilhar_baralho(&baralho_principal);
            printf("|| %d %c ||\n", carta_mao.numero, carta_mao.nipe);

            printf("\n");
            print_lista(&cartas_mesa);

            printf("\n\n");
            for(int k=0; k<num_jogadores; k++){
                if(k!=i)
                    print_montes(&jogadores[k]);
            }

        }




    }


   }






   return 0;
}


   