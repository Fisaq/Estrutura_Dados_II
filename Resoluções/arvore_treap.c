// Aluno: Isaque Ferreira de Paula Reis
// Turma: CC6N

// Árvore Treap

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura de um nó na árvore treap
typedef struct No {
    int chave;          
    int prioridade;     
    struct No *esq, *dir; 
} No;


No* novoNo(int chave) {
    No* no = (No*)malloc(sizeof(No));
    no->chave = chave;
    no->prioridade = rand() % 100; // Gera uma prioridade aleatória
    no->esq = no->dir = NULL;
    return no;
}


No* rotacaoDireita(No* y) {
    No* x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    return x;
}


No* rotacaoEsquerda(No* x) {
    No* y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    return y;
}


No* inserir(No* raiz, int chave) {
    if (raiz == NULL) return novoNo(chave);

    if (chave < raiz->chave) {
        raiz->esq = inserir(raiz->esq, chave);
        if (raiz->esq->prioridade > raiz->prioridade)
            raiz = rotacaoDireita(raiz);
    } else {
        raiz->dir = inserir(raiz->dir, chave);
        if (raiz->dir->prioridade > raiz->prioridade)
            raiz = rotacaoEsquerda(raiz);
    }
    return raiz;
}


No* buscar(No* raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave)
        return raiz;
    if (chave < raiz->chave)
        return buscar(raiz->esq, chave);
    return buscar(raiz->dir, chave);
}


No* excluir(No* raiz, int chave) {
    if (raiz == NULL) return raiz;

    if (chave < raiz->chave)
        raiz->esq = excluir(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = excluir(raiz->dir, chave);
    else {
        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            raiz = temp;
        } else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            raiz = temp;
        } else if (raiz->esq->prioridade < raiz->dir->prioridade) {
            raiz = rotacaoEsquerda(raiz);
            raiz->esq = excluir(raiz->esq, chave);
        } else {
            raiz = rotacaoDireita(raiz);
            raiz->dir = excluir(raiz->dir, chave);
        }
    }
    return raiz;
}

// Exibir a árvore em ordem (mostra a estrutura da árvore)
void exibir(No* raiz) {
    if (raiz != NULL) {
        exibir(raiz->esq);
        printf("Chave: %d, Prioridade: %d\n", raiz->chave, raiz->prioridade);
        exibir(raiz->dir);
    }
}

// Menu principal
int main() {
    srand(time(0)); 
    No* raiz = NULL;
    int opcao, chave;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Inserir\n");
        printf("2. Excluir\n");
        printf("3. Buscar\n");
        printf("4. Exibir\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor para inserir: ");
                scanf("%d", &chave);
                raiz = inserir(raiz, chave);
                break;
            case 2:
                printf("Digite o valor para excluir: ");
                scanf("%d", &chave);
                raiz = excluir(raiz, chave);
                break;
            case 3:
                printf("Digite o valor para buscar: ");
                scanf("%d", &chave);
                No* resultado = buscar(raiz, chave);
                if (resultado != NULL)
                    printf("Valor %d encontrado com prioridade %d\n", resultado->chave, resultado->prioridade);
                else
                    printf("Valor %d não encontrado\n", chave);
                break;
            case 4:
                printf("Árvore em ordem:\n");
                exibir(raiz);
                break;
            case 5:
                printf("Fim do Programa!.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
