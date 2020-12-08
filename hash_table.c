/*
Hugo da Silva e Souza - 761211
Engenharia da Computação 018
Trabalho Prático 1 - AED2
*/

// Bibliotecas 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *Chave;
typedef int Valor;
typedef struct celTS CelTS;

// Função para verificação do malloc, deixando mais segura a sua utilização
void *mallocSafe(unsigned nbytes){
    void *p;
    p = malloc(nbytes);
    if(p == NULL){
        exit(EXIT_FAILURE);
    }
    return p;
}

// Função para fazer a cópia de uma string, caractere a caractere
char *copyString(Chave chave){
    int i = 0;
    while (chave[i] != '\0'){
        i += 1;
    }
    char *palavra = mallocSafe(sizeof(char) * i + 1);
    i = 0;
    while (chave[i] != '\0'){
        palavra[i] = chave[i];
        i += 1;
    }
    return palavra;
}

// Função para geração do valor hash(espalhamento)
int hash(Chave chave, int M){
    int i, h = 0;
    int primo = 577;
    for(i = 0; chave[i] != '\0'; i++){
        h = (h * primo + chave[i]) % M;
    }
    return abs(h);
}

// Estrutura da célula(noh) que será utilizado na tabela
struct celTS{
    Chave chave;
    Valor valor;
    CelTS *prox;
};

// Variáveis globais para a criação da tabela hash
static CelTS **tab = NULL;
static int nChaves = 0;
static int M; // Tamanho total da tabela

// Procedimento que inicia a tabela hash, alocando o tamanho máximo de célular que ela pode ter
void stInit(int max){
    int h;
    M = max;
    nChaves = 0;
    tab = mallocSafe(M * sizeof(CelTS *));
    for(h = 0; h < M; h++){
        tab[h] = NULL;
    }
}

// Função de pesquisa de célula a partir da sua chave, retornando o valor dela ou 0 caso não seja encontrada a chave
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

// Procedimento de inserção de uma nova célula na tabela
void stInsert(Chave chave, Valor valor){
    CelTS *p;
    int h = hash(chave, M);
    p = tab[h];
    while(p != NULL && strcmp(p->chave, chave)){
        p = p->prox;
    }
    if(p == NULL){
        p = mallocSafe(sizeof(*p));
        p->chave = copyString(chave);
        p->valor = valor;
        nChaves +=1;
        p->prox = tab[h];
        tab[h] = p;
    }
}

// Procedimento de alteração do valor de uma chave
void stChange(Chave chave, Valor valor){
    CelTS *p;
    int h = hash(chave, M);
    p = tab[h];
    while(p != NULL && strcmp(p->chave, chave)){
        p = p->prox;
    }
    p->valor = valor;
}

// Procedimento de deletar uma célula da tabela, a partir da chave da mesma
void stDelete(Chave chave){
    CelTS *p, *aux;
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
    while(p->prox != NULL && strcmp((p->prox)->chave, chave) != 0){
        p = p->prox;
    }
    if(p->prox != NULL){
        aux = p->prox;
        p->prox = aux->prox;
        free(aux->chave);
        free(aux);
        nChaves--;
        return;
    }
}

// Procedimento de excluir(liberar) a tabela hash interia
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
    free(tab);
    nChaves = 0;
}

// Programa principal - Tabela hash como agenda de contatos
int main(int argc, char const *argv[]){
    int tamanho = 1000000000; // Tamanho da tabela hash para armazenar os contatinhos 
    char op[22]; // Vetor de char para armazenar a operação que será realizada na agenda de contatinhos
    char nome[22]; // Vetor de char para armazenar o nome(chave) do contatinho obtido da entrada de dados
    int num; // Variável para armazenar o número(valor) do contatinho obtido da entrada de dados
    stInit(tamanho); // Inicializando a agenda(tabela hash) com o tamanho desejado
       
    // Laço de repetição para obter as operações e realizá-las
    do{
        scanf("%s", op); // Obtendo a operação que será realizada na agenda
        
        // Operação de inserção de contatos - Verifica a presença na agenda, caso não esteja presente é inserido o novo
        // contato, senão é apresentado mensagem de erro
        if(strcmp(op, "I") == 0){
            scanf("%s", nome);
            scanf("%d", &num);
            if(stSearch(nome) ==0){
                stInsert(nome, num);
            }else{
                printf("Contatinho ja inserido\r\n");
            }
        // Operação de pesquisa de contato - Verifica a presença do mesmo na agenda, caso esteja presente é apresentado
        // uma mensagem informando o seu telefone, senão é apresentado uma mensagem de erro   
        }else if(strcmp(op, "P") == 0){
            scanf("%s", nome);
            if(stSearch(nome) == 0){
                printf("Contatinho nao encontrado\r\n");
            }else{
                printf("Contatinho encontrado: telefone %d\r\n", stSearch(nome));
            }
        // Operação de remoção de contato - Verifica a presença do mesmo na agenda, caso esteja presente é removido da
        // agenda, senão é apresentado uma mensagem de erro   
        }else if(strcmp(op, "R") == 0){
            scanf("%s", nome);
            if(stSearch(nome) == 0){
                printf("Operacao invalida: contatinho nao encontrado\r\n");
            }else{
                stDelete(nome);
            }
        // Operação de alteração de contato - Verifica a presença do mesmo na agenda, caso esteja presente é alterado 
        // o valor do seu número, senão é apresentado uma mensagem de erro
        }else if(strcmp(op, "A") == 0){
            scanf("%s", nome);
            scanf("%d", &num);
            if(stSearch(nome) == 0){
                printf("Operacao invalida: contatinho nao encontrado\r\n");
            }else{
                stChange(nome, num);
            }
        // Operação de deletar a tabela - É liberado todos os contatos e seus respectivos espaços alocados
        }else{
            stFree();
        }  
    } while (strcmp(op, "0") != 0);
}

