#ifndef GRAFO_H
#define GRAFO_H

#define MAX_VERTICES 100

typedef struct adj {
    int dest;
    struct adj *prox;
} Adj;

typedef struct vertice {
    int id;
    int x, y;
    char freq;
    Adj *lista;
} Vertice;

typedef struct grafo {
    int n_vertices;
    Vertice vertices[MAX_VERTICES];
} Grafo;


void inicializaGrafo(Grafo *g);
int adicionaVertice(Grafo *g, int x, int y, char freq);
void adicionaAresta(Grafo *g, int orig, int dest);
void imprimeGrafo(Grafo *g);
void dfs(Grafo *g, int start_id);
void bfs(Grafo *g, int start_id);
void listarCaminhos(Grafo *g, int origem, int destino);

#endif
