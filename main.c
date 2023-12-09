#include <stdio.h>
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
    int jogador_monte_roubado = 0;
    


    
    printf("\033[0;33m");
    printf("-----BEM VINDO AO JOGO ROUBA MONTES-----\n");


    printf("Digite qualquer tecla para iniciar\n\n");
    printf("\033[0;37m");


  
     int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
    getchar();

    printf("\n\n");

    


    printf("Digite o numero de jogadores: ");
    scanf("%d", &num_jogadores);

    
    printf("Digite a quantidade de baralhos: ");
    scanf("%d", &num_baralhos);
 

   
    jogador *jogadores = (jogador *)malloc(num_jogadores * sizeof(jogador));//cria um array dinamico com o numero de jogadores selecionado
    pilha *baralho = (pilha *)malloc(num_baralhos * sizeof(pilha));//cria um array dinamico com os baralhos
    lista cartas_mesa;





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
    for(int b = 0; b<num_baralhos; b++) {
    int retorno_inicializa_baralho = inicializa_baralho(&baralho[b]);
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
                empilhar_baralho(&baralho[b], c);//empilha as cartas no baralho principal
            }
        }
   }
  }
  embaralharPilha(&baralho[b]);
 }




    printf("Tudo pronto, vamos ao jogo!\n\n");



///////////////////////////////////////////////

    carta carta_mao;


    printf("CADA JOGADOR RETIRA UMA CARTA\n");
    for(int i = 0; i<num_jogadores; i++){
    printf("\nJOGADA JOGADOR %sAperte qualquere tecla para iniciar ", jogadores[i].nome);
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
    getchar();

    carta_mao = desempilhar_baralho(&baralho[0]);
    printf(">>Sua carta e:\n");
    printf("|| %d %c ||\n", carta_mao.numero, carta_mao.nipe);
    insere_monte_jogador(&jogadores[i], carta_mao);
    }

   int retorno_inicializa_cartas_comunitarias = inicializa_lista(&cartas_mesa);
   if(retorno_inicializa_cartas_comunitarias == 0)
    printf("Erro inicializacao lista");
   else{
    carta carta_desempilhada = desempilhar_baralho(&baralho[0]);
    insere_lista(&cartas_mesa, carta_desempilhada);
    print_lista(&cartas_mesa);
   }

    int QTD_CARTAS_MIN = 52;
    int QTD_CARTAS_MAX = (num_baralhos*52)-num_jogadores;


    for(int b = 0; b<num_baralhos; b++){

        while( QTD_CARTAS_MIN > 0) {


            for(int i=0; i<num_jogadores; i++){

                    
                if(QTD_CARTAS_MAX == 1)
                        printf("\nUltima rodada\n");
                    else
                        printf("\nCartas no baralho: %d\n", QTD_CARTAS_MAX);


            
                    
                    printf("\nJOGADA JOGADOR %sAperte qualquere tecla para iniciar ", jogadores[i].nome);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
                    getchar();

                    carta_mao = desempilhar_baralho(&baralho[b]);
                    printf(">>Sua carta e:\n");
                    printf("|| %d %c ||\n", carta_mao.numero, carta_mao.nipe);



                    if(cartas_mesa.num_de_cartas == 0){
                        carta carta_desempilhada = desempilhar_baralho(&baralho[b]);
                        insere_lista(&cartas_mesa, carta_desempilhada);
                    }



                    printf("\n");
                    print_lista(&cartas_mesa);

                    printf("\n\n");
                    for(int k=0; k<num_jogadores; k++){
                        if(k!=i)
                            print_montes(&jogadores[k], k);
                    }
                    printf("\nTOPO DO SEU MONTE: \n");
                    if (jogadores[i].monte.topo != NULL) {
                    printf("|| %d %c ||\n", jogadores[i].monte.topo->carta.numero, jogadores[i].monte.topo->carta.nipe);
                    printf("Numero de cartas: %d\n", jogadores[i].numero_de_cartas);
                    } else {
                    printf("nao possui cartas\n");
                    }

                    int op;
                    printf("\nQual jogada sera feita?\n---1)Descarte\n---2)Usar carta da mesa\n---3)Roubar Monte\n---4)Inserir no topo do monte\n");
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
                        carta_pesquisa = cartas_mesa.cartas[carta_jogada-1];
                        retorno_verificacao = verificacao(&carta_mao, &carta_pesquisa);
                        if(retorno_verificacao == 1){
                            printf("\njogada valida\n");
                            insere_monte_jogador(&jogadores[i], carta_mao);
                            insere_monte_jogador(&jogadores[i], carta_pesquisa);
                            retirar_carta_lista(&cartas_mesa, carta_jogada);
                            printf("Voce tem direito a uma nova jogada!\n");
                            i--;
                        }else
                            printf("\nJogada invalida\n");

                        break;

                    case 3:
                        printf("De qual jogador ira roubar o monte?\n");
                        scanf("%d", &jogador_monte_roubado);
                        
                            if(carta_mao.numero == jogadores[jogador_monte_roubado].monte.topo->carta.numero){
                                printf("Jogada valida\n");
                                roubar_monte(&jogadores[i], &jogadores[jogador_monte_roubado]);
                                insere_monte_jogador(&jogadores[i], carta_mao);    
                                printf("Cartas transferidas com sucesso para o monte do jogador atual.\n");
                                printf("Voce tem direito a uma nova jogada!\n");
                                i--;
                            }else{
                            printf("Jogada invalida\n");
                            break;
                            }
                        
                        case 4:
                            if(carta_mao.numero == jogadores[i].monte.topo->carta.numero){
                            printf("Jogada Valida\n");
                            insere_monte_jogador(&jogadores[i], carta_mao);   
                            printf("Voce tem direito a uma nova jogda!\n");
                            i--;
                            break;
                            }else{
                                printf("Jogada Invalida\n");
                                break;
                            }

                    }

                
            QTD_CARTAS_MAX--;
            }

        QTD_CARTAS_MIN--;
        }
      
    }


    int max = jogadores[0].numero_de_cartas;
    int vencedor = 0;
    for(int i = 1; i<num_jogadores; i++){
      if(jogadores[i].numero_de_cartas>max){
        max = jogadores[i].numero_de_cartas;
        vencedor = i;
      }
    }

    printf("Jogador/es campeao/es:\n");
    printf("%s\n", jogadores[vencedor].nome);
    lista lista_jogador;
    inserir_ordenado(&lista_jogador, jogadores[vencedor].monte);



    for(int i = 0; i < num_jogadores; i++){
        if(i!=vencedor){
            if(jogadores[i].numero_de_cartas == jogadores[vencedor].numero_de_cartas){
                 printf("%s\n", jogadores[i].nome);
                 lista lista_jogador;
                 inserir_ordenado(&lista_jogador, jogadores[i].monte);
            }
        }
    }


    lista_ranking* ranking = (lista_ranking*)malloc(sizeof(lista_ranking));
    ordenar_ranking(ranking, jogadores, num_jogadores);
    print_lista_dinamica(&ranking);

    printf("\n\n");
    printf("\033[0;33m");
    printf("-----OBRIGADO POR JOGAR-----");
    
    return 0;
}
 



        