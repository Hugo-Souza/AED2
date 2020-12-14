/*
Hugo da Silva e Souza - 761211
Engenharia de Computação -18
Trabalho Prático 2 - AED2
*/

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>

// Definição do tamanho da string
#define MAX 100

// Procedimento de intecalar vetor utilizado no método de ordenação MergeSort
void intercala(double v[], int p, int q, int r){
    int i, j, k , tam;
    i = p;
    j = q;
    k = 0;
    tam = r - p;
    
    double *w = malloc(tam * sizeof(double));
    while(i < q && j < r){
        if(v[i] <= v[j]){
            w[k++] = v[i++];
        }else{
            w[k++] = v[j++];
        }
    }
    while(i < q){
        w[k++] = v[i++];
    }
    while(j < r){
        w[k++] = v[j++];
    }
    for(k = 0; k < tam; k++){
        v[p+k] = w[k];
    }
    free(w);
}

// Procedimento de ordenação - MergeSort Iterativo 
void mergeSort(double *v, int n){
    int b = 1;
    while(b < n){
        int p = 0;
        while(p + b < n){
            int r = p + 2*b;
            if(r > n){
                r = n;
            }
            intercala(v,p,p+b,r); 
            p = p + 2*b;
        }
        b = 2*b;
    }
}

// Procedimento de ordenação de matriz - Utiliza o MergeSort
void ordenaMatriz(double **v, int n){
    int i;
    // Ordena cada linha da matriz
    for(i = 0; i < n; i++){
        mergeSort(v[i],n);
    }
}

// Função de verificação de outliers, segundo a definição descrita no PDF de intrução do TP2
int verificaOutliers(double **v, int n, int k, double limiar){
    int i, qtdOutliers = 0;
    for(i = 0; i < n; i++){
        if(v[i][k+1] > limiar){
            qtdOutliers++;
        }
    }
    return qtdOutliers;
}

// Programa principal
int main(int argc, char *argv[])
{
    // Variáveis utilizadas para obter, armazenar e liberar a matriz de dados
    char file_name[MAX];
    double **v, limiar;
    int n, k, i, j;
    FILE *entrada;

    // Obtendo a matriz de dados, a partir do nome do arquivo digitado
    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL){
        printf("\nNão encontrei o arquivo!\n");
        exit(EXIT_FAILURE);
    }
    fscanf(entrada, "%d %d %lf", &n, &k, &limiar);
    v = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++){
        v[i] = (double *)malloc(n * sizeof(double));
        for (j = 0; j < n; j++)
            fscanf(entrada, "%lf", &v[i][j]);
    }
    fclose(entrada);

    // Ordenando a matriz de dados
    ordenaMatriz(v,n);

    // Verificando e mostrando a quantidade de outliers presentes na matriz de dados
    int outliers = verificaOutliers(v,n,k,limiar);
    printf("%d",outliers);

    // Librando o espaço alocado para armazenar a matriz de dados
    for (i = 0; i < n; i++)
        free(v[i]);
    free(v);

    return 0;
}
