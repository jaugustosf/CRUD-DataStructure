#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do nó da ABB usando typedef
typedef struct Node {
    int chave;
    struct Node* esquerda;
    struct Node* direita;
} Node;

Node* raiz = NULL;

// Função para criar um novo nó
Node* criarNo(int chave) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->chave = chave;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um nó na ABB
Node* inserir(Node* raiz, int chave) {
    // Se a árvore estiver vazia, retorna um novo nó
    if (raiz == NULL) {
        return criarNo(chave);
    }

    // Verifica se a chave já existe na árvore
    if (chave == raiz->chave) {
        printf("Chave duplicada: %d\n", chave);
        return raiz;
    }

    // Caso contrário, percorre a árvore recursivamente
    if (chave < raiz->chave) {
        raiz->esquerda = inserir(raiz->esquerda, chave);
    } else {
        raiz->direita = inserir(raiz->direita, chave);
    }

    // Retorna a raiz da árvore atualizada
    return raiz;
}


// Função para pesquisar um nó na ABB
Node* pesquisar(Node* raiz, int chave) {
    // Caso base: se a raiz for nula ou a chave for encontrada
    if (raiz == NULL || raiz->chave == chave) {
        return raiz;
    }

    // Se a chave for menor que a chave da raiz, pesquisar na subárvore esquerda
    if (chave < raiz->chave) {
        return pesquisar(raiz->esquerda, chave);
    }

    // Se a chave for maior que a chave da raiz, pesquisar na subárvore direita
    return pesquisar(raiz->direita, chave);
}

// Função para encontrar o nó com a chave mínima (nó mais à esquerda)
Node* encontrarMinimo(Node* no) {
    Node* atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Função para excluir um nó da ABB
Node* excluir(Node* raiz, int chave) {
    // Caso base: se a raiz for nula, retorna
    if (raiz == NULL) {
        return raiz;
    }

    // Percorre a árvore recursivamente para encontrar o nó a ser excluído
    if (chave < raiz->chave) {
        raiz->esquerda = excluir(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = excluir(raiz->direita, chave);
    } else {
        // Nó encontrado, realiza a exclusão

        // Caso 1: o nó não possui filhos ou possui apenas um filho
        if (raiz->esquerda == NULL) {
            Node* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Node* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Caso 2: o nó possui dois filhos
        Node* temp = encontrarMinimo(raiz->direita); // Encontra o sucessor in-order
        raiz->chave = temp->chave; // Copia a chave do sucessor in-order para o nó atual
        raiz->direita = excluir(raiz->direita, temp->chave); // Exclui o sucessor in-order
    }
    return raiz;
}

// Função para percorrer a árvore em ordem (in-order traversal)
void percorrerEmOrdem(Node* raiz) {
    if (raiz != NULL) {
        percorrerEmOrdem(raiz->esquerda);
        printf("%d ", raiz->chave);
        percorrerEmOrdem(raiz->direita);
    }
}

int main() {


    // Inserindo nós na ABB
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    // Percorrendo a árvore em ordem
    printf("Árvore em ordem: ");
    percorrerEmOrdem(raiz);
    printf("\n");

    // Pesquisando um nó
    Node* noPesquisado = pesquisar(raiz, 40);
    if (noPesquisado != NULL) {
        printf("Nó encontrado: %d\n", noPesquisado->chave);
    } else {
        printf("Nó não encontrado.\n");
    }

    // Excluindo um nó
    raiz = excluir(raiz, 30);

    // Percorrendo a árvore novamente após a exclusão
    printf("Árvore em ordem após exclusão: ");
    percorrerEmOrdem(raiz);
    printf("\n");

    return 0;
}
