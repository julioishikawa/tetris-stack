/**
 * Tetris Stack - Sistema de Fila de Peças Futuras
 * 
 * Programa que simula a fila de peças futuras do jogo Tetris Stack,
 * utilizando uma fila circular para gerenciar as peças.
 * 
 * Desenvolvido para a ByteBros. (Empresa fictícia de desenvolvimento de jogos)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ========================== Definições ========================== */

#define MAX_FILA 5  /* Capacidade máxima da fila de peças */

/* Tipos de peças disponíveis no jogo */
const char TIPOS_PECA[] = {'I', 'O', 'T', 'L'};
const int TOTAL_TIPOS = 4;

/* ========================== Estruturas ========================== */

/* Representa uma peça do jogo com tipo e identificador único */
typedef struct {
    char nome;  /* Tipo da peça: 'I', 'O', 'T' ou 'L' */
    int id;     /* Identificador numérico único da peça */
} Peca;

/* Fila circular que armazena as peças futuras do jogo */
typedef struct {
    Peca itens[MAX_FILA]; /* Array de peças */
    int inicio;           /* Índice do primeiro elemento (frente) */
    int fim;              /* Índice da próxima posição livre (traseira) */
    int total;            /* Quantidade atual de elementos na fila */
} FilaPecas;

/* Contador global para gerar IDs únicos para cada peça */
int proximoId = 0;

/* ========================== Funções ========================== */

/**
 * Gera uma nova peça com tipo aleatório e ID único.
 * O tipo é sorteado entre 'I', 'O', 'T' e 'L'.
 * O ID é incrementado automaticamente a cada chamada.
 */
Peca gerarPeca() {
    Peca novaPeca;
    novaPeca.nome = TIPOS_PECA[rand() % TOTAL_TIPOS];
    novaPeca.id = proximoId++;
    return novaPeca;
}

/**
 * Inicializa a fila, zerando os índices e o contador.
 */
void inicializarFila(FilaPecas *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->total = 0;
}

/**
 * Verifica se a fila está cheia.
 * Retorna 1 se cheia, 0 caso contrário.
 */
int filaCheia(FilaPecas *fila) {
    return fila->total == MAX_FILA;
}

/**
 * Verifica se a fila está vazia.
 * Retorna 1 se vazia, 0 caso contrário.
 */
int filaVazia(FilaPecas *fila) {
    return fila->total == 0;
}

/**
 * Insere (enqueue) uma peça ao final da fila circular.
 * Caso a fila esteja cheia, exibe uma mensagem de erro.
 */
void inserirPeca(FilaPecas *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("\n  [!] Fila cheia! Nao e possivel inserir a peca %c (ID: %d).\n", peca.nome, peca.id);
        return;
    }

    /* Coloca a peça na posição "fim" e avança o índice circularmente */
    fila->itens[fila->fim] = peca;
    fila->fim = (fila->fim + 1) % MAX_FILA;
    fila->total++;

    printf("\n  [+] Peca %c (ID: %d) adicionada a fila.\n", peca.nome, peca.id);
}

/**
 * Remove (dequeue) a peça da frente da fila circular.
 * Retorna a peça removida através do ponteiro "pecaRemovida".
 * Caso a fila esteja vazia, exibe mensagem de erro e retorna 0.
 * Retorna 1 se a remoção foi bem-sucedida.
 */
int jogarPeca(FilaPecas *fila, Peca *pecaRemovida) {
    if (filaVazia(fila)) {
        printf("\n  [!] Fila vazia! Nao ha pecas para jogar.\n");
        return 0;
    }

    /* Copia a peça da frente e avança o índice de início circularmente */
    *pecaRemovida = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX_FILA;
    fila->total--;

    printf("\n  [>] Peca jogada: %c (ID: %d)\n", pecaRemovida->nome, pecaRemovida->id);
    return 1;
}

/**
 * Exibe o estado atual da fila de peças, percorrendo-a
 * circularmente do início ao fim.
 */
void exibirFila(FilaPecas *fila) {
    printf("\n  ============================\n");
    printf("       Fila de pecas\n");

    if (filaVazia(fila)) {
        printf("       (vazia)\n");
    } else {
        printf("  ");
        int idx = fila->inicio;
        for (int i = 0; i < fila->total; i++) {
            printf(" [%c %d]", fila->itens[idx].nome, fila->itens[idx].id);
            idx = (idx + 1) % MAX_FILA;
        }
        printf("\n");
    }

    printf("  ============================\n");
}

/**
 * Exibe o menu de opções para o jogador.
 */
void exibirMenu() {
    printf("\n  --------- MENU ---------\n");
    printf("  1 - Jogar peca (dequeue)\n");
    printf("  2 - Inserir nova peca (enqueue)\n");
    printf("  0 - Sair\n");
    printf("  ------------------------\n");
    printf("  Escolha uma opcao: ");
}

/**
 * Preenche a fila com peças geradas automaticamente
 * até atingir a capacidade máxima inicial.
 */
void preencherFilaInicial(FilaPecas *fila) {
    for (int i = 0; i < MAX_FILA; i++) {
        Peca novaPeca = gerarPeca();
        fila->itens[fila->fim] = novaPeca;
        fila->fim = (fila->fim + 1) % MAX_FILA;
        fila->total++;
    }
}

/* ========================== Main ========================== */

int main() {
    FilaPecas fila;
    int opcao;
    Peca pecaRemovida;

    /* Inicializa o gerador de números aleatórios */
    srand(time(NULL));

    /* Prepara a fila e a preenche com peças iniciais */
    inicializarFila(&fila);
    preencherFilaInicial(&fila);

    printf("\n  ================================\n");
    printf("     TETRIS STACK - ByteBros\n");
    printf("  ================================\n");

    /* Loop principal do programa */
    do {
        /* Mostra o estado atual da fila */
        exibirFila(&fila);

        /* Mostra o menu e lê a opção do jogador */
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                /* Jogar peça: remove da frente da fila */
                jogarPeca(&fila, &pecaRemovida);
                break;

            case 2:
                /* Inserir nova peça: gera automaticamente e adiciona ao final */
                inserirPeca(&fila, gerarPeca());
                break;

            case 0:
                printf("\n  Encerrando o Tetris Stack. Ate mais!\n\n");
                break;

            default:
                printf("\n  [!] Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
