#include <stdio.H>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "oprecoes.h"




int main() {
    
    int num_jogadores = 0;
    int num_baralhos = 0;

    printf("Jogo rouba montes\n");

    printf("Digite o numero de jogadores: ");
    scanf("%d", &num_jogadores);

    
    printf("Digite a quantidade de baralhos: ");
    scanf("%d", &num_baralhos);

    pilha baralho;
    jogador *jogadores = (jogador *)malloc(num_jogadores * sizeof(jogador));

    // nome dos jogadores
    for (int i = 0; i < num_jogadores; i++) {
        printf("Digite o nome do Jogador %d: ", i + 1);
        scanf("%s", jogadores[i].nome);
        jogadores[i].numero_de_cartas = 0; //número de cartas de cada jogador
    }

    return 0;
}
