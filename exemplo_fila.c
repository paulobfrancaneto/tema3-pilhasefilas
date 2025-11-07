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
    if (filaCheia(f)) { // Impede inserção se estiver cheia
        printf("\nFila cheia! Nao e possivel inserir.\n");
        return;
    }
    f->itens[f->fim] = e;            // Insere no final
    f->fim = (f->fim + 1) % MAX;     // Atualiza circularmente o índice
    f->total++;                      // Incrementa a contagem de Pessoas
}

Pessoa retirar(Fila *f) {
    Pessoa vazio = {-1};               // Valor padrão caso a fila esteja vazia
    if (filaVazia(f)){
        printf("\nFila vazia! Nao e possivel retirar.\n"); // Imprime nos casos que a Fila está vazia 
        return vazio;      // Evita remoção se estiver vazia
    }
    Pessoa e = f->itens[f->inicio];    // Armazena o item a ser removido
    f->inicio = (f->inicio + 1) % MAX;   // Atualiza o índice de início
    f->total--;                          // Diminui o total
    return e;                            // Retorna o item removido
}

void mostrarFila(const Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }
    printf("Conteudo da fila:\n");
    for (int i = 0; i < f->total; i++) {
        int index = (f->inicio + i) % MAX;
        printf("Pessoa %d: Nome: %s, Idade: %d\n", i + 1, f->itens[index].nome, f->itens[index].idade);
    }
}
 
Pessoa espiar(const Fila *f) {
    Pessoa vazio = {-1};              // Valor padrão se a fila estiver vazia
    if (filaVazia(f))
        return vazio;     // Impede acesso indevido
    return f->itens[f->inicio];         // Retorna o Pessoa da frente
}

int main(int argc, char const *argv[])
{
    Fila f;
    inicializar(&f); // Inicializa a Fila
    // Abaixo eu crio algumas pessoas para colocar na Fila
    Pessoa p1 = {"Joao", 25};
    Pessoa p2 = {"Maria", 30};
    Pessoa p3 = {"Carlos", 28};
    Pessoa p4 = {"Ana", 22};
    Pessoa p5 = {"Beatriz", 27};

    inserir(&f, p1);
    inserir(&f, p2);
    inserir(&f, p3);
    inserir(&f, p4);
    inserir(&f, p5); // Concluída a inserção de 2 pessoas na fila

    mostrarFila(&f);

    Pessoa retirado = retirar(&f);
    printf("\nRetirado da fila: Nome: %s, Idade: %d\n", retirado.nome, retirado.idade);

    mostrarFila(&f);

    retirado = retirar(&f);
    printf("\nRetirado da fila: Nome: %s, Idade: %d\n", retirado.nome, retirado.idade);

    mostrarFila(&f);

    return 0;
}
