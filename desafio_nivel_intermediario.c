#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Necessário para gerar números aleatórios

#define MAX_FILA 5
#define MAX_PILHA 3

// Variável global (ou static) para rastrear o ID mais alto já gerado, 
// garantindo que cada peça tenha um ID ÚNICO.
static int PROXIMO_ID_GLOBAL = 0; 

// --- ESTRUTURA DAS PEÇAS ---
typedef struct
{
    char nome[2]; // Tamanho 2 para armazenar o caractere + o terminador nulo '\0'
    int id_exclusivo;
} Peca;

// --- ESTRUTURA DA FILA (Próximas Peças) ---
typedef struct
{
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} FilaPecas;

// --- ESTRUTURA DA PILHA (Peça Reservada) ---
typedef struct
{
    Peca itens[MAX_PILHA];
    int topo;
} PilhaPecas;

// ====================================================================
// FUNÇÕES DE PEÇAS
// ====================================================================

Peca gerarPeca()
{
    Peca p;
    char opcoes[] = {'I', 'O', 'T', 'L'};

    // Escolhe aleatoriamente uma letra das opções
    p.nome[0] = opcoes[rand() % 4];
    p.nome[1] = '\0';
    
    // Atribui o ID global e o incrementa para a próxima peça
    p.id_exclusivo = PROXIMO_ID_GLOBAL++; 

    return p;
}

// ====================================================================
// FUNÇÕES DA PILHA
// ====================================================================

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

    p->topo++; // Avança o topo
    p->itens[p->topo] = nova; // Insere o novo Peca
}

// Funções pop e peek não alteradas, estão corretas.

void pop(PilhaPecas *p, Peca *removida)
{
    if (pilhaVazia(p))
    {
        printf("Erro: Pilha vazia. Não há Peças para remover.\n");
        // Usamos o ID -1 para indicar que a peça é inválida/erro, útil para funções chamadoras.
        removida->id_exclusivo = -1; 
        return;
    }

    *removida = p->itens[p->topo]; // Copia o valor do topo
    p->topo--;                     // Decrementa o topo
}

void mostrarPilha(const PilhaPecas *p)
{
    printf("\n--- PILHA DE RESERVA (Capacidade Max: %d) ---\n", MAX_PILHA);
    if (pilhaVazia(p))
    {
        printf("Pilha vazia!\n");
        return;
    }
    
    printf("Pilha de Reserva (Topo --> Base): ");
    for (int i = p->topo; i >= 0; i--)
    {
        // Usabilidade: Mostra em linha para melhor visualização horizontal
        printf("[%s %d]%s", p->itens[i].nome, p->itens[i].id_exclusivo, (i == 0 ? "" : " <-> "));
    }
    printf("\n");
}

// ====================================================================
// FUNÇÕES DA FILA
// ====================================================================

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
        printf("\nErro: Fila cheia! Não é possível inserir. \n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

Peca remover(FilaPecas *f) // Alterado para retornar a Peca removida
{
    Peca peca_erro = {"E", -1}; // Valor sentinela

    if (filaVazia(f))
    {
        printf("\nErro: Fila vazia! Nao e possivel retirar.\n");
        return peca_erro;
    }
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
    // Não imprime aqui. A função principal irá imprimir para encapsular a lógica.
    return p;
}

void mostrarFila(const FilaPecas *f)
{
    printf("\n--- FILA DE PEÇAS FUTURAS (Prox --> Fim) ---\n");
    if (filaVazia(f))
    {
        printf("Fila vazia!\n");
        return;
    }
    
    printf("Fila de Peças: ");
    for (int i = 0; i < f->total; i++)
    {
        int index = (f->inicio + i) % MAX_FILA;
        // Usabilidade: Mostra em linha para melhor visualização horizontal
        printf("[%s %d]%s", f->itens[index].nome, f->itens[index].id_exclusivo, (i == f->total - 1 ? "" : " -> "));
    }
    printf("\n");
}

// ====================================================================
// FUNÇÕES DE AÇÃO DO JOGO
// ====================================================================

// Ação 2: Move a peça da fila para a pilha de reserva
void reservarPeca(FilaPecas *f, PilhaPecas *p)
{
    if (pilhaCheia(p)) {
        printf("\nErro: Pilha de Reserva cheia! Nao e possivel reservar.\n");
        return;
    }
    
    Peca peca_removida = remover(f); // Tenta remover da fila
    
    if (peca_removida.id_exclusivo == -1) {
        // Se a fila estava vazia, a função remover já imprimiu a mensagem de erro.
        return;
    }

    push(p, peca_removida);
    printf("\nRESERVOU: Peça %s (ID %d) movida da Fila para o Topo da Pilha.\n", 
           peca_removida.nome, peca_removida.id_exclusivo);
}

// Ação 3: Usa a peça do topo da pilha de reserva
void usarPecaReservada(PilhaPecas *p)
{
    Peca peca_liberada;
    pop(p, &peca_liberada); // Tenta remover da pilha
    
    if (peca_liberada.id_exclusivo == -1) {
        // Se a pilha estava vazia, a função pop já imprimiu a mensagem de erro.
        return;
    }

    // A peça é "usada" e não volta para o jogo, então não é inserida em lugar nenhum.
    printf("\nUSOU: Peça %s (ID %d) removida do Topo da Pilha e utilizada no jogo.\n", 
           peca_liberada.nome, peca_liberada.id_exclusivo);
}


// ====================================================================
// FUNÇÕES DE INICIALIZAÇÃO
// ====================================================================

void inicializarJogo(FilaPecas *f, PilhaPecas *p)
{
    inicializarFila(f);
    inicializarPilha(p);

    // Reinicia o contador global de ID para garantir que a inicialização comece em 0
    PROXIMO_ID_GLOBAL = 0; 

    // Insere 5 peças INICIAIS na Fila (Fila deve estar cheia)
    for (int i = 0; i < MAX_FILA; i++) {
        inserir(f, gerarPeca());
    }
    
    // Insere 2 peças INICIAIS na Pilha de Reserva
    for (int i = 0; i < 2; i++) {
        push(p, gerarPeca());
    }
    
    printf("--- JOGO INICIALIZADO ---\n");
    printf("Fila de Peças preenchida com %d peças iniciais (ID %d a %d).\n", 
           MAX_FILA, PROXIMO_ID_GLOBAL - MAX_FILA - 2, PROXIMO_ID_GLOBAL - 3);
    printf("Pilha de Reserva preenchida com 2 peças (ID %d e %d).\n", 
           PROXIMO_ID_GLOBAL - 2, PROXIMO_ID_GLOBAL - 1);
    printf("--------------------------\n");
}

int main(int argc, char const *argv[])
{
    // Inicializa o gerador de números aleatórios com o tempo atual (para ser realmente aleatório)
    srand(time(NULL)); 

    FilaPecas f;
    PilhaPecas p;

    inicializarJogo(&f, &p);

    int opcao;
    
    // Mostra o estado inicial
    mostrarFila(&f);
    mostrarPilha(&p);

    while (1)
    {
        printf("\n\nOpções de Ação:\n");
        printf("| Código | Ação                       |\n");
        printf("|---|----------------------------|\n");
        printf("| 1 | Jogar peça da fila (dequeue) |\n");
        printf("| 2 | Reservar peça (Fila -> Pilha)|\n");
        printf("| 3 | Usar peça reservada (pop)  |\n");
        printf("| 0 | Sair                       |\n");
        printf("Opção: ");

        if (scanf("%d", &opcao) != 1 || opcao == 0)
            break;
        
        Peca peca_removida; // Usada nas opções 1 e 3

        if (opcao == 1) // JOGAR UMA PEÇA
        {
            peca_removida = remover(&f);
            
            if (peca_removida.id_exclusivo != -1) {
                printf("\nJOGOU: Peça %s (ID %d) removida da fila e usada no jogo.\n", 
                       peca_removida.nome, peca_removida.id_exclusivo);
                
                // REQUISITO: A cada ação, uma nova peça é adicionada ao final da fila
                inserir(&f, gerarPeca()); 
                printf("AUTOMÁTICO: Nova peça (ID %d) adicionada ao final da fila.\n", 
                       PROXIMO_ID_GLOBAL - 1);
            }
        }
        else if (opcao == 2) // RESERVAR UMA PEÇA
        {
            // A função já trata as regras de Pilha cheia/Fila vazia
            reservarPeca(&f, &p); 

            // Se a reserva foi bem-sucedida, insere a nova peça
            if (!pilhaCheia(&p) && !filaVazia(&f)) {
                // Se a peça foi removida da fila para a pilha
                inserir(&f, gerarPeca());
                printf("AUTOMÁTICO: Nova peça (ID %d) adicionada ao final da fila.\n", 
                       PROXIMO_ID_GLOBAL - 1);
            }
        }
        else if (opcao == 3) // USAR UMA PEÇA RESERVADA
        {
            int era_vazia = pilhaVazia(&p);
            
            usarPecaReservada(&p);
            
            if (!era_vazia) { // Se a pilha não estava vazia e a peça foi usada
                // REQUISITO: A cada ação, uma nova peça é adicionada ao final da fila
                inserir(&f, gerarPeca());
                printf("AUTOMÁTICO: Nova peça (ID %d) adicionada ao final da fila.\n", 
                       PROXIMO_ID_GLOBAL - 1);
            }
        }
        else
        {
            printf("\nOpção inválida. Escolha 1, 2, 3 ou 0.\n");
        }

        // Exibir o estado atual da fila e pilha após cada ação
        mostrarFila(&f);
        mostrarPilha(&p);
    }
    
    printf("\nPrograma encerrado.\n");

    return 0;
}