#ifndef EXEMPLO_FILA_H
#define EXEMPLO_FILA_H
#include <stdbool.h>

#define MAX 5

typedef struct {
    int idade;
    char nome[30];
} Pessoa;

typedef struct {
    Pessoa itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

/* Inicializa a fila */
void inicializar(Fila *f);

/* Consultas */
bool filaCheia(const Fila *f);
bool filaVazia(const Fila *f);

/* Operações */
void inserir(Fila *f, Pessoa e);
Pessoa retirar(Fila *f);
Pessoa espiar(const Fila *f);

#endif /* EXEMPLO_FILA_H */