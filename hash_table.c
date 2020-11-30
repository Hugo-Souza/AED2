/*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char Chave;
typedef int Valor;

// Funcção de espalhamento
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

static noh_HT **hash_table == NULL;
static int nChaves = 0;
static int M; // tamanho da tabela;

void init_HT(int max){
    M = max;
    nChaves = 0;
    ht = mallocSafe(M * sizeof(noh_HT*));
    for (int i = 0; i < M; i++){
        ht[h] = NULL:
    }
}

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