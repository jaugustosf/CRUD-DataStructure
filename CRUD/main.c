#include <stdio.h>
#include <stdlib.h>
#include <string.h>

                                                            // Definindo a estrutura do nó da ABB usando typedef
typedef struct manga{
    int  key;                                               // Chave de identificação.
    char name_manga[100];                                        // Título do mangá.
    char demography[10];                                        // Se a demografia é Shounem(Até 16) ou Seinen(Apartir de 17+).
    unsigned int numpag;                                    // Número de páginas || Unsigned é para que o número de páginas seja apenas número positivos.
    char publisher[10];                                         // Editora que publima o mangá no país em questão.
    float price;                                            // Preço do mangá em questão.

    struct manga *right;
    struct manga *left;
}Manga;

Manga *source = NULL;                                       //Source é a raiz da árvore.

Manga *Criar_manga(int key, char *name_manga, char *demography, unsigned int numpag, char *publisher, float price){                                // Função para criar um novo nó
    Manga* Novo_manga = malloc(sizeof(Manga));              // Node* novoNo = (Node*)malloc(sizeof(Node));
    
    Novo_manga -> key = key;
    strcpy(Novo_manga -> name_manga, name_manga);
    strcpy(Novo_manga -> demography, demography);
    Novo_manga -> numpag = numpag;
    strcpy(Novo_manga -> publisher, publisher);
    Novo_manga -> price = price;

    Novo_manga -> left = NULL;
    Novo_manga -> right = NULL;

    return Novo_manga;
}

Manga* Search(Manga* source, int key) {
    // Caso base: se a raiz for nula ou a key for encontrada
    if (source == NULL){
        return NULL;
    }
    if(source->key == key){
        return source;
    }
    // Se a key for menor que a key da raiz, pesquisa na subárvore esquerda
    if (key < source->key) {
        return Search(source -> left, key);
    }

    // Se a key for maior que a key da raiz, pesquisa na subárvore direita
    return Search(source->right, key);
}

Manga* Add(Manga* source, int key, char *name_manga, char *demography, unsigned int numpag, char *publisher, float price) {
    // Se a árvore estiver vazia, retorna um novo nó.
    if (source == NULL) {
        return Criar_manga(key, name_manga, demography, numpag, publisher, price);
    }
    // Verifica se já existe um manga com o mesmo ID.
    if (key == source -> key) {
        printf("A chave %d ja existe.\n", key);
        return source;
    }

    // Percorre a árvore recursivamente.
    if (key < source->key) {
        source->left = Add(source->left, key, name_manga, demography, numpag, publisher, price);
    } else if (key > source->key) {
        source->right = Add(source->right, key, name_manga, demography, numpag, publisher, price);
    }

    // Retorna a raiz da árvore atualizada.
    return source;
}

void print(Manga *source){
    if(source != NULL){
        printf("ID: %d | Titulo - %s | Demografia - %s | Paginas - %d | Editora - %s | Preco - RS %.2f\n",source->key, source->name_manga, source->demography, source->numpag, source->publisher, source->price);
        print(source->left);
        print(source->right);
    }
}


int main(){
    







    /*
    source = Add(source, 6, "Real", "Seinen", 200, "Panini", 34.90);
    source = Add(source, 9, "One Piece", "Shounen", 100, "Panini", 9.99);
    source = Add(source, 7, "Naruto", "Shounen", 200, "Panini", 8.99);
    source = Add(source, 3, "Berserk", "Seinen", 300, "Panini", 12.99);
    source = Add(source, 4, "Attack on Titan", "Shounen", 150, "Panini", 10.99);
    source = Add(source, 5, "Death Note", "Shounen", 120, "New Pop", 7.99);
    */
    print(source);
    return 0;
}