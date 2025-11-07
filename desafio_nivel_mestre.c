#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Necessário para gerar números aleatórios
#include <string.h> // Necessário para manipulação de strings (strncpy)

#define MAX_FILA 5
#define MAX_PILHA 3

// Variável global para rastrear o ID mais alto já gerado, 
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
// FUNÇÕES DA PILHA (LIFO)
// ====================================================================

void inicializarPilha(PilhaPecas *p)
{
    p->topo = -1;
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
        printf("Erro: Pilha cheia. Não é possível inserir.\n");
        return;
    }

    p->topo++; 
    p->itens[p->topo] = nova; 
}

void pop(PilhaPecas *p, Peca *removida)
{
    if (pilhaVazia(p))
    {
        printf("Erro: Pilha vazia. Não há Peças para remover.\n");
        removida->id_exclusivo = -1; // Valor sentinela de erro
        return;
    }

    *removida = p->itens[p->topo]; 
    p->topo--;                     
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
        printf("[%s %d]%s", p->itens[i].nome, p->itens[i].id_exclusivo, (i == 0 ? "" : " <-> "));
    }
    printf("\n");
}

// ====================================================================
// FUNÇÕES DA FILA (FIFO Circular)
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
        // Em um sistema Tetris, isso geralmente significa que o jogo acabou, 
        // mas aqui mantemos o erro informativo.
        printf("\nErro: Fila cheia! Não é possível inserir. \n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

Peca remover(FilaPecas *f) 
{
    Peca peca_erro = {"E", -1}; 

    if (filaVazia(f))
    {
        printf("\nErro: Fila vazia! Nao e possivel retirar.\n");
        return peca_erro;
    }
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
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
        printf("[%s %d]%s", f->itens[index].nome, f->itens[index].id_exclusivo, (i == f->total - 1 ? "" : " -> "));
    }
    printf("\n");
}

// ====================================================================
// FUNÇÕES DE AÇÃO E ESTRATÉGIA DO JOGO
// ====================================================================

// Ação 2: Move a peça da frente da fila para o topo da pilha de reserva
void reservarPeca(FilaPecas *f, PilhaPecas *p)
{
    // A validação de Pilha Cheia é feita na função chamadora (main) ou em push.
    Peca peca_removida = remover(f); 
    
    if (peca_removida.id_exclusivo == -1) {
        return; // Fila estava vazia
    }

    push(p, peca_removida);
    printf("\nRESERVOU: Peça %s (ID %d) movida da Fila para o Topo da Pilha.\n", 
           peca_removida.nome, peca_removida.id_exclusivo);
}

// Ação 3: Usa a peça do topo da pilha de reserva
void usarPecaReservada(PilhaPecas *p)
{
    Peca peca_liberada;
    pop(p, &peca_liberada);
    
    if (peca_liberada.id_exclusivo == -1) {
        return; // Pilha estava vazia
    }

    printf("\nUSOU: Peça %s (ID %d) removida do Topo da Pilha e utilizada no jogo.\n", 
           peca_liberada.nome, peca_liberada.id_exclusivo);
}


 // Ação 4: Troca a peça da frente da fila (f->inicio) com a peça do topo da pilha (p->topo).

void trocarPecaAtual(FilaPecas *f, PilhaPecas *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("\nERRO: Nao e possivel realizar a troca. A Fila ou Pilha estao vazias.\n");
        return;
    }
    
    // 1. Armazena a peça da frente da Fila (f->inicio)
    Peca temp_peca_fila = f->itens[f->inicio];
    
    // 2. Copia a peça do Topo da Pilha para a frente da Fila
    f->itens[f->inicio] = p->itens[p->topo];
    
    // 3. Copia a peça temporária (que estava na fila) para o Topo da Pilha
    p->itens[p->topo] = temp_peca_fila;

    printf("\nTROCA SIMPLES: Peça %s (ID %d) da Fila e Peça %s (ID %d) da Pilha foram trocadas.\n",
           f->itens[f->inicio].nome, f->itens[f->inicio].id_exclusivo,
           p->itens[p->topo].nome, p->itens[p->topo].id_exclusivo);
}


// Ação 5: Alterna as 3 primeiras peças da fila com as 3 peças da pilha.

void trocarMultipla(FilaPecas *f, PilhaPecas *p) {
    // Validação: Ambas devem ter no mínimo 3 peças
    if (f->total < MAX_PILHA || p->topo < MAX_PILHA - 1) { 
        printf("\nERRO: Troca Múltipla requer que a Fila tenha %d pecas e a Pilha esteja cheia (%d pecas).\n", 
               MAX_PILHA, MAX_PILHA);
        return;
    }
    
    Peca temp_pilha[MAX_PILHA];
    int i;

    // 1. Mover as 3 peças da Fila (f->inicio, f->inicio+1, f->inicio+2) para um buffer temporário.
    for (i = 0; i < MAX_PILHA; i++) {
        int index_fila = (f->inicio + i) % MAX_FILA;
        temp_pilha[i] = f->itens[index_fila];
    }
    
    // 2. Mover as 3 peças da Pilha (p->topo, p->topo-1, p->topo-2) para os 3 primeiros lugares da Fila.
    for (i = 0; i < MAX_PILHA; i++) {
        int index_fila = (f->inicio + i) % MAX_FILA;
        int index_pilha = p->topo - i;
        f->itens[index_fila] = p->itens[index_pilha];
    }

    // 3. Mover o buffer temporário (as peças da fila) para a Pilha.
    // NOTE: A ordem de inserção da pilha deve ser LIFO.
    // A peça que era f->inicio (i=0) deve ir para a base da pilha.
    // A peça que era f->inicio+2 (i=2) deve ir para o topo da pilha (p->topo).
    for (i = 0; i < MAX_PILHA; i++) {
        p->itens[p->topo - i] = temp_pilha[MAX_PILHA - 1 - i];
    }

    printf("\nTROCA MÚLTIPLA: As %d primeiras pecas da Fila e todas as %d pecas da Pilha foram alternadas.\n", MAX_PILHA, MAX_PILHA);
}


// ====================================================================
// FUNÇÕES DE INICIALIZAÇÃO
// ====================================================================

void inicializarJogo(FilaPecas *f, PilhaPecas *p)
{
    inicializarFila(f);
    inicializarPilha(p);

    PROXIMO_ID_GLOBAL = 0; 

    // Insere 5 peças INICIAIS na Fila
    for (int i = 0; i < MAX_FILA; i++) {
        inserir(f, gerarPeca());
    }
    
    // Insere 2 peças INICIAIS na Pilha de Reserva (não cheia)
    for (int i = 0; i < 2; i++) {
        push(p, gerarPeca());
    }
    
    printf("--- JOGO INICIALIZADO ---\n");
    printf("Fila de Peças preenchida com %d peças iniciais.\n", MAX_FILA);
    printf("Pilha de Reserva preenchida com 2 peças (capacidade max: %d).\n", MAX_PILHA);
    printf("--------------------------\n");
}

int main(int argc, char const *argv[])
{
    // Inicializa o gerador de números aleatórios
    srand(time(NULL)); 

    FilaPecas f;
    PilhaPecas p;

    inicializarJogo(&f, &p);
    
    // Mostra o estado inicial
    mostrarFila(&f);
    mostrarPilha(&p);

    int opcao;
    while (1)
    {
        printf("\n\nOpções disponíveis:\n");
        printf("| Código | Ação                                           |\n");
        printf("|---|------------------------------------------------|\n");
        printf("| 1 | Jogar peça da frente da fila (dequeue)         |\n");
        printf("| 2 | Enviar peça da fila para a pilha de reserva    |\n");
        printf("| 3 | Usar peça da pilha de reserva (pop)            |\n");
        printf("| 4 | Trocar peça da frente da fila com o topo da pilha|\n");
        printf("| 5 | Trocar os 3 primeiros da fila com as 3 da pilha|\n");
        printf("| 0 | Sair                                           |\n");
        printf("Opção: ");

        if (scanf("%d", &opcao) != 1 || opcao == 0)
            break;
        
        Peca peca_removida;
        int sucesso = 0; // Flag para rastrear se uma peça foi removida ou enviada/usada.

        if (opcao == 1) // 1 - Jogar peça da frente da fila
        {
            peca_removida = remover(&f);
            if (peca_removida.id_exclusivo != -1) {
                printf("\nJOGOU: Peça %s (ID %d) removida da fila e usada no jogo.\n", peca_removida.nome, peca_removida.id_exclusivo);
                sucesso = 1;
            }
        }
        else if (opcao == 2) // 2 - Enviar peça da fila para a pilha de reserva
        {
            int era_cheia = pilhaCheia(&p);
            int era_vazia_fila = filaVazia(&f);
            
            reservarPeca(&f, &p); 
            
            // Sucesso se a pilha não estava cheia E a fila não estava vazia
            if (!era_cheia && !era_vazia_fila) {
                sucesso = 1;
            }
        }
        else if (opcao == 3) // 3 - Usar peça da pilha de reserva
        {
            int era_vazia_pilha = pilhaVazia(&p);
            
            usarPecaReservada(&p);
            
            // Sucesso se a pilha não estava vazia
            if (!era_vazia_pilha) {
                sucesso = 1;
            }
        }
        else if (opcao == 4) // 4 - Trocar peça da frente da fila com o topo da pilha
        {
            // A Troca Simples não remove nem insere peças, apenas troca posições.
            trocarPecaAtual(&f, &p);
            // NÃO GERA NOVA PEÇA
        }
        else if (opcao == 5) // 5 - Trocar os 3 primeiros da fila com as 3 da pilha
        {
            // A Troca Múltipla não remove nem insere peças, apenas troca posições.
            trocarMultipla(&f, &p);
            // NÃO GERA NOVA PEÇA
        }
        else
        {
            printf("\nOpção inválida. Escolha uma das opções disponiveis.\n");
        }
        
        // REQUISITO: Gerar uma nova peça a cada remoção ou envio (Opções 1, 2, 3)
        if (sucesso) {
            if (!filaCheia(&f)) {
                inserir(&f, gerarPeca());
                printf("AUTOMÁTICO: Nova peça (ID %d) adicionada ao final da fila.\n", PROXIMO_ID_GLOBAL - 1);
            } else {
                printf("AUTOMÁTICO: Ação de reposição ignorada, a Fila está cheia.\n");
            }
        }

        // Exibir o estado atual da fila e pilha após cada ação
        mostrarFila(&f);
        mostrarPilha(&p);
    }
    
    printf("\nPrograma encerrado.\n");

    return 0;
}