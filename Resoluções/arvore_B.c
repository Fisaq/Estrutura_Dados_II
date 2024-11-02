// Aluno: Isaque Ferreira de Paula Reis
// Turma: CC6N

#include <stdio.h>
#include <stdlib.h>

#define T 3 // Grau mínimo (número mínimo de filhos)

// Estrutura de um nó da árvore B
typedef struct No {
    int n;                // Número de chaves
    int chave[2 * T - 1]; // Array de chaves
    struct No* filho[2 * T]; // Array de ponteiros para filhos
    int folha;            // Verdadeiro se é uma folha
} No;

// Função para criar um novo nó
No* novoNo(int folha) {
    No* no = (No*)malloc(sizeof(No));
    no->n = 0;
    no->folha = folha;
    for (int i = 0; i < 2 * T; i++)
        no->filho[i] = NULL;
    return no;
}

// Função para inserir uma chave em um nó não cheio
void inserirNaoCheio(No* no, int chave) {
    int i = no->n - 1;

    if (no->folha) {
        while (i >= 0 && chave < no->chave[i]) {
            no->chave[i + 1] = no->chave[i];
            i--;
        }
        no->chave[i + 1] = chave;
        no->n++;
    } else {
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

// Função para inserir uma chave na árvore B
void inserir(No** raiz, int chave) {
    if (*raiz == NULL) {
        *raiz = novoNo(1);
        (*raiz)->chave[0] = chave;
        (*raiz)->n = 1;
    } else {
        if ((*raiz)->n == 2 * T - 1) {
            No* novoRaiz = novoNo(0);
            novoRaiz->filho[0] = *raiz;
            novoRaiz->folha = 0;
            *raiz = novoRaiz;

            inserirNaoCheio(novoRaiz, chave);
        } else {
            inserirNaoCheio(*raiz, chave);
        }
    }
}

void removerNaoCheio(No* no, int i) {
    if (no->folha) {
        for (int j = i + 1; j < no->n; j++)
            no->chave[j - 1] = no->chave[j];
        no->n--;
    } else {
        // Se não for folha
        int chave = no->chave[i];
        
        if (no->filho[i]->n >= T) {
            No* pred = no->filho[i];
            while (!pred->folha)
                pred = pred->filho[pred->n];
            no->chave[i] = pred->chave[pred->n - 1];
            removerNaoCheio(no->filho[i], pred->n - 1);
        } else if (no->filho[i + 1]->n >= T) {
            No* succ = no->filho[i + 1];
            while (!succ->folha)
                succ = succ->filho[0];
            no->chave[i] = succ->chave[0];
            removerNaoCheio(no->filho[i + 1], 0);
        } else {
            No* filho1 = no->filho[i];
            No* filho2 = no->filho[i + 1];

            filho1->chave[T - 1] = chave;

            for (int j = 0; j < filho2->n; j++)
                filho1->chave[j + T] = filho2->chave[j];

            if (!filho1->folha) {
                for (int j = 0; j <= filho2->n; j++)
                    filho1->filho[j + T] = filho2->filho[j];
            }

            filho1->n += filho2->n + 1;
            free(filho2);
            
            for (int j = i + 1; j < no->n; j++)
                no->chave[j - 1] = no->chave[j];

            for (int j = i + 2; j <= no->n; j++)
                no->filho[j - 1] = no->filho[j];

            no->n--;
            removerNaoCheio(filho1, T - 1);
        }
    }
}

void remover(No** raiz, int chave) {
    if (*raiz == NULL) {
        printf("A árvore está vazia. Não é possível remover %d.\n", chave);
        return;
    }

    No* raizTemp = *raiz;

    if (raizTemp->n == 1) {
        removerNaoCheio(raizTemp, 0);
        if (raizTemp->n == 0) {
            No* temp = raizTemp;
            *raiz = raizTemp->filho[0];
            free(temp);
        }
    } else {
        removerNaoCheio(raizTemp, 0);
    }
}

No* buscar(No* raiz, int chave) {
    int i = 0;

    while (i < raiz->n && chave > raiz->chave[i])
        i++;

    if (i < raiz->n && chave == raiz->chave[i])
        return raiz;

    if (raiz->folha)
        return NULL;

    return buscar(raiz->filho[i], chave);
}

// Função para exibir a árvore B em ordem
void exibir(No* raiz) {
    if (raiz != NULL) {
        for (int i = 0; i < raiz->n; i++) {
            if (!raiz->folha)
                exibir(raiz->filho[i]);
            printf("%d ", raiz->chave[i]);
        }
        if (!raiz->folha)
            exibir(raiz->filho[raiz->n]);
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
        printf("3. Remover\n");
        printf("4. Exibir\n");
        printf("5. Sair\n");
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
                printf("Digite o valor para remover: ");
                scanf("%d", &chave);
                remover(&raiz, chave);
                break;
            case 4:
                printf("Árvore B em ordem:\n");
                exibir(raiz);
                printf("\n");
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
