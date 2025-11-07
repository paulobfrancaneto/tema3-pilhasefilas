#include<stdio.h>
#include<stdlib.h>

#define MAX 5

typedef struct {
    char nome[50];
    int idade;
} Pessoa;

typedef struct {
    Pessoa itens[MAX];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;  // Indica que a pilha está vazia
}

int pilhaCheia(const Pilha *p) {
    return p->topo == MAX - 1;
}

int pilhaVazia(const Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Pessoa nova) {
    if (pilhaCheia(p)) {
        printf("Erro: pilha cheia. Não é possível inserir.\n");
        return;
    }
 
    p->topo++;              // Avança o topo
    p->itens[p->topo] = nova;  // Insere o novo Pessoa
}

void pop(Pilha *p, Pessoa *removida) {
    if (pilhaVazia(p)) {
        printf("Erro: pilha vazia. Não há Pessoas para remover.\n");
        removida->idade = -1;  // Define um valor padrão para indicar falha
        return;
    }

    *removida = p->itens[p->topo];  // Copia o valor do topo
    p->topo--;               // Decrementa o topo
}

void peek(const Pilha *p, Pessoa *visualizada) {
    if (pilhaVazia(p)) {
        printf("Erro: pilha vazia. Não há Pessoas para visualizar.\n");
        visualizada->idade = -1;  // Define um valor padrão para indicar falha
        return;
    }

    *visualizada = p->itens[p->topo];  // Copia o valor do topo
}

void mostrarPilha(const Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia!\n");
        return;
    }

    printf("Pilha (topo --> base):\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("Pessoa %d: Nome: %s, Idade: %d\n", i + 1, p->itens[i].nome, p->itens[i].idade);
    }
    printf("\n");
}

void liberarPilha(Pilha *p) {
    p->topo = -1;  // Reseta o topo para indicar que a pilha está vazia Pilha Estática Apenas        
}


int main(int argc, char const *argv[])
{
    Pilha p;
    inicializarPilha(&p);

    Pessoa a = {"Alice", 30};
    Pessoa b = {"Bob", 25};
    Pessoa c = {"Charlie", 35};
    // Adicionando Pessoas à Pilha
    push(&p, a);
    push(&p, b);
    push(&p, c);
    // Mostrando o conteúdo da Pilha
    mostrarPilha(&p);

    // Removendo uma Pessoa da Pilha
    Pessoa removida;
    pop(&p, &removida);
    printf("Removida: Nome: %s, Idade: %d\n", removida.nome, removida.idade);

    Pessoa topo;
    peek(&p, &topo);
    printf("Topo atual: Nome: %s, Idade: %d\n", topo.nome, topo.idade);

    return 0;
}


