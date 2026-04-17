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
    printf("  4 - Trocar peca da frente com topo da pilha\n");
    printf("  5 - Trocar 3 primeiros da fila com 3 da pilha\n");
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

void trocarPecaAtual(FilaPecas *fila, PilhaReserva *pilha) {
    // Ambas devem ter pelo menos uma peça para a troca
    if (filaVazia(fila)) {
        printf("\n  [!] Fila vazia! Nao e possivel realizar a troca.\n");
        return;
    }
    if (pilhaVazia(pilha)) {
        printf("\n  [!] Pilha vazia! Nao e possivel realizar a troca.\n");
        return;
    }

    // Troca a peça da frente da fila com o topo da pilha
    Peca temp = fila->itens[fila->inicio];
    fila->itens[fila->inicio] = pilha->itens[pilha->topo];
    pilha->itens[pilha->topo] = temp;

    printf("\n  [T] Troca realizada entre a frente da fila e o topo da pilha.\n");
}

void trocaMultipla(FilaPecas *fila, PilhaReserva *pilha) {
    // Verifica se há pelo menos 3 peças em cada estrutura
    if (fila->total < 3) {
        printf("\n  [!] Fila precisa ter pelo menos 3 pecas para a troca multipla.\n");
        return;
    }
    if (pilha->topo < 2) {
        printf("\n  [!] Pilha precisa ter pelo menos 3 pecas para a troca multipla.\n");
        return;
    }

    // Troca posicionalmente as 3 primeiras da fila com as 3 da pilha (topo a base)
    for (int i = 0; i < 3; i++) {
        int idx = (fila->inicio + i) % MAX_FILA;
        Peca temp = fila->itens[idx];
        fila->itens[idx] = pilha->itens[pilha->topo - i];
        pilha->itens[pilha->topo - i] = temp;
    }

    printf("\n  [M] Troca multipla realizada entre os 3 primeiros da fila e as 3 pecas da pilha.\n");
}