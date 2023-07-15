#include <stdio.h>
#include <stdlib.h>
#include <string.h>
                                                        
typedef struct manga{                                       // Definindo a estrutura do nó.
    int  key;                                               // Chave de identificação.
    char name_manga[100];                                   // Título do mangá.
    char demography[10];                                    // Se a demografia é Shounem(Até 16) ou Seinen(Apartir de 17+).
    unsigned int numpag;                                    // Número de páginas || Unsigned é para que o número de páginas seja apenas número positivos.
    char publisher[10];                                     // Editora que publima o mangá no país em questão.
    float price;                                            // Preço do mangá em questão.

    struct manga *right;
    struct manga *left;
}Manga;

Manga *source = NULL;                                       // Source é a raiz da árvore.
                                                            // Função para criar um novo nó
Manga *Criar_manga(int key, char *name_manga, char *demography, unsigned int numpag, char *publisher, float price){
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
    if (source == NULL || source->key == key){              // Caso base: se a raiz for nula ou a key for encontrada.
        return source;
    }

    if (key < source->key) {                                // Se a key for menor que a key da raiz, pesquisa na subárvore esquerda.
        return Search(source -> left, key);
    }
                                                            
    return Search(source->right, key);                      // Se a key for maior que a key da raiz, pesquisa na subárvore direita.
}

Manga* Add(Manga* source, int key, char *name_manga, char *demography, unsigned int numpag, char *publisher, float price) {                                                            
    if (source == NULL) {                                   // Se a árvore estiver vazia, retorna um novo nó.
        return Criar_manga(key, name_manga, demography, numpag, publisher, price);
    }                                                            
    if (key == source -> key) {                             // Verifica se já existe um manga com o mesmo ID.
        printf("A chave %d ja existe.\n", key);
        return source;
    }

    if (key < source->key) {                                // Percorre a árvore recursivamente.
        source->left = Add(source->left, key, name_manga, demography, numpag, publisher, price);
    } else if (key > source->key) {
        source->right = Add(source->right, key, name_manga, demography, numpag, publisher, price);
    }
    return source;                                          // Retorna a raiz da árvore atualizada.
}

Manga *encontrarMinimo(Manga *source) {
    if (source == NULL) {
        return NULL;
    } else if (source -> left != NULL) {
        return encontrarMinimo(source -> left);
    }
    return source;
}

Manga *Remove(Manga *source, int key) {
    if (source == NULL) {
        return source;
    }

    if (key < source->key) {
        source->left = Remove(source->left, key);
    } else if (key > source->key) {
        source->right = Remove(source->right, key);
    } else {                                                                    
        if (source->left == NULL && source->right == NULL) {        // Caso 1: Nó folha (não tem filhos)
            free(source);
            source = NULL;
        }else if (source->left == NULL) {                           // Caso 2: Nó com um filho
            Manga *aux = source;
            source = source->right;
            free(aux);
        } else if (source->right == NULL) {
            Manga *aux = source;
            source = source->left;
            free(aux);
        }else{                                                      // Caso 3: Nó com dois filhos
            Manga *aux = encontrarMinimo(source->right);
            source->key = aux->key;
            source->right = Remove(source->right, aux->key);
        }
    }
    return source;
}

void Alterar_dados(Manga* source, int key) {
    Manga* result_1 = Search(source, key);

    if (result_1 != NULL) {
        printf("\nManga encontrado. Selecione o dado que deseja alterar:\n");
        printf("1 - Titulo\n");
        printf("2 - Demografia\n");
        printf("3 - Numero de paginas\n");
        printf("4 - Editora\n");
        printf("5 - Preco\n");
        printf("Escolha uma opcao:");

        int option;
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Novo titulo: ");
                scanf(" %99[^\n]", result_1->name_manga);
                break;
            case 2:
                printf("Nova demografia: ");
                scanf(" %9[^\n]", result_1->demography);
                break;
            case 3:
                printf("Novo numero de paginas: ");
                scanf("%u", &result_1->numpag);
                break;
            case 4:
                printf("Nova editora: ");
                scanf(" %9[^\n]", result_1->publisher);
                break;
            case 5:
                printf("Novo preco: ");
                scanf("%f", &result_1->price);
                break;
            default:
                printf("Opcao invalida.\n");
                return;
        }
        printf("Dados do manga alterados com sucesso.\n");
    } else {
        printf("Manga com a chave %d nao encontrado.\n", key);
    }
}

void Printall(Manga *source){                                   // Usando o metodo Pre-Order.
    if(source != NULL){
        printf("ID: %d | Titulo - %s | Demografia - %s | Paginas - %u | Editora - %s | Preco - RS %.2f\n",source->key, source->name_manga, source->demography, source->numpag, source->publisher, source->price);
        Printall(source->left);                                 // Percorre até o nó mais profundo a esquerda da subarvore.
        Printall(source->right);                                // Percorre até o nó mais profundo a direita da subarvore.
    }
}

int main(){
    int option;                                                 // Grava a opção selecionada pelo usuário.

    int key;
    char name_manga[100];
    char demography[10];
    unsigned int numpag;
    char publisher[10];
    float price;
                                                                // Para não precisar cadastrar todas manualmente coloquei algumas previamente.                                                             
    source = Add(source, 58, "Real", "Seinen", 200, "Panini", 34.90);
    source = Add(source, 1, "One Piece", "Shounen", 100, "Panini", 9.99);
    source = Add(source, 12, "Naruto", "Shounen", 200, "Panini", 8.99);
    source = Add(source, 93, "Berserk", "Seinen", 300, "Panini", 12.99);
    source = Add(source, 25, "Attack on Titan", "Shounen", 150, "Panini", 10.99);
    source = Add(source, 71, "Death Note", "Shounen", 120, "New Pop", 7.99);
    source = Add(source, 37, "My Hero Academia", "Shounen", 180, "JBC", 14.99);
    source = Add(source, 84, "Tokyo Ghoul", "Seinen", 100, "New Pop", 11.99);
    source = Add(source, 66, "Fullmetal Alchemist", "Shounen", 250, "JBC", 16.99);
    source = Add(source, 45, "Hunter x Hunter", "Shounen", 160, "Panini", 13.99);
    source = Add(source, 79, "Haikyu!!", "Shounen", 80, "New Pop", 6.99);
    source = Add(source, 18, "One Punch Man", "Seinen", 90, "JBC", 9.99);
    source = Add(source, 63, "Demon Slayer", "Shounen", 130, "Panini", 11.99);
    source = Add(source, 30, "JoJo's Bizarre Adventure", "Seinen", 200, "JBC", 18.99);
    source = Add(source, 52, "Fairy Tail", "Shounen", 120, "Panini", 10.99);

    while(option != 0){
        printf("\n============MANGASYSTEM============\n");
        printf(" 1 - Cadastrar Manga\n");
        printf(" 2 - Excluir Manga\n");
        printf(" 3 - Alterar dados cadastrados\n");
        printf(" 4 - Buscar Manga\n");
        printf(" 5 - Mostrar tudo\n");
        printf(" 0 - Sair\n");
        printf("===================================\n");
        printf("Escolha uma opcao:");

        scanf(" %d", &option);

        switch (option) {
            case 1:                                                    // Opção para adicionar um manga                    
                printf("\nDigite os detalhes do Manga:\n");
                printf("Chave: ");
                scanf("%d", &key);
                printf("Nome: ");
                scanf(" %99[^\n]", name_manga);
                printf("Demografia: ");
                scanf(" %9[^\n]", demography);
                printf("Numero de paginas: ");
                scanf("%u", &numpag);
                printf("Editora: ");
                scanf(" %9[^\n]", publisher);
                printf("Preco: ");
                scanf("%f", &price);

                source = Add(source, key, name_manga, demography, numpag, publisher, price);
                break;
            
            case 2:                                                    // Opção para excluir um manga
                printf("\nDigite o ID do manga que deseja remover:");
                scanf("%d", &key);
                source = Remove(source, key);  
                
                break;

            case 3:  // Opção para alterar dados cadastrados
                printf("\nDigite o ID do manga que deseja alterar:");
                scanf("%d", &key);
                Alterar_dados(source, key);
                break;


            case 4:                                                    // Opção para buscar um manga                                                        
                printf("\nDigite o ID que deseja buscar:");
                scanf("%d", &key);
                Manga *result = Search(source, key);                        
                if (result != NULL) {
                    printf("\nManga encontrado:\n");
                    printf("Titulo: %s | Demografia: %s | Paginas: %u | Editora: %s | Preco: R$ %.2f\n",result->name_manga, result->demography, 
                                                                                                                 result->numpag, result->publisher, result->price);
                } else {printf("Manga com a chave %d nao encontrado.\n\n", key);}
                break;

            case 5:                                                    // Opção para mostrar todos os mangás cadastrados.
                printf("\nTodos os mangas cadastrados:\n");  
                Printall(source);                                      // Chama a função Print que mostra todos os nós da arvore em forma Pre-Order.
                break;

            case 0:
                printf("\nSaindo.\n");
                break;

            default:
                printf("\nOpcao invalida, tente outra.\n");
                break;
        }
    }
    return 0;
}