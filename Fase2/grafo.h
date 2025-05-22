/**
 * @file grafo.h
 * @author Daniel Vilaça (a16939@alunos.ipca.pt)
 * @brief
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdbool.h>

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
bool adicionaAresta(Grafo *g, int orig, int dest);
void imprimeGrafo(Grafo *g);
bool dfs(Grafo *g, int start_id);
bool bfs(Grafo *g, int start_id);
bool listarCaminhos(Grafo *g, int origem, int destino);
void listarIntersecoes(Grafo *g, char freq1, char freq2);

#endif
