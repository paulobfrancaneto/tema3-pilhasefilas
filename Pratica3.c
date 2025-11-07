#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50

typedef struct {
    char nome[30]; // Nome da peça (1 caractere + terminador nulo)
    int idade; // ID exclusivo da peça
} Pessoa;

typedef struct {
    Pessoa dados[MAX];
    int inicio, fim;
} Fila;

typedef struct {
    Pessoa dados[MAX];
    int topo;
} Pilha;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Funções de Operação da Fila
void inserir(Fila *f, Pessoa p) {
    if (f->fim < MAX) {
        f->dados[f->fim++] = p;
    }
}

Pessoa remover(Fila *f) {
    return f->dados[f->inicio++];
}

// Funções de Operação da Pilha
void push(Pilha *p, Pessoa pes) {
    if (p->topo < MAX - 1) {
        p->dados[++p->topo] = pes;
    }
}

Pessoa pop(Pilha *p) {
    return p->dados[p->topo--];
}

void exibirFila(Fila f) {
    for (int i = f.inicio; i < f.fim; i++) {
        printf("Nome: %s | Idade: %d\n", f.dados[i].nome, f.dados[i].idade);
    }
}

int main(int argc, char const *argv[])
{
    Fila filaOriginal, filaInvertida;
    Pilha auxiliar;

    inicializarFila(&filaOriginal);
    inicializarFila(&filaInvertida);
    inicializarPilha(&auxiliar);

    Pessoa pessoas[] = {
        {"Carlos", 45},
        {"Joana", 62},
        {"Lucas", 30},
        {"Maria", 45},
        {"Ana", 25},
        {"Pedro", 40},
        {"Sofia", 35},
        {"Rafael", 28},
        {"Beatriz", 32}
    };

    for (int i = 0; i < 9; i++) {
        inserir(&filaOriginal, pessoas[i]);
    }

    printf("Fila Original:\n");
    exibirFila(filaOriginal);

    // Invertendo a fila usando a pilha auxiliar
    while (filaOriginal.inicio < filaOriginal.fim) {
        Pessoa p = remover(&filaOriginal);
        push(&auxiliar, p);
    }
    while (auxiliar.topo != -1) {
        Pessoa p = pop(&auxiliar);
        inserir(&filaInvertida, p);
    }
    printf("\nFila Invertida:\n");
    exibirFila(filaInvertida);

    return 0;
}
