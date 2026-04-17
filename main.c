#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fila.h"
#include "pilha.h"
#include "peca.h"
#include "jogo.h"

/*
 * main.c
 * ----------
 * Ponto de entrada do programa:
 * 1) Inicializa estruturas
 * 2) Exibe estado/menu
 * 3) Processa ações até o usuário sair
 */

int main() {
    FilaPecas fila;
    PilhaReserva pilha;
    int opcao;

    // Inicializa semente do rand() para gerar peças diferentes em cada execução
    srand((unsigned int)time(NULL));

    // Prepara fila e pilha no estado inicial
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    preencherFilaInicial(&fila);

    printf("====================================\n");
    printf("        TETRIS STACK (C)            \n");
    printf("====================================\n");

    do {
        // Mostra o estado atual antes de cada ação
        exibirEstado(&fila, &pilha);
        exibirMenu();

        // Lê a opção do usuário com validação simples
        if (scanf("%d", &opcao) != 1) {
            printf("\n  [!] Entrada invalida. Digite um numero.\n");
            while (getchar() != '\n') { } // limpa buffer de entrada
            opcao = -1;
            continue;
        }

        // Executa ação correspondente
        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                reservarPeca(&fila, &pilha);
                break;
            case 3:
                usarPecaReservada(&pilha);
                break;
            case 4:
                trocarPecaAtual(&fila, &pilha);
                break;
            case 5:
                trocaMultipla(&fila, &pilha);
                break;
            case 0:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("\n  [!] Opcao invalida.\n");
                break;
        }
    } while (opcao != 0); // mantém loop até sair

    return 0;
}