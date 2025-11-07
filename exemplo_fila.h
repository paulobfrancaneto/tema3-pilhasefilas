#ifndef EXEMPLO_FILA_H
#define EXEMPLO_FILA_H

#include <stdbool.h>

#define MAX 100

typedef struct {
    int valor;
    char nome[30];
} Elemento;

typedef struct {
    Elemento itens[MAX];
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
void inserir(Fila *f, Elemento e);
Elemento retirar(Fila *f);
Elemento espiar(const Fila *f);

#endif /* EXEMPLO_FILA_H */