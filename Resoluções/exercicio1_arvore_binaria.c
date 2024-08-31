//NOME: ISAQUE FERREIRA DE PAULA REIS

#include <stdio.h>
#include <stdlib.h>

// Criando a estrutura do Nó da Árvore
typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

// Função criarNo que vai receber um dado a ser inserido na árvore
No *criarNo(int dado) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro: Não foi possível alocar memória no novo Nó\n");
        return NULL;
    }
    novoNo->dado = dado;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    printf("Novo Nó criado com valor %d\n", dado);
    return novoNo;
}

// Função recursiva que insere um Novo dado nos Nós da Árvore
No *inserirNo(No *noRaiz, int dado) {
    if (noRaiz == NULL) {
        return criarNo(dado);
    }
    if (dado <= noRaiz->dado) {
        noRaiz->esq = inserirNo(noRaiz->esq, dado);
    } else {
        noRaiz->dir = inserirNo(noRaiz->dir, dado);
    }
    return noRaiz;
}

// Função para pesquisar um determinado valor na Árvore
void pesquisarNo(No *raiz, int dado) {
    if (raiz == NULL) {
        printf("Valor %d não encontrado!\n", dado);
        return;
    }
    if (dado < raiz->dado) {
        pesquisarNo(raiz->esq, dado);
    } else if (dado > raiz->dado) {
        pesquisarNo(raiz->dir, dado);
    } else {
        printf("Valor %d encontrado!\n", dado);
    }
}

// Função para excluir um Nó da Árvore
No *excluir(No *raiz, int dado) {
    if (raiz == NULL) {
        return raiz;
    }
    if (dado < raiz->dado) {
        raiz->esq = excluir(raiz->esq, dado);
    } else if (dado > raiz->dado) {
        raiz->dir = excluir(raiz->dir, dado);
    } else {
        if (raiz->esq == NULL) {
            No *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        No *temp = raiz->dir;
        while (temp && temp->esq != NULL) {
            temp = temp->esq;
        }
        raiz->dado = temp->dado;
        raiz->dir = excluir(raiz->dir, temp->dado);
    }
    return raiz;
}

int main() {
    
    No *raiz = NULL;
    int dado;
    int opcao = -1;

    while (opcao != 0) {
        
        printf("\nMenu do Sistema\n1 - Inserir Nó na Árvore\n2 - Excluir Nó da Árvore\n5 - Pesquisar Nó\n0
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Informe o valor do próximo Nó: \nR: ");
                scanf("%d", &dado);
                raiz = inserirNo(raiz, dado);
                printf("Nó inserido com sucesso!\n");
                break;
            case 2:
                printf("Informe o valor do Nó a ser excluído: \nR: ");
                scanf("%d", &dado);
                raiz = excluir(raiz, dado);
                printf("Nó excluído com sucesso!\n");
                break;
            case 5:
                printf("Informe o valor a ser pesquisado: \nR: ");
                scanf("%d", &dado);
                pesquisarNo(raiz, dado);
                break;
            case 0:
                printf("Fim do Programa!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }
    return 0;
}
