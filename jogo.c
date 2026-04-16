#include "jogo.h"
#include <stdio.h>

/*
 * jogo.c
 * ----------
 * Orquestra as ações do usuário sobre fila e pilha.
 */

void exibirEstado(FilaPecas *fila, PilhaReserva *pilha) {
    printf("\nEstado atual:\n");
    exibirFila(fila);
    exibirPilha(pilha);
}

void exibirMenu() {
    printf("\n  --------- MENU ---------\n");
    printf("  1 - Jogar peca\n");
    printf("  2 - Reservar peca\n");
    printf("  3 - Usar peca reservada\n");
    printf("  0 - Sair\n");
    printf("  ------------------------\n");
    printf("  Escolha uma opcao: ");
}

void jogarPeca(FilaPecas *fila) {
    Peca removida;

    // Remove da frente da fila (simula jogar)
    if (removerDaFila(fila, &removida)) {
        printf("\n  [J] Peca jogada: [%c %d]\n", removida.nome, removida.id);

        // Mantém a fila sempre cheia com uma nova peça
        inserirPecaNaFila(fila, gerarPeca());
    }
}

void reservarPeca(FilaPecas *fila, PilhaReserva *pilha) {
    // Só permite reservar se houver espaço na pilha
    if (pilhaCheia(pilha)) {
        printf("\n  [!] Nao e possivel reservar: pilha cheia.\n");
        return;
    }

    Peca removida;

    // Remove da fila e envia para a pilha
    if (removerDaFila(fila, &removida)) {
        empilharPeca(pilha, removida);

        // Após retirar da fila, gera nova peça para manter tamanho fixo
        inserirPecaNaFila(fila, gerarPeca());
    }
}

void usarPecaReservada(PilhaReserva *pilha) {
    Peca usada;

    // Usa (remove) a peça do topo da pilha
    desempilharPeca(pilha, &usada);
}