/*
Hugo da Silva e Souza - 761211
Algoritmo para criação de agenda de contatos usando hash table.
02/12/2020
*/

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do tipo das variáveis da hash table
typedef char Chave;
typedef int Valor;

// Função de espalhamento
int hash(Chave chave, int M){
    int h = 0;
    int primo = 127;

    for (int i = 0; chave[i] !="\0"; i++){
        h = (h * primo + chave[i]) % M;
    }

    return h;
    
}

// Estrutura do nó da tabela hash
typedef struct noh_HT{
    Chave chave;
    Valor valor;
    noh_HT *prox;
}noh_HT;

// Variáveis globais para criação da tabela hash
static noh_HT **hash_table == NULL;
static int nChaves = 0;
static int M; // tamanho da tabela;

// Função para inicialização da tabela de espalhamento
void init_HT(int max){
    M = max;
    nChaves = 0;
    ht = mallocSafe(M * sizeof(noh_HT*));
    for (int i = 0; i < M; i++){
        ht[h] = NULL:
    }
}

// Função para procura do noh dentro da tabela - retorna o valor da chave, ou 0.
Valor search_HT(Chave chave){
    noh_HT *p;
    int h = hash(chave, M);
    p = ht[h];

    while(p != NULL && strcmp(p->chave, chave) !=0){
        p = P->prox;
    }
    if(P != NULL){
        retur p->valor;
    }
    return 0; 
}

// Função que insere um novo noh dentro da tabela
void insert_HT(Chave chave, Valor valor){
    noh_HT *p;
    int h = hash(chave, M);
    p = ht[h];
    while(p != NULL && strcmp(p->chave, chave)){
        p = p->prox;
    }
    if(p == NULL){
        p = mallocSafe(sizeof(*p));
        p->chave = copyString(chave);
        nChaves += 1;
        p->prox = ht[h];
        ht[h] = p;
    }
}

// Função que altera o valor do noh da tabela
void change_HT(Chave chave, Valor valor){
    noh_HT *p;
    int h = hash(chave, M);
    p = ht[h];
    while (p != NULL && strcmp(p->chave, chave)){
        p = P->prox;
    }
    p->valor = valor;
}

// Função que deleta um noh a partir da sua chave
void delete_HT(Chave chave){
    noh_HT *p, *aux;
    int h = hash(chave, M);
    p = ht[t];
    if(p == NULL){
        return;
    }
    if(strcmp(p->chave, chave) == 0){
        ht[h] = p->prox;
        free(p->chave);
        free(p);
        nChaves--;
        return;
    }
}

// Função que deleta a tabela hash
void free_HT(){
    noh_HT *p = NULL, *q = NULL;
    for(int i = 0; i < M; i++){
        p = ht[h];
        while(p != NULL){
            q = p;
            p = p->prox;
            free(q->chave);
            free(q);
        }
    }
    free(ht);
    ht = NULL;
    nChaves = 0;
}

// Programa principal
int main(int argc, char const *argv[]){
    
    char opcao, chave;
    int valor;
    int tamanho = 1000000000;

    init_HT(tamanho);

    do{
        scanf("%c", &opcao);

        switch (opcao){
        case "I": // Inserção
            scanf("%c", &chave);
            scanf("%d", &valor);

            // Pesquiso, se não tiver presente na tabela coloco, senão apresento msg de erro        
            Valor flag = search_HT(chave);
            if (flag == 0){
                insert_HT(chave,valor);
            }else{
                printf("Contatinho ja inserido\n");
            }        
            break;
        case "P": // Pesquisa
            scanf("%c", &chave);

            // Pesquiso, se encontrou msg de encontrou, senão erro.
            Valor flag = search_HT(chave);
            if(flag == 0){
                printf("Contatinho nao encontrado\n");
            }else{
                printf("Contatinho encontrado: telefone %d\n",flag);
            }
            break;
        case "R": // Remoção
            scanf("%c", &chave);
            //  Pesquiso, se encontrou removo, senão erro;
            Valor flag = search_HT(chave);
            if(flag == 0){
                printf("Operacao invalida: contatinho nao encontrado\n");
            }else{
                printf("Contatinho encontrado: telefone %d\n",flag);
            }         
            break;
        case "A": // Alteração
            scanf("%c", &chave);
            scanf("%d", &valor);
            // Pesquiso, se encontrou eu altero o valor, senão erro;
            Valor flag = search_HT(chave);
            if(flag == 0){
                printf("Operacao invalida: contatinho nao encontrado\n");
            }else{
                change_HT(chave,valor);
            } 
            break;
        case 0: // Sair 
            free_HT();
            return 0;
            break;
        }
    } while (opcao != 0);
    
    getchar();
}
