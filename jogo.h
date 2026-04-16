#ifndef JOGO_H
#define JOGO_H

/*
 * jogo.h
 * ----------
 * Interface das funções de alto nível do fluxo do jogo.
 */

#include "fila.h"
#include "pilha.h"

// Mostra fila e pilha
void exibirEstado(FilaPecas *fila, PilhaReserva *pilha);

// Mostra opções disponíveis para o jogador
void exibirMenu();

// Ações do menu
void jogarPeca(FilaPecas *fila);
void reservarPeca(FilaPecas *fila, PilhaReserva *pilha);
void usarPecaReservada(PilhaReserva *pilha);

#endif // JOGO_H