#ifndef PILHA_H
#define PILHA_H

/*
 * pilha.h
 * ----------
 * Define a pilha de reserva (LIFO) usada para guardar peças.
 */

#include "peca.h"

#define MAX_PILHA 3  // Limite de peças reservadas

typedef struct {
    Peca itens[MAX_PILHA];
    int topo; // -1 indica pilha vazia
} PilhaReserva;

// Inicializa pilha vazia
void inicializarPilha(PilhaReserva *pilha);

// Verificações de estado
int pilhaCheia(PilhaReserva *pilha);
int pilhaVazia(PilhaReserva *pilha);

// Operações principais da pilha
int empilharPeca(PilhaReserva *pilha, Peca peca);
int desempilharPeca(PilhaReserva *pilha, Peca *saida);

// Exibição da pilha (Topo -> Base)
void exibirPilha(PilhaReserva *pilha);

#endif // PILHA_H