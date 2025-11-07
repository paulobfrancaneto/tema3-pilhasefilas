#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50

typedef struct {
    char nome[30]; // Nome da Pessoa
    int idade; // Idade da pessoa
} Pessoa;

typedef struct {
    Pessoa dados[MAX];
    int inicio, fim, total;
} Fila;

typedef struct {
    Pessoa dados[MAX];
    int topo;
} Pilha;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

void inicializarPilha(Pilha *p) {
    p->topo = -1; // Indica que a pilha está vazia
}

void inserirFila(Fila *f, Pessoa p) {
    if (f->total == MAX) {
        printf("Fila cheia! Nao e possivel inserir.\n");
        return;
    }
    f->dados[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

Pessoa removerFila(Fila *f) {
    Pessoa p_erro = {"", -1}; // Valor sentinela

    if (f->total == 0) {
        printf("Fila vazia! Nao e possivel retirar.\n");
        return p_erro;
    }
    Pessoa p = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return p;
}

void pushPilha(Pilha *p, Pessoa pessoa) {
    if (p->topo == MAX - 1) {
        printf("Pilha cheia! Nao e possivel inserir.\n");
        return;
    }
    p->dados[++(p->topo)] = pessoa;
}

void popPilha(Pilha *p, Pessoa *pessoa) {
    Pessoa p_erro = {"", -1}; // Valor sentinela

    if (p->topo == -1) {
        printf("Pilha vazia! Nao e possivel retirar.\n");
        *pessoa = p_erro;
        return;
    }
    *pessoa = p->dados[(p->topo)--];
}

Pessoa peek(Pilha *p) {
    Pessoa p_erro = {"", -1}; // Valor sentinela

    if (p->topo == -1) {
        printf("Pilha vazia! Nao ha elemento no topo.\n");
        return p_erro;
    }
    return p->dados[p->topo];
}

void mostrarFila(Fila *f) {
    if (f->total == 0) {
        printf("Fila vazia!\n");
        return;
    }
    
    printf("Fila de Pessoas: ");
    for (int i = 0; i < f->total; i++) {
        int index = (f->inicio + i) % MAX;
        // Usabilidade: Mostra em linha para melhor visualização horizontal
        printf("[%s %d]%s", f->dados[index].nome, f->dados[index].idade, (i == f->total - 1 ? "" : " ---> "));
    }
    printf("\n");
}

void mostrarPilha(Pilha *p) {
    if (p->topo == -1) {
        printf("Pilha vazia!\n");
        return;
    }
    
    printf("Pilha de Pessoas com Prioridade Abaixo:\n");
    for (int i = p->topo; i >= 0; i--) {
        // Usabilidade: Mostra em linha para melhor visualização horizontal
        printf("[%s %d]%s", p->dados[i].nome, p->dados[i].idade, (i == 0 ? "" : " <-> "));
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    Fila fila;
    Pilha pilhaPrioridade;

    inicializarFila(&fila);
    inicializarPilha(&pilhaPrioridade);

    // Exemplo de uso
    Pessoa pessoas[] = {
        {"Carlos", 45},
        {"Joana", 62},
        {"Lucas", 30},
        {"Maria", 75},
        {"Renan", 56}
    };

    for (int i = 0; i < 5; i++) {
        inserirFila(&fila, pessoas[i]);
    }

    while (fila.inicio < fila.fim || fila.total > 0) {
        Pessoa atual = removerFila(&fila);
        if (atual.idade >= 60) {
            pushPilha(&pilhaPrioridade, atual);
            printf("Pessoa %s (ID %d) movida para a pilha de prioridade.\n", atual.nome, atual.idade);
        } else {
            printf("Pessoa %s (ID %d) atendida normalmente.\n", atual.nome, atual.idade);
        }
    }

    printf("\nAtendendo pessoas na pilha de prioridade:\n");
    mostrarPilha(&pilhaPrioridade);

    return 0;
}
