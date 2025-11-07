typedef struct {
    int valor;
    char nome[30];
} Pessoa;

#include<stdio.h>
#include "exemplo_fila.h"

void inicializar(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(const Fila *f) {
    return f->total == MAX;
}

int filaVazia(const Fila *f) {
    return f->total == 0;
}

void inserir(Fila *f, Pessoa e) {
    if (filaCheia(f)) // Impede inserção se estiver cheia
        printf("\nFila cheia! Nao e possivel inserir.\n");
        return;
    f->itens[f->fim] = e;            // Insere no final
    f->fim = (f->fim + 1) % MAX;     // Atualiza circularmente o índice
    f->total++;                      // Incrementa a contagem de Pessoas
}

Pessoa retirar(Fila *f) {
    Pessoa vazio = {-1};               // Valor padrão caso a fila esteja vazia
    if (filaVazia(f)) 
        return vazio;      // Evita remoção se estiver vazia
    Pessoa e = f->itens[f->inicio];    // Armazena o item a ser removido
    f->inicio = (f->inicio + 1) % MAX;   // Atualiza o índice de início
    f->total--;                          // Diminui o total
    return e;                            // Retorna o item removido
}
 
Pessoa espiar(const Fila *f) {
    Pessoa vazio = {-1};              // Valor padrão se a fila estiver vazia
    if (filaVazia(f))
        return vazio;     // Impede acesso indevido
    return f->itens[f->inicio];         // Retorna o Pessoa da frente
}