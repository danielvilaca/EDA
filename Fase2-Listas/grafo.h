#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>


typedef struct Adj Adj;
typedef struct Vertice Vertice;


struct Adj {
    Vertice *dest;
    Adj     *prox;
};


struct Vertice {
    int      id;
    int      x, y;
    char     freq;
    Adj     *lista;
    Vertice *next;

    bool     visited;
};


typedef struct {
    Vertice *head;
    int      n_vertices;
} Grafo;


void    inicializaGrafo(Grafo *g);
int     adicionaVertice(Grafo *g, int x, int y, char freq);
bool    adicionaAresta(Grafo *g, int orig_id, int dest_id);
void    imprimeGrafo(Grafo *g);
bool    dfs(Grafo *g, int start_id);
bool    bfs(Grafo *g, int start_id);
bool    listarCaminhos(Grafo *g, int origem, int destino);
void    listarIntersecoes(Grafo *g, char freq1, char freq2);
bool    removerVertice(Grafo *g, int id);

#endif
