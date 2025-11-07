#include<stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    char nome[2];
    int id_exclusivo;
} Peca;

typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} FilaPecas;

void inicializar(FilaPecas *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(const FilaPecas *f) {
    return f->total == MAX;
}

int filaVazia(const FilaPecas *f) {
    return f->total == 0;
}

void inserir(FilaPecas *f, Peca p) {
    if (filaCheia(f)) {
        printf("\nFila cheia! Nao e possivel inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void remover(FilaPecas *f) {
    if (filaVazia(f)) {
        printf("\nFila vazia! Nao e possivel retirar.\n");
        return;
    }
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    printf("\nRetirado da fila: Nome: %s, ID Exclusivo: %d\n", p.nome, p.id_exclusivo);
}

void mostrarFila(const FilaPecas *f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }
    printf("Conteudo da fila:\n");
    for (int i = 0; i < f->total; i++) {
        int index = (f->inicio + i) % MAX;
        printf("Peca %d: Nome: %s, ID Exclusivo: %d\n", i + 1, f->itens[index].nome, f->itens[index].id_exclusivo);
    }
}

int main(int argc, char const *argv[])
{
    FilaPecas f;
    inicializar(&f);

    Peca p1 = {"T", 0};
    Peca p2 = {"O", 1};
    Peca p3 = {"L", 2};
    Peca p4 = {"I", 3};
    Peca p5 = {"I", 4};

    inserir(&f, p1);
    inserir(&f, p2);
    inserir(&f, p3);
    inserir(&f, p4);
    inserir(&f, p5); // Fila cheia

    int opcao;
    while (1) {
        printf("\nMenu:\n1 - Jogar uma peça (remover)\n2 - Inserir nova peça (inserir)\n3 - Exibir estado atual da fila\nEscolha uma opção (Ctrl+D para sair): ");
        if (scanf("%d", &opcao) != 1) break;

        if (opcao == 1) {
            remover(&f);
        } else if (opcao == 2) {
            if (filaCheia(&f)) {
                printf("\nFila cheia! Nao e possivel inserir.\n");
            } else {
                Peca p;
                printf("Digite o nome da peça em Maiúsculo (max 1 caractere): ");
                if (scanf("%1s", p.nome) != 1) {
                    printf("Entrada inválida.\n");
                    break;
                }
                printf("Digite o id exclusivo: ");
                if (scanf("%d", &p.id_exclusivo) != 1) {
                    printf("Entrada inválida.\n");
                    break;
                }
                inserir(&f, p);
            }
        } else if (opcao == 3) {
            // apenas exibir a fila abaixo
        } else {
            printf("Opção inválida.\n");
        }

        // Exibir o estado atual da fila após cada ação
        mostrarFila(&f);
    }


    return 0;
}
