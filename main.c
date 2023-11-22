#include <stdio.H>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "operacoes.h"




int main() {
    
    int num_jogadores = 0;
    int num_baralhos = 0;
    int retorno_insere_lista;
    carta carta_pesquisa;
    int carta_jogada;
    int retorno_verificacao;
    int aux_carta;
    int jogador_monte_roubado = 0;
    carta retorno_desempilhamento;
    carta_pesquisa.nipe = '0';
    carta_pesquisa.numero = 0;

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
        for(int k=0; k<2; k++){
            carta c;
            c.numero = 0;
            c.nipe = 'J';
            empilhar_baralho(&baralho_principal, c);//ampilhamento das cartas coringas
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

    while(baralho_principal.topo > 0) {



        if(baralho_principal.topo == 1)
                printf("\nUltima rodada\n");
            else
                printf("\nCartas no baralho: %d\n", baralho_principal.topo);


        for(int i=0; i<num_jogadores; i++){

            
            printf("\nJogada jogador %sAperte qualquere tecla para iniciar ", jogadores[i].nome);
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
            getchar();

            carta_mao = desempilhar_baralho(&baralho_principal);
            printf(">>Sua carta e:\n");
            printf("|| %d %c ||\n", carta_mao.numero, carta_mao.nipe);



            if(cartas_mesa->num_de_cartas == 0){
                carta carta_desempilhada = desempilhar_baralho(&baralho_principal);
                insere_lista(&cartas_mesa, carta_desempilhada);
            }



            printf("\n");
            print_lista(&cartas_mesa);

            printf("\n\n");
            for(int k=0; k<num_jogadores; k++){
                if(k!=i)
                    print_montes(&jogadores[k], k);
            }

            int op;
            printf("\nQual jogada sera feita?\n1-Descarte\n2-Usar carta da mesa\n3-Roubar Monte\n");
            scanf("%d", &op);

            switch (op){
            
            case 1:
                retorno_insere_lista = insere_lista(&cartas_mesa, carta_mao);
                if(retorno_insere_lista == 1)
                    printf("Jogada realizada!\n");
                else
                    printf("ERRO\n");
    
                break;

            case 2:
                printf("Qual o indice da carta que sera usada?\n");
                scanf("%d", &carta_jogada);
                aux_carta = carta_jogada;
                retorno_verificacao = pesquisa_indice(&cartas_mesa, carta_jogada-1, &carta_mao);
                printf("Ate aqui");
                //retorno_verificacao = verificacao(&carta_mao, &carta_pesquisa);
                if(retorno_verificacao == 1){
                    printf("\njogada valida\n");
                    insere_monte_jogador(&jogadores[i], carta_mao);
                    insere_monte_jogador(&jogadores[i], carta_pesquisa);
                    retirar_carta_lista(&cartas_mesa, aux_carta);
                    printf("Voce tem direito a uma nova jogada\n");
                    i--;
                }else
                    printf("\nJogada invalida\n");

                break;

            case 3:
                printf("De qual jogador ira roubar o monte?\n");
                scanf("%d", &jogador_monte_roubado);
                for(int k=0; k<num_jogadores; k++){
                    if(k!=i)
                        if(k == jogador_monte_roubado){
                        retorno_verificacao = verificacao(&carta_mao, &jogadores[k].monte.topo);
                        if(retorno_verificacao == 1){
                            roubar_monte(&jogadores[i], &jogadores[k]);
                            insere_monte_jogador(&jogadores[i], carta_mao);
                        }else
                            printf("Jogada invalida\n");
                            printf("Cartas transferidas com sucesso para o monte do jogador atual.\n");
                        break;
                        }
                 }

            }

           

        }
      }
    }
 

   return 0;
}


   