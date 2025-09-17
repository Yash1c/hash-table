#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_BUCKETS 10  
#define MIN_CHAVE 10
#define MAX_CHAVE 25
#define MIN_VALOR 40
#define MAX_VALOR 100

typedef struct elemento {
    char *chave;
    char *valor;
    struct elemento *proximo;
} Elemento;

typedef struct {
    Elemento **buckets;
} TabelaHash;

// Função hash simples: soma dos códigos ASCII módulo número de buckets
unsigned int hash_simples(char *chave) {
    unsigned int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += (unsigned int)chave[i];
    }
    return soma % NUM_BUCKETS;
}

TabelaHash *criar_tabela_hash() {
    TabelaHash *tabela = malloc(sizeof(TabelaHash));
    tabela->buckets = calloc(NUM_BUCKETS, sizeof(Elemento *));
    return tabela;
}

bool validar_string(const char *str, int min, int max, const char *tipo) {
    int len = strlen(str);
    if (len < min || len > max) {
        printf("Erro: %s deve ter entre %d e %d caracteres (tem %d)\n", 
               tipo, min, max, len);
        return false;
    }
    return true;
}

bool inserir(TabelaHash *tabela, char *chave, char *valor) {
    if (!validar_string(chave, MIN_CHAVE, MAX_CHAVE, "Chave") ||
        !validar_string(valor, MIN_VALOR, MAX_VALOR, "Valor")) {
        return false;
    }
    
    unsigned int indice = hash_simples(chave);
    Elemento *novo = malloc(sizeof(Elemento));
    novo->chave = strdup(chave);
    novo->valor = strdup(valor);
    novo->proximo = tabela->buckets[indice];
    tabela->buckets[indice] = novo;
    
    printf("Inserido: Chave '%s' -> Valor '%s' no bucket %d\n", 
           chave, valor, indice);
    return true;
}

char *buscar(TabelaHash *tabela, char *chave) {
    if (!validar_string(chave, MIN_CHAVE, MAX_CHAVE, "Chave")) {
        return NULL;
    }
    
    unsigned int indice = hash_simples(chave);
    Elemento *atual = tabela->buckets[indice];
    
    while (atual) {
        if (strcmp(atual->chave, chave) == 0) {
            printf("Encontrado: Chave '%s' -> Valor '%s' no bucket %d\n", 
                   chave, atual->valor, indice);
            return atual->valor;
        }
        atual = atual->proximo;
    }
    
    printf("Chave '%s' não encontrada\n", chave);
    return NULL;
}

bool remover(TabelaHash *tabela, char *chave) {
    if (!validar_string(chave, MIN_CHAVE, MAX_CHAVE, "Chave")) {
        return false;
    }
    
    unsigned int indice = hash_simples(chave);
    Elemento *atual = tabela->buckets[indice];
    Elemento *anterior = NULL;
    
    while (atual) {
        if (strcmp(atual->chave, chave) == 0) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                tabela->buckets[indice] = atual->proximo;
            }
            
            printf("Removido: Chave '%s' -> Valor '%s' do bucket %d\n", 
                   chave, atual->valor, indice);
            
            free(atual->chave);
            free(atual->valor);
            free(atual);
            return true;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("Chave '%s' não encontrada para remoção\n", chave);
    return false;
}

void exibir_tabela(TabelaHash *tabela) {
    printf("\n=== CONTEÚDO DA TABELA HASH ===\n");
    for (int i = 0; i < NUM_BUCKETS; i++) {
        printf("Bucket %d: ", i);
        Elemento *atual = tabela->buckets[i];
        
        if (atual == NULL) {
            printf("Vazio\n");
            continue;
        }
        
        while (atual) {
            printf("[%s -> %s]", atual->chave, atual->valor);
            if (atual->proximo) printf(" -> ");
            atual = atual->proximo;
        }
        printf("\n");
    }
    printf("===============================\n\n");
}

void liberar_tabela_hash(TabelaHash *tabela) {
    for (int i = 0; i < NUM_BUCKETS; i++) {
        Elemento *atual = tabela->buckets[i];
        while (atual) {
            Elemento *temp = atual;
            atual = atual->proximo;
            free(temp->chave);
            free(temp->valor);
            free(temp);
        }
    }
    free(tabela->buckets);
    free(tabela);
}

int main() {
    TabelaHash *tabela = criar_tabela_hash();
    int opcao;
    char chave[200], valor[300];

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Inserir\n");
        printf("2 - Buscar\n");
        printf("3 - Remover\n");
        printf("4 - Exibir tabela\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer do enter

        switch (opcao) {
            case 1:
                printf("Digite a chave (%d-%d caracteres): ", MIN_CHAVE, MAX_CHAVE);
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = 0;

                printf("Digite o valor (%d-%d caracteres): ", MIN_VALOR, MAX_VALOR);
                fgets(valor, sizeof(valor), stdin);
                valor[strcspn(valor, "\n")] = 0;

                inserir(tabela, chave, valor);
                break;

            case 2:
                printf("Digite a chave para buscar: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = 0;
                buscar(tabela, chave);
                break;

            case 3:
                printf("Digite a chave para remover: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = 0;
                remover(tabela, chave);
                break;

            case 4:
                exibir_tabela(tabela);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    liberar_tabela_hash(tabela);
    return 0;
}
