/*
Hugo da Silva e Souza - 761211
Engenharia da computação 

*/

// Bibliotecas 
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Procedimento de intercalar vetor utilizado no método de mergeSort
void intercala(double v[], int p, int q, int r){
    int i, j , k, tam;
    i = p;
    j = q;
    k = 0;
    tam = r - p;
    int P = p;

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
        v[P+k] = w[k];
    }
    free(w);
}

// Procedimento de ordenação - mergeSorte iterativo
void mergeSortI(double *v, int n){
    int b = 1;
    while(b < n){
        int p = 0;
        while(p + b < n){
            int r = p + 2 * b;
            if (r > n){
                r = n;
            }
            intercala(v,p,p+b,r);
            p = p + 2* b;
        }
        b = b*2;
    }
}

void ordenaMatriz(double **v, int n){
   
        
        for (int j = 0; j < n; j++){
           mergeSortI(v[j],n);
        }
}

int verificaOutliers(double **v, int n, int k, double limiar){
    int qtd_outliers = 0;
    for (int i = 0; i < n; i++){
       if(v[i][k+1] > limiar){
           qtd_outliers++;
       }
    }
    return qtd_outliers;
}

void obtemMatriz(char file_name[MAX], double **v, int n, int k, double limiar){
    FILE *entrada;
    entrada = fopen(file_name, "r");
    if (entrada == NULL){
        printf("\nNão encontrei o arquivo!\n");
        exit(EXIT_FAILURE);
    }
    fscanf(entrada, "%d %d %lf", &n, &k, &limiar);
    v = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++){
        v[i] = (double *)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++){
            fscanf(entrada, "%lf", &v[i][j]);
        } 
    }
    fclose(entrada);
}

void liberaMatriz(double **v, int n){
    for (int i = 0; i < n; i++)
        free(v[i]);
    free(v);
}


// Programa principal
int main(int argc, char const *argv[]){
    
    char file_name[MAX];
    double **v, limiar;
    int n, k;
    

    scanf("%s", file_name);
    obtemMatriz(file_name,v,n,k,limiar);
    
    
    ordenaMatriz(v,n);

    printf("%d",verificaOutliers(v,n,k,limiar));

    liberaMatriz(v,n);

    return 0;
    
}
