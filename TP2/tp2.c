/*
Hugo da Silva e Souza - 761211
Engenharia da computação 

*/

// Bicliotecas 
#include <stdio.h>
#include <stdlib.h>

#define MAX 100


void intercala(double v[], double p, double q, double r){
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

void mergeSort(double v[],double p, double r){
    int m;
    if(r - p > 1){
        m = (p + r)/2;
        mergeSort(v,p,m);
        mergeSort(v,m,r);
        intercala(v,p,m,r);
    }
}

void mergeSortI(double v[], int n){
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


// Programa principal
int main(int argc, char const *argv[]){
    
    char file_name[MAX];
    double **v, limiar;
    int n, k, i, j;
    FILE *entrada;

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
        for (j = 0; j < n; j++){
            fscanf(entrada, "%lf", &v[i][j]);
        } 
    }
    fclose(entrada);

    double linha[n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%.2lf ",v[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
           linha[j]=v[i][j];
        }
        mergeSortI(linha,n);
        for (int j = 0; j < n; j++){
           v[i][j]=linha[j];
        }
    }

// Aqui eu ja tenho a matriz ordenada

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%.2lf ",v[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
    int qtd_outliers = 0;

    for (int i = 0; i < n; i++){
       if(v[i][k+1] > limiar){
           qtd_outliers++;
       }
    }

    printf("%d",qtd_outliers);

    for (i = 0; i < n; i++)
        free(v[i]);
    free(v);

    return 0;
    
}
