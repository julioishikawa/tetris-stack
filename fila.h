#ifndef FILA_H
#define FILA_H

/*
 * fila.h
 * ----------
 * Define a fila circular de peças futuras.
 * A fila guarda sempre as próximas peças disponíveis para jogar/reservar.
 */

#include "peca.h"

#define MAX_FILA 5  // Quantidade fixa de peças que ficam visíveis/futuras

/*
 * Fila circular:
 * - inicio: índice da peça da frente (próxima a sair)
 * - fim: índice da próxima posição livre para inserir
 * - total: quantas peças existem atualmente
 */
typedef struct {
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} FilaPecas;

// Inicializa a fila vazia (índices e contador)
void inicializarFila(FilaPecas *fila);

// Verificações de estado da fila
int filaCheia(FilaPecas *fila);
int filaVazia(FilaPecas *fila);

// Operações principais da fila circular
void inserirPecaNaFila(FilaPecas *fila, Peca peca);
int removerDaFila(FilaPecas *fila, Peca *saida);

// Utilitários do jogo
void preencherFilaInicial(FilaPecas *fila);
void exibirFila(FilaPecas *fila);

#endif // FILA_H