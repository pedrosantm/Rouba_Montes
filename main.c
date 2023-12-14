#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "operacoes.h"




int main() {
    
    int num_jogadores = 0;//variaveis globais
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
    lista cartas_mesa;//cria as cartas da mesa





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
        for (int numero = 1; numero <= 13; numero++) {
            for (int nipe = 0; nipe<4; nipe++) {
                carta c;
                c.numero = numero;
                c.nipe = np[nipe];
                empilhar_baralho(&baralho[b], c);//empilha as cartas no baralho principal
            }
        
   }
  }
  embaralharPilha(&baralho[b]);//embaralhamento
 }




    printf("Tudo pronto, vamos ao jogo!\n\n");



///////////////////////////////////////////////

    carta carta_mao;//variavel da carta da vez


    printf("CADA JOGADOR RETIRA UMA CARTA\n");
    for(int i = 0; i<num_jogadores; i++){
    printf("\nJOGADA JOGADOR %sAperte qualquere tecla para iniciar ", jogadores[i].nome);
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
    getchar();

    carta_mao = desempilhar_baralho(&baralho[0]);//desempilha do baralho
    printf(">>Sua carta e:\n");
    printf("|| %d %c ||\n", carta_mao.numero, carta_mao.nipe);
    insere_monte_jogador(&jogadores[i], carta_mao);//insere no monte do jogador
    }

   int retorno_inicializa_cartas_comunitarias = inicializa_lista(&cartas_mesa);
   if(retorno_inicializa_cartas_comunitarias == 0)
    printf("Erro inicializacao lista");
   else{
    carta carta_desempilhada = desempilhar_baralho(&baralho[0]);//desempilha baralho e insere na mesa
    insere_lista(&cartas_mesa, carta_desempilhada);
    print_lista(&cartas_mesa);
   }

    int QTD_CARTAS_MIN = 52;//variaveis que controlam a quantidade de jogadas, esta por cada baralho
    int QTD_CARTAS_MAX = (num_baralhos*52)-num_jogadores;//variaveis que controlam a quantidade de jogadas, esta para cartas no total


    for(int b = 0; b<num_baralhos; b++){
                                        //roda a quantidade de jogadas de acordo com o numero de cartas
        while( QTD_CARTAS_MIN > 0) {


            for(int i=0; i<num_jogadores; i++){

                    
                if(QTD_CARTAS_MAX == 0)
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



                    if(cartas_mesa.num_de_cartas == 0){//quando nao ha cartas na mesa uma é obrigatoriamente tirada
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

                    int op;//escolha do jogador por qual jogada sera feita
                    printf("\nQual jogada sera feita?\n---1)Descarte\n---2)Usar carta da mesa\n---3)Roubar Monte\n---4)Inserir no topo do monte\n");
                    scanf("%d", &op);

                    switch (op){
                    
                    case 1://insere na lista
                        retorno_insere_lista = insere_lista(&cartas_mesa, carta_mao);
                        if(retorno_insere_lista == 1)
                            printf("Jogada realizada!\n");
                        else
                            printf("ERRO\n");
            
                        break;

                    case 2://usar carta da mesa
                        printf("Qual o indice da carta que sera usada?\n");
                        scanf("%d", &carta_jogada);
                        carta_pesquisa = cartas_mesa.cartas[carta_jogada-1];//pesquisa na lista
                        retorno_verificacao = verificacao(&carta_mao, &carta_pesquisa);//verifica se os numeros sao iguais
                        if(retorno_verificacao == 1){
                            printf("\njogada valida\n");
                            insere_monte_jogador(&jogadores[i], carta_mao);
                            insere_monte_jogador(&jogadores[i], carta_pesquisa);
                            retirar_carta_lista(&cartas_mesa, carta_jogada);
                            printf("Voce tem direito a uma nova jogada!\n");
                            i--;//decrementa o "i" para o jogador repetir a jogada
                        }else{
                            printf("\nJogada invalida\n");//se a jogada for invalida a carta é inserida na lista
                            retorno_insere_lista = insere_lista(&cartas_mesa, carta_mao);
                            printf("Carta inserida na mesa\n");
                        }

                        break;

                    case 3://roubar monte do jogador
                        printf("De qual jogador ira roubar o monte?\n");
                        scanf("%d", &jogador_monte_roubado);
                        
                            if(carta_mao.numero == jogadores[jogador_monte_roubado].monte.topo->carta.numero){//compara para validação da jogada
                                printf("Jogada valida\n");
                                roubar_monte(&jogadores[i], &jogadores[jogador_monte_roubado]);//rouba o monte
                                insere_monte_jogador(&jogadores[i], carta_mao);//insere a carta da vez
                                printf("Cartas transferidas com sucesso para o monte do jogador atual.\n");
                                printf("Voce tem direito a uma nova jogada!\n");
                                i--;//decrementa o "i" para o jogador repetir a jogada
                            }else{
                                printf("Jogada invalida\n");//se a jogada for invalida a carta é inserida na lista
                                retorno_insere_lista = insere_lista(&cartas_mesa, carta_mao);
                                printf("Carta inserida na mesa\n");
                            }
                            break;
                        
                        case 4://insere a carta no topo do monte
                            if(carta_mao.numero == jogadores[i].monte.topo->carta.numero){//compara para validação da jogada
                            printf("Jogada Valida\n");
                            insere_monte_jogador(&jogadores[i], carta_mao);//insere no monte
                            printf("Voce tem direito a uma nova jogda!\n");
                            i--;//decrementa o "i" para o jogador repetir a jogada
                            break;
                            }else{
                                printf("Jogada Invalida\n");//se a jogada for invalida a carta é inserida na lista
                                retorno_insere_lista = insere_lista(&cartas_mesa, carta_mao);
                                printf("Carta inserida na mesa\n");
                                break;
                            }

                    }

                
            QTD_CARTAS_MAX--;//decrementa as variaveis de controle
            }

        QTD_CARTAS_MIN--;
        }
      
    }


    int max = jogadores[0].numero_de_cartas;//define o jogador com maior numero de cartas
    int vencedor = 0;
    for(int i = 1; i<num_jogadores; i++){
      if(jogadores[i].numero_de_cartas>max){
        max = jogadores[i].numero_de_cartas;
        vencedor = i;
      }
    }

    printf("Jogador/es campeao/es:\n");
    printf("%s\n", jogadores[vencedor].nome);
    lista lista_jogador;//cria lista para o jogador
    inserir_ordenado(&lista_jogador, jogadores[vencedor].monte);//ordena na lista



    for(int i = 0; i < num_jogadores; i++){//verifica se existem outros campeoes
        if(i!=vencedor){
            if(jogadores[i].numero_de_cartas == jogadores[vencedor].numero_de_cartas){
                 printf("%s\n", jogadores[i].nome);
                 lista lista_jogador;//cria lista para o jogador
                 inserir_ordenado(&lista_jogador, jogadores[i].monte);//ordena na lista
            }
        }
    }


    lista_ranking* ranking = (lista_ranking*)malloc(sizeof(lista_ranking));//cria lista para ranking
    ordenar_ranking(ranking, jogadores, num_jogadores);//ordena a lista de acordo com o ranking
    print_lista_dinamica(&ranking);

    printf("\n\n");
    printf("\033[0;33m");
    printf("-----OBRIGADO POR JOGAR-----");
    
    return 0;
}
 



        