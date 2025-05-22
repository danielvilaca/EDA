/**
 * @file grafo.c
 * @author Daniel Vilaça (a16939@alunos.ipca.pt)
 * @brief
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grafo.h"


/// @brief Inicializa o grafo (número de vértices) a 0
/// @param g
void inicializaGrafo(Grafo *g) {
    g->n_vertices = 0;
}

/// @brief Adiciona uma nova antena (vértice) ao grafo.
/// @param g Apontador para o grafo
/// @param x Coordenada x da antena
/// @param y Coordenada y da antena
/// @param freq Frequência de ressonância da antena
/// @return ID atribuído ao novo vértice ou -1 se o grafo estiver cheio
int adicionaVertice(Grafo *g, int x, int y, char freq) {
    if (g->n_vertices >= MAX_VERTICES) return -1;
    int id = g->n_vertices;
    g->vertices[id].id = id;
    g->vertices[id].x = x;
    g->vertices[id].y = y;
    g->vertices[id].freq = freq;
    g->vertices[id].lista = NULL;
    g->n_vertices++;
    return id;
}

/// @brief Adiciona uma aresta bidirecional entre dois vértices com a mesma frequência
/// @param g Apontador para o grafo
/// @param orig Vértice de origem
/// @param dest Vértice de destino
bool adicionaAresta(Grafo *g, int orig, int dest) {
    if (orig < 0 || dest < 0 || orig >= g->n_vertices || dest >= g->n_vertices)
        return false;
    if (g->vertices[orig].freq != g->vertices[dest].freq)
        return false;

    Adj *nova = malloc(sizeof(Adj));
    if (!nova) return false;

    nova->dest = dest;
    nova->prox = g->vertices[orig].lista;
    g->vertices[orig].lista = nova;

    Adj *nova2 = malloc(sizeof(Adj));
    if (!nova2) return false;

    nova2->dest = orig;
    nova2->prox = g->vertices[dest].lista;
    g->vertices[dest].lista = nova2;

    return true;
}


/// @brief Imprime todos os vértices do grafo e as suas ligações (arestas)
/// @param g Apontador
void imprimeGrafo(Grafo *g) {
    for (int i = 0; i < g->n_vertices; i++) {
        printf("Antena %d [%c] em (%d,%d) -> ", g->vertices[i].id, g->vertices[i].freq, g->vertices[i].x, g->vertices[i].y);
        Adj *aux = g->vertices[i].lista;
        while (aux != NULL) {
            printf("%d ", aux->dest);
            aux = aux->prox;
        }
        printf("\n");
    }
}

/// @brief Função auxiliar recursiva para DFS. Visita os vértices ligados ao atual
/// @param g Apontador
/// @param id Vértice atual
/// @param visitado Array de vértices já visitados
void dfs_visit(Grafo *g, int id, int *visitado) {
    visitado[id] = 1;
    printf("Visitado DFS: Antena %d [%c] em (%d,%d)\n",
           g->vertices[id].id,
           g->vertices[id].freq,
           g->vertices[id].x,
           g->vertices[id].y);

    Adj *adj = g->vertices[id].lista;
    while (adj != NULL) {
        if (!visitado[adj->dest]) {
            dfs_visit(g, adj->dest, visitado);
        }
        adj = adj->prox;
    }
}

/// @brief Inicia a procura em profundidade (DFS) a partir de uma antena
/// @param g Apontador
/// @param start_id Antena de partida
bool dfs(Grafo *g, int start_id) {
    if (start_id < 0 || start_id >= g->n_vertices) {
        printf("ID invalido.\n");
        return false;
    }

    int visitado[MAX_VERTICES] = {0};
    printf("DFS a partir da antena %d\n", start_id);
    dfs_visit(g, start_id, visitado);
    return true;
}


/// @brief Inicia a procura em largura (BFS) a partir de uma antena
/// @param g Apontador
/// @param start_id Antena de partida
bool bfs(Grafo *g, int start_id) {
    if (start_id < 0 || start_id >= g->n_vertices) {
        printf("ID invalido.\n");
        return false;
    }

    int visitado[MAX_VERTICES] = {0};
    int fila[MAX_VERTICES];
    int inicio = 0, fim = 0;

    fila[fim++] = start_id;
    visitado[start_id] = 1;

    printf("BFS a partir da antena %d\n", start_id);

    while (inicio < fim) {
        int atual = fila[inicio++];
        printf("Visitado BFS: Antena %d [%c] em (%d,%d)\n",
               g->vertices[atual].id,
               g->vertices[atual].freq,
               g->vertices[atual].x,
               g->vertices[atual].y);

        Adj *adj = g->vertices[atual].lista;
        while (adj != NULL) {
            if (!visitado[adj->dest]) {
                fila[fim++] = adj->dest;
                visitado[adj->dest] = 1;
            }
            adj = adj->prox;
        }
    }
    return true;
}


/// @brief Função recursiva auxiliar para listar todos os caminhos entre duas antenas
/// @param g Apontador
/// @param atual Vértice atual
/// @param destino Vértice de destino
/// @param visitado Array de vértices já visitados
/// @param path Array com o caminho atual
/// @param path_len Comprimento atual do caminho
bool listarCaminhosAux(Grafo *g, int atual, int destino, int *visitado, int *path, int path_len) {
    visitado[atual] = 1;
    path[path_len++] = atual;

    if (atual == destino) {
        printf("Caminho: ");
        for (int i = 0; i < path_len; i++) {
            int id = path[i];
            printf("%d [%c](%d,%d)", id,
                   g->vertices[id].freq,
                   g->vertices[id].x,
                   g->vertices[id].y);
            if (i < path_len - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        Adj *adj = g->vertices[atual].lista;
        while (adj != NULL) {
            if (!visitado[adj->dest]) {
                listarCaminhosAux(g, adj->dest, destino, visitado, path, path_len);
            }
            adj = adj->prox;
        }
    }

    visitado[atual] = 0; // backtrack
}

/// @brief Lista todos os caminhos possíveis entre duas antenas com a mesma frequência
/// @param g Apontador
/// @param origem Antena de origem
/// @param destino Antena de destino
bool listarCaminhos(Grafo *g, int origem, int destino) {
    if (origem < 0 || origem >= g->n_vertices || destino < 0 || destino >= g->n_vertices) {
        printf("ID invalido.\n");
        return false;
    }

    if (g->vertices[origem].freq != g->vertices[destino].freq) {
        printf("Antenas com frequencias diferentes nao estao ligadas.\n");
        return false;
    }

    int visitado[MAX_VERTICES] = {0};
    int path[MAX_VERTICES];
    printf("Caminhos entre %d e %d:\n", origem, destino);
    listarCaminhosAux(g, origem, destino, visitado, path, 0);
    return true;
}


/**
 * @brief Lista todos os pares de antenas com frequências distintas A e B.
 *
 * @param g Apontador para o grafo.
 * @param freq1 Primeira frequência a considerar.
 * @param freq2 Segunda frequência a considerar.
 */
void listarIntersecoes(Grafo *g, char freq1, char freq2) {
    if (freq1 == freq2) {
        printf("As frequencias devem ser diferentes.\n");
        return;
    }

    printf("Intersecoes entre antenas com frequencias '%c' e '%c':\n", freq1, freq2);

    for (int i = 0; i < g->n_vertices; i++) {
        if (g->vertices[i].freq == freq1) {
            for (int j = 0; j < g->n_vertices; j++) {
                if (g->vertices[j].freq == freq2) {
                    printf("Antena [%c] em (%d,%d)  <->  Antena [%c] em (%d,%d)\n",
                           freq1, g->vertices[i].x, g->vertices[i].y,
                           freq2, g->vertices[j].x, g->vertices[j].y);
                }
            }
        }
    }
}

