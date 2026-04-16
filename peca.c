#include "peca.h"
#include <stdlib.h>

/*
 * peca.c
 * ----------
 * Responsável por gerar peças aleatórias para a fila.
 */

const char TIPOS_PECA[] = {'I', 'O', 'T', 'L'};
const int TOTAL_TIPOS = 4;

// Id global incremental (garante unicidade)
int proximoId = 0;

Peca gerarPeca() {
    Peca nova;

    // Seleciona tipo aleatório entre os tipos disponíveis
    nova.nome = TIPOS_PECA[rand() % TOTAL_TIPOS];

    // Atribui id único e incrementa para a próxima peça
    nova.id = proximoId++;

    return nova;
}