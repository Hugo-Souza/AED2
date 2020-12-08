#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main(int argc, char *argv[])
{
    char file_name[MAX];
    double **v, limiar;
    int n, k, i, j;
    FILE *entrada;

    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL)
    {
        printf("\nNão encontrei o arquivo!\n");
        exit(EXIT_FAILURE);
    }
    fscanf(entrada, "%d %d %lf", &n, &k, &limiar);
    v = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
    {
        v[i] = (double *)malloc(n * sizeof(double));
        for (j = 0; j < n; j++)
            fscanf(entrada, "%lf", &v[i][j]);
    }
    fclose(entrada);

    for (i = 0; i < n; i++)
        free(v[i]);
    free(v);

    return 0;
}
