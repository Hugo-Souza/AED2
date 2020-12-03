#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char Chave[11];
typedef int Valor;
typedef struct celTS CelTS;

void *mallocSafe(unsigned nbytes){
    void *p;
    p = malloc(nbytes);
    if(p == NULL){
        exit(EXIT_FAILURE);
    }
    return p;
}

int hash(Chave chave, int M){
    int i, h = 0;
    int primo = 577;
    for(i = 0; chave[i] != '\0'; i++){
        h = (h * primo + chave[i]) % M;
    }
    return abs(h);
}

struct celTS{
    Chave chave;
    Valor valor;
    CelTS *prox;
};

static CelTS **tab = NULL;
static int nChaves = 0;
static int M;

void stInit(int max){
    int h;
    M = max;
    nChaves = 0;
    tab = mallocSafe(M * sizeof(CelTS *));
    for(h = 0; h < M; h++){
        tab[h] = NULL;
    }
}

Valor stSearch(Chave chave){
    CelTS *p;
    int h = hash(chave, M);
    p = tab[h];
    while(p != NULL && strcmp(p->chave, chave) != 0){
        p = p->prox;
    }
    if(p != NULL){
        return p->valor;
    }
    return 0;
}

void stInsert(Chave chave, Valor valor){
    CelTS *p;
    int h = hash(chave, M);
    p = tab[h];
    while(p != NULL && strcmp(p->chave, chave)){
        p = p->prox;
    }
    if(p == NULL){
        p = mallocSafe(sizeof(*p));
        strcpy(p->chave,chave);
        p->valor = valor;
        nChaves +=1;
        p->prox = tab[h];
        tab[h] = p;
    }
}

void stChange(Chave chave, Valor valor){
    CelTS *p;
    int h = hash(chave, M);
    p = tab[h];
    while(p != NULL && strcmp(p->chave, chave)){
        p = p->prox;
    }
    p->valor = valor;
}

void stDelete(Chave chave){
    CelTS *p;
    int h = hash(chave, M);
    p = tab[h];
    if(p == NULL){
        return;
    }
    if(strcmp(p->chave, chave) == 0){
        tab[h] = p->prox;
        free(p->chave);
        free(p);
        nChaves--;
        return;
    }
}

void stFree(){
    CelTS *p = NULL, *q = NULL;
    int h;
    for(h = 0; h < M; h++){
        p = tab[h];
        while(p != NULL){
            q = p;
            p = p->prox;
            free(q->chave);
            free(q);
        }
    }
    free(tab);
    tab = NULL;
    nChaves = 0;
}


int main(int argc, char const *argv[]){
    int tamanho = 100000000;
    char op[11], nome[11];
    int num;
    stInit(tamanho);
       
    do{
        scanf("%s",op);
        
        
        if(strcmp(op,"I")==0){

            scanf("%s",nome);
            scanf("%d",&num);
            

            if(stSearch(nome)==0){
                stInsert(nome,num);
            }else{
                printf("Contatinho ja inserido\n");
            }
            
        }else if(strcmp(op,"P")==0){

            scanf("%s",nome);
            
            if(stSearch(nome)==0){
                printf("Contatinho nao encontrado\n");
            }else{
                printf("Contatinho encontrado: telefone %d\n",stSearch(nome));
            }
            
        }else if(strcmp(op,"R")==0){
            scanf("%s",nome);
            
            if(stSearch(nome)==0){
                printf("Operacao invalida: contatinho nao encontrado\n");
            }else{
                stDelete(nome);
            }

        }else if(strcmp(op,"A")==0){

            scanf("%s",nome);
            scanf("%d",&num);
            
            if(stSearch(nome)==0){
                printf("Operacao invalida: contatinho nao encontrado\n");
            }else{
                stChange(nome,num);
            }

        }else{
            stFree();
        }  
    } while (strcmp(op,"0") !=0 );
}

