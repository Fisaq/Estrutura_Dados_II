// Aluno: Isaque Ferreira de Paula Reis
// Turma: CC6N

//Árvore B+
#include <stdio.h>
#include <stdlib.h>

#define T 3 // Grau mínimo (número mínimo de filhos)

// Estrutura de um nó da árvore B+
typedef struct No {
    int n;                    // Número de chaves
    int chave[2 * T - 1];     // Array de chaves
    struct No* filho[2 * T];  // Array de ponteiros para filhos
    struct No* prox;          // Ponteiro para o próximo nó folha
    int folha;                // Verdadeiro se é uma folha
} No;

// Função para criar um novo nó
No* novoNo(int folha) {
    No* no = (No*)malloc(sizeof(No));
    no->n = 0;
    no->folha = folha;
    no->prox = NULL;
    for (int i = 0; i < 2 * T; i++)
        no->filho[i] = NULL;
    return no;
}

// Função para inserir uma chave em um nó não cheio
void inserirNaoCheio(No* no, int chave) {
    int i = no->n - 1;

    if (no->folha) {
        // Inserção em nó folha
        while (i >= 0 && chave < no->chave[i]) {
            no->chave[i + 1] = no->chave[i];
            i--;
        }
        no->chave[i + 1] = chave;
        no->n++;
    } else {
        // Inserção em nó interno
        while (i >= 0 && chave < no->chave[i])
            i--;
        i++;

        if (no->filho[i]->n == 2 * T - 1) {
            // Se o filho estiver cheio, divida-o
            No* filho = no->filho[i];
            No* novoFilho = novoNo(filho->folha);
            novoFilho->n = T - 1;

            for (int j = 0; j < T - 1; j++)
                novoFilho->chave[j] = filho->chave[j + T];

            if (!filho->folha) {
                for (int j = 0; j < T; j++)
                    novoFilho->filho[j] = filho->filho[j + T];
            } else {
                novoFilho->prox = filho->prox;
                filho->prox = novoFilho;
            }

            filho->n = T - 1;

            for (int j = no->n; j >= i + 1; j--)
                no->filho[j + 1] = no->filho[j];

            no->filho[i + 1] = novoFilho;

            for (int j = no->n - 1; j >= i; j--)
                no->chave[j + 1] = no->chave[j];

            no->chave[i] = filho->chave[T - 1];
            no->n++;
        }
        inserirNaoCheio(no->filho[i], chave);
    }
}

// Função para inserir uma chave na árvore B+
void inserir(No** raiz, int chave) {
    if (*raiz == NULL) {
        *raiz = novoNo(1);
        (*raiz)->chave[0] = chave;
        (*raiz)->n = 1;
    } else {
        if ((*raiz)->n == 2 * T - 1) {
            No* novoRaiz = novoNo(0);
            novoRaiz->filho[0] = *raiz;
            *raiz = novoRaiz;

            inserirNaoCheio(novoRaiz, chave);
        } else {
            inserirNaoCheio(*raiz, chave);
        }
    }
}

// Função para buscar uma chave na árvore B+
No* buscar(No* raiz, int chave) {
    int i = 0;

    while (i < raiz->n && chave > raiz->chave[i])
        i++;

    if (i < raiz->n && chave == raiz->chave[i] && raiz->folha)
        return raiz;

    if (raiz->folha)
        return NULL;

    return buscar(raiz->filho[i], chave);
}

// Função para exibir a árvore B+ em ordem
void exibir(No* raiz) {
    No* folha = raiz;
    while (!folha->folha)
        folha = folha->filho[0];

    while (folha != NULL) {
        for (int i = 0; i < folha->n; i++)
            printf("%d ", folha->chave[i]);
        folha = folha->prox;
    }
}

// Função principal com menu
int main() {
    No* raiz = NULL;
    int opcao, chave;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Inserir\n");
        printf("2. Buscar\n");
        printf("3. Exibir\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor para inserir: ");
                scanf("%d", &chave);
                inserir(&raiz, chave);
                break;
            case 2:
                printf("Digite o valor para buscar: ");
                scanf("%d", &chave);
                No* resultado = buscar(raiz, chave);
                if (resultado != NULL)
                    printf("Valor %d encontrado.\n", chave);
                else
                    printf("Valor %d não encontrado.\n", chave);
                break;
            case 3:
                printf("Árvore B+ em ordem:\n");
                exibir(raiz);
                printf("\n");
                break;
            case 4:
                printf("Fim do Programa!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
