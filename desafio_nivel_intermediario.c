#include <stdio.h>
#include <stdlib.h>

#define MAX_FILA 5
#define MAX_PILHA 3

typedef struct
{
    char nome[2];
    int id_exclusivo;
} Peca;

typedef struct
{
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} FilaPecas;

typedef struct
{
    Peca itens[MAX_PILHA];
    int topo;
} PilhaPecas;

void inicializarPilha(PilhaPecas *p)
{
    p->topo = -1; // Indica que a pilha está vazia
}

int pilhaCheia(const PilhaPecas *p)
{
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(const PilhaPecas *p)
{
    return p->topo == -1;
}

void push(PilhaPecas *p, Peca nova)
{
    if (pilhaCheia(p))
    {
        printf("Erro: pilha cheia. Não é possível inserir.\n");
        return;
    }

    p->topo++;                // Avança o topo
    p->itens[p->topo] = nova; // Insere o novo Peca
}

void pop(PilhaPecas *p, Peca *removida)
{
    if (pilhaVazia(p))
    {
        printf("Erro: pilha vazia. Não há Pecas para remover.\n");
        removida->id_exclusivo = -1; // Define um valor padrão para indicar falha
        return;
    }

    *removida = p->itens[p->topo]; // Copia o valor do topo
    p->topo--;                     // Decrementa o topo
}

void peek(const PilhaPecas *p, Peca *visualizada)
{
    if (pilhaVazia(p))
    {
        printf("Erro: Pilha Vazia. Não há Pecas para visualizar.\n");
        visualizada->id_exclusivo = -1; // Define um valor padrão para indicar falha
        return;
    }

    *visualizada = p->itens[p->topo]; // Copia o valor do topo
}

void mostrarPilha(const PilhaPecas *p)
{
    if (pilhaVazia(p))
    {
        printf("Pilha vazia!\n");
        return;
    }
    printf("Pilha de Reserva (Topo --> Base):\n");
    for (int i = p->topo; i >= 0; i--)
    {
        printf("[%s %d]\n", p->itens[i].nome, p->itens[i].id_exclusivo);
    }
}

void jogarPecaParaPilha(FilaPecas *f, PilhaPecas *p)
{
    if (filaVazia(f))
    {
        printf("\nFila vazia! Nao e possivel retirar.\n");
        return;
    }
    Peca pecaRemovida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;

    push(p, pecaRemovida);
    printf("\nJogou a peça para a pilha de reserva: Nome: %s, ID Exclusivo: %d\n", pecaRemovida.nome, pecaRemovida.id_exclusivo);
}

void liberarPecaDaPilha(FilaPecas *f, PilhaPecas *p)
{
    if (pilhaVazia(p))
    {
        printf("\nPilha vazia! Nao e possivel liberar.\n");
        return;
    }
    Peca pecaLiberada;
    pop(p, &pecaLiberada);

    inserir(f, pecaLiberada);
    printf("\nLiberou a peça da pilha de reserva para a fila: Nome: %s, ID Exclusivo: %d\n", pecaLiberada.nome, pecaLiberada.id_exclusivo);
}

void inicializarFila(FilaPecas *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(const FilaPecas *f)
{
    return f->total == MAX_FILA;
}

int filaVazia(const FilaPecas *f)
{
    return f->total == 0;
}

void inserir(FilaPecas *f, Peca p)
{
    if (filaCheia(f))
    {
        printf("\nFila cheia! Nao e possivel inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

void remover(FilaPecas *f)
{
    if (filaVazia(f))
    {
        printf("\nFila vazia! Nao e possivel retirar.\n");
        return;
    }
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
    printf("\nRetirado da fila: Nome: %s, ID Exclusivo: %d\n", p.nome, p.id_exclusivo);
}

void mostrarFila(const FilaPecas *f)
{
    if (filaVazia(f))
    {
        printf("Fila vazia!\n");
        return;
    }
    printf("Conteudo da fila:\n");
    for (int i = 0; i < f->total; i++)
    {
        int index = (f->inicio + i) % MAX_FILA;
        printf("Peca %d: Nome: %s, ID Exclusivo: %d\n", i + 1, f->itens[index].nome, f->itens[index].id_exclusivo);
    }
}

Peca gerarPeca(FilaPecas *f)
{
    Peca p;
    char opcoes[] = {'I', 'O', 'T', 'L'};
    int maior_id = -1;

    // Encontra o maior ID na fila
    for (int i = 0; i < f->total; i++)
    {
        int index = (f->inicio + i) % MAX_FILA;
        if (f->itens[index].id_exclusivo > maior_id)
        {
            maior_id = f->itens[index].id_exclusivo;
        }
    }

    // Escolhe aleatoriamente uma letra das opções
    p.nome[0] = opcoes[rand() % 4];
    p.nome[1] = '\0';
    p.id_exclusivo = maior_id + 1;

    return p;
}

void inicializarJogo(FilaPecas *f, PilhaPecas *p)
{
    inicializarFila(f);
    inicializarPilha(p);

    // Gerando as Peças para a Lista
    Peca p1 = {"T", 0};
    Peca p2 = {"O", 1};
    Peca p3 = {"L", 2};
    Peca p4 = {"I", 3};
    Peca p5 = {"I", 4};

    // Inserindo as Peças na Fila
    inserir(&f, p1);
    inserir(&f, p2);
    inserir(&f, p3);
    inserir(&f, p4);
    inserir(&f, p5); // Fila cheia

    // Gerando as Peças para a Pilha
    Peca p6 = {"0", 6};
    Peca p7 = {"T", 7};

    // Inserindo as Peças na Pilha
    push(&p, p6);
    push(&p, p7);
}

int main(int argc, char const *argv[])
{
    FilaPecas f;
    PilhaPecas p;

    inicializarJogo(&f, &p);

    int opcao;
    while (1)
    {
        printf("\nMenu:\n1 - JOGAR UMA PEÇA\n2 - RESERVAR UMA PEÇA (inserir)\n3 - USAR UMA PEÇA RESERVADA\n4 - EXIBIR O ESTADO ATUAL\nEscolha uma opção (Ctrl+D para sair): ");
        if (scanf("%d", &opcao) != 1)
            break;

        if (opcao == 1)
        {
            remover(&f);
            inserir(&f, gerarPeca(&f));
        }
        else if (opcao == 2)
        {
            if (pilhaCheia(&f))
            {
                printf("\nPilha cheia! Nao e possivel inserir.\n");
            }
            else
            {
                jogarPecaParaPilha(&f, &p);
            }
        }
        else if (opcao == 3)
        {
            Peca removida;
            pop(&p, &removida);
        }
        else
        {
            printf("Opção inválida.\n");
        }

        // Exibir o estado atual da fila após cada ação
        mostrarFila(&f);
        mostrarPilha(&p);
    }

    return 0;
}
