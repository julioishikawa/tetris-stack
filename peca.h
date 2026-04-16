#ifndef PECA_H
#define PECA_H

/*
 * peca.h
 * ----------
 * Define a estrutura da peça e a função de geração automática.
 */

typedef struct {
    char nome; // Tipo da peça: I, O, T, L
    int id;    // Identificador único incremental
} Peca;

// Gera uma nova peça aleatória com id único
Peca gerarPeca();

// Contador global do próximo id
extern int proximoId;

#endif // PECA_H