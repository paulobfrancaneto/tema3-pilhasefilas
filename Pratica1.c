#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[30];
    int idade;
} Pessoa;

#define MAX 5

typedef struct {
    Pessoa itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

inicializaFilar(Fila *f) {
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

void inserir(Fila *f, Pessoa p) {
    if (filaCheia(f)) {
        printf("\n\nFila cheia! Nao e possivel inserir.\n\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

Pessoa remover(Fila *f) {
    if (filaVazia(f)) {
        printf("\n\nFila vazia! Nao e possivel retirar.\n\n");
        return (Pessoa){"",-1};
    }
    Pessoa p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return p;
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

int main(int argc, char const *argv[])
{
    Fila f;
    inicializaFilar(&f); // Inicializa a Fila


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
    inserir(&f, p5); // Concluída a inserção de 5 pessoas na fila

    mostrarFila(&f);

    // Retira uma pessoa da fila
    Pessoa retirado = remover(&f);
    printf("\nRetirado da fila: Nome: %s, Idade: %d\n", retirado.nome, retirado.idade);
    mostrarFila(&f);

    // Retira outra pessoa da fila
    retirado = remover(&f);
    printf("\nRetirado da fila: Nome: %s, Idade: %d\n", retirado.nome, retirado.idade);
    mostrarFila(&f);


    return 0;
}
