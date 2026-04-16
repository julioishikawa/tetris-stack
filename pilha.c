#include "pilha.h"
#include <stdio.h>

/*
 * pilha.c
 * ----------
 * Implementa operações da pilha de reserva (último a entrar, primeiro a sair).
 */

void inicializarPilha(PilhaReserva *pilha) {
    // Topo em -1 representa pilha vazia
    pilha->topo = -1;
}

int pilhaCheia(PilhaReserva *pilha) {
    return pilha->topo == MAX_PILHA - 1;
}

int pilhaVazia(PilhaReserva *pilha) {
    return pilha->topo == -1;
}

int empilharPeca(PilhaReserva *pilha, Peca peca) {
    // Evita overflow da pilha
    if (pilhaCheia(pilha)) {
        printf("\n  [!] Pilha cheia! Nao foi possivel reservar [%c %d].\n", peca.nome, peca.id);
        return 0;
    }

    // Avança topo e coloca a peça
    pilha->topo++;
    pilha->itens[pilha->topo] = peca;

    printf("\n  [R] Peca reservada: [%c %d]\n", peca.nome, peca.id);
    return 1;
}

int desempilharPeca(PilhaReserva *pilha, Peca *saida) {
    // Evita underflow da pilha
    if (pilhaVazia(pilha)) {
        printf("\n  [!] Pilha vazia! Nenhuma peca reservada para usar.\n");
        return 0;
    }

    // Remove a peça do topo
    *saida = pilha->itens[pilha->topo];
    pilha->topo--;

    printf("\n  [U] Peca usada da reserva: [%c %d]\n", saida->nome, saida->id);
    return 1;
}

void exibirPilha(PilhaReserva *pilha) {
    printf("  Pilha de reserva (Topo -> Base): ");

    if (pilhaVazia(pilha)) {
        printf("(vazia)");
    } else {
        // Exibe do topo até a base para refletir a ordem de uso
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->itens[i].nome, pilha->itens[i].id);
        }
    }

    printf("\n");
}