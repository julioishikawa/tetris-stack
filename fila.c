#include "fila.h"
#include <stdio.h>

/*
 * fila.c
 * ----------
 * Implementa as operações da fila circular de peças.
 */

void inicializarFila(FilaPecas *fila) {
    // No início, fila vazia e índices na posição zero
    fila->inicio = 0;
    fila->fim = 0;
    fila->total = 0;
}

int filaCheia(FilaPecas *fila) {
    // Fila cheia quando total alcança capacidade máxima
    return fila->total == MAX_FILA;
}

int filaVazia(FilaPecas *fila) {
    // Fila vazia quando não há elementos
    return fila->total == 0;
}

void inserirPecaNaFila(FilaPecas *fila, Peca peca) {
    // Evita overflow da fila
    if (filaCheia(fila)) {
        printf("\n  [!] Fila cheia! Nao foi possivel inserir [%c %d].\n", peca.nome, peca.id);
        return;
    }

    // Insere no índice "fim"
    fila->itens[fila->fim] = peca;

    // Avança circularmente o índice de inserção
    fila->fim = (fila->fim + 1) % MAX_FILA;
    fila->total++;
}

int removerDaFila(FilaPecas *fila, Peca *saida) {
    // Evita underflow da fila
    if (filaVazia(fila)) {
        printf("\n  [!] Fila vazia! Nenhuma peca para remover.\n");
        return 0;
    }

    // Remove da frente da fila
    *saida = fila->itens[fila->inicio];

    // Avança circularmente o índice de início
    fila->inicio = (fila->inicio + 1) % MAX_FILA;
    fila->total--;
    return 1;
}

void preencherFilaInicial(FilaPecas *fila) {
    // Gera peças até completar a capacidade fixa da fila
    while (!filaCheia(fila)) {
        inserirPecaNaFila(fila, gerarPeca());
    }
}

void exibirFila(FilaPecas *fila) {
    printf("  Fila de pecas: ");

    if (filaVazia(fila)) {
        printf("(vazia)");
    } else {
        // Percorre os elementos respeitando a ordem lógica da fila circular
        for (int i = 0; i < fila->total; i++) {
            int idx = (fila->inicio + i) % MAX_FILA;
            printf("[%c %d] ", fila->itens[idx].nome, fila->itens[idx].id);
        }
    }

    printf("\n");
}