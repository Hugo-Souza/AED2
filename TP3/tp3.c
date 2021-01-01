/*
Hugo da Silva e Souza - 761211
Engenharia de Computação - 2018
Trabalho Prático 3 - AED2
*/

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct noh Noh;

struct noh{
    int rotulo;
    int custo;
    Noh *prox;
};

typedef struct grafo *Grafo;

struct grafo{
    Noh **A;
    int n; // Número de vértices
    int m; // Número de arestas/arcos
};

// Função de construção de um grafo G com n-1 vértices e nenhum arco
Grafo inicializaGrafo(int n){
    int i;
    Grafo G = malloc(sizeof *G);
    G->n = n;
    G->m = 0;
    G->A = malloc(n * sizeof(Noh *));
    for(i = 0; i < n; i++){
        G->A[i] = NULL;
    }
    return G;
}

// Procedimento de inserção de um arco v-w em um grafo G. Caso já exista este arco, não faz nada
void insereArcoGrafo(Grafo G, int v, int w, int c){
    Noh *p;
    for(p = G->A[v]; p != NULL; p = p->prox){
        if(p->rotulo == w){
            return;
        }
    }
    p = malloc(sizeof(Noh));
    p->rotulo = w;
    p->custo = c;
    p->prox = G->A[v];
    G->A[v] = p;
    G->m++;
}

void mostraGrafo(Grafo G){

}

void imprimeGrafo(Grafo G){

}

// Procedimento que cria arquivo de saída com todos os vértices adjacentes a cada vértice v
void imprimeArquivoGrafo(Grafo G, FILE *saida){
    int i; 
    Noh *p;
    fprintf(saida, "%d %d\n", G->n, G->m);
    for(i = 0; i < G->n; i++){
        for(p = G->A[i]; p != NULL; p = p->prox){
            fprintf(saida, "%2d ",p->rotulo);
        }
        fprintf(saida, "-1"); // Sentinela para marcar o fim da lista
        fprintf(saida, "\n");
    }
}

// Função de liberação de memória alocada de um grafo G, devolvendo NULL
Grafo liberaGrafo(Grafo G){
    int i;
    Noh *p;
    for(i = 0; i < G->n; i++){
        p = G->A[i];
        while(p != NULL){
            G->A[i] = p;
            p = p->prox;
            free(G->A[i]);
        }
        G->A[i] = NULL;
    }
    free(G->A);
    G->A = NULL;
    free(G);
    return NULL;
}

void buscaProfOrdTopoR(Grafo G, int v, int *visitado, int *ordTopo, int *protulo_atual){
    int w;
    Noh *p;
    visitado[v] = 1;
    p = G->A[v];
    while(p != NULL){
        w = p->rotulo;
        if(visitado[w] == 0){
            buscaProfOrdTopoR(G, w, visitado, ordTopo, protulo_atual);
        }
        p = p->prox;
    }
    ordTopo[*protulo_atual] = v;
    (*protulo_atual)--;
}

void ordenacaoTopologica(Grafo G, int *ordTopo){
    int v, rotulo_atual, *visitado;
    visitado = malloc(G->n * sizeof(int));
    for(v = 0; v < G->n; v++){
        visitado[v] = 0;
    }
    rotulo_atual = G->n;
    for(v = 0; v < G->n; v++){
        if(visitado[v] == 0){
            buscaProfOrdTopoR(G, v, visitado, ordTopo, &rotulo_atual);
        }
    }
    free(visitado);
}

void distanciasDAG(Grafo G, int origem, int *dist, int *pred){
    int i, *ordTopo;
    int v, w, custo;
    Noh *p;
    for(i = 0; i < G->n; i++){
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[origem] = 0;
    ordTopo = malloc((G->n + 1) * sizeof(int));
    ordenacaoTopologica(G, ordTopo);
    for(i = 0; i <= G->n; i++){
        v = ordTopo[i];
        p = G->A[v];
        while(p != NULL){
            w = p->rotulo;
            custo = p->custo;
            if(dist[w] > dist[v] + custo){
                dist[w] = dist[v] + custo;
                pred[w] = v;
            }
            p = p->prox;
        }
    }
    free(ordTopo);
}

void Dijkstra(Grafo G, int origem, int *dist, int *pred){
    int i, *R;
    int v, w, custo, tam_R, min_dist;
    Noh *p;
    for(i = 0; i < G->n; i++){
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[origem] = 0;
    R = malloc(G->n * sizeof(int));
    for(i = 0; i < G->n; i++){
        R[i] = 0;
    }
    tam_R = 0;
    while(tam_R < G->n){
        min_dist = INT_MAX;
        v = -1;
        for(i = 0; i <= G->n; i++){
            if(R[i] == 0 && dist[i] < min_dist){
                v = i;
                min_dist = dist[i];
            }
        }
        R[v] = 1;
        tam_R++;
        p = G->A[v];
        while(p != NULL){
            w = p->rotulo;
            custo = p->custo;
            if(R[w] == 0 && dist[w] > dist[v] + custo){
                dist[w] = dist[v] + custo;
                pred[w] = v;
            }
            p = p->prox;
        }
    }
    free(R);
}

int main(int argc, char const *argv[]){
    int vertices, arestas;
    int A, B, W; //A = , B = , W = peso
    Grafo G;

    
    G = inicializaGrafo(vertices);

    
    return 0;
}
