#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

static Vertice *getVerticePorID(Grafo *g, int id) {
    for (Vertice *v = g->head; v; v = v->next) {
        if (v->id == id) return v;
    }
    return NULL;
}


static bool arestaExiste(const Vertice *src, const Vertice *dest) {
    for (Adj *a = src->lista; a; a = a->prox) {
        if (a->dest == dest) return true;
    }
    return false;
}


static void removerArestaDireta(Vertice *src, Vertice *dest) {
    Adj *prev = NULL, *cur = src->lista;
    while (cur) {
        if (cur->dest == dest) {
            if (prev) prev->prox = cur->prox;
            else       src->lista = cur->prox;
            free(cur);
            return;
        }
        prev = cur;
        cur  = cur->prox;
    }
}


static void clearVisited(Grafo *g) {
    for (Vertice *v = g->head; v; v = v->next) {
        v->visited = false;
    }
}


void inicializaGrafo(Grafo *g) {
    g->head = NULL;
    g->n_vertices = 0;
}

int adicionaVertice(Grafo *g, int x, int y, char freq) {
    Vertice *novo = malloc(sizeof *novo);
    if (!novo) return -1;

    novo->id       = g->n_vertices;
    novo->x        = x;
    novo->y        = y;
    novo->freq     = freq;
    novo->lista    = NULL;
    novo->visited  = false;

    novo->next     = g->head;
    g->head        = novo;
    g->n_vertices++;

    return novo->id;
}

bool adicionaAresta(Grafo *g, int orig_id, int dest_id) {
    Vertice *v1 = getVerticePorID(g, orig_id);
    Vertice *v2 = getVerticePorID(g, dest_id);
    if (!v1 || !v2) return false;
    if (v1->freq != v2->freq) return false;
    if (v1 == v2) return false;
    if (arestaExiste(v1, v2)) return true;


    Adj *a1 = malloc(sizeof *a1);
    if (!a1) return false;
    a1->dest = v2;
    a1->prox = v1->lista;
    v1->lista = a1;


    Adj *a2 = malloc(sizeof *a2);
    if (!a2) {

        Adj *undo = v1->lista;
        v1->lista = undo->prox;
        free(undo);
        return false;
    }
    a2->dest = v1;
    a2->prox = v2->lista;
    v2->lista = a2;

    return true;
}

void imprimeGrafo(Grafo *g) {

    for (int i = 0; i < g->n_vertices; i++) {
        Vertice *v = getVerticePorID(g, i);
        if (!v) continue;
        printf("Antena %d [%c] em (%d,%d) -> ",
               v->id, v->freq, v->x, v->y);
        for (Adj *a = v->lista; a; a = a->prox) {
            printf("%d ", a->dest->id);
        }
        printf("\n");
    }
}

static void dfs_rec(Vertice *v) {
    v->visited = true;
    printf("Visitado DFS: Antena %d [%c] em (%d,%d)\n",
           v->id, v->freq, v->x, v->y);
    for (Adj *a = v->lista; a; a = a->prox) {
        if (!a->dest->visited) {
            dfs_rec(a->dest);
        }
    }
}

bool dfs(Grafo *g, int start_id) {
    Vertice *start = getVerticePorID(g, start_id);
    if (!start) {
        printf("ID invalido.\n");
        return false;
    }
    clearVisited(g);
    printf("DFS a partir da antena %d\n", start_id);
    dfs_rec(start);
    return true;
}

bool bfs(Grafo *g, int start_id) {
    Vertice *start = getVerticePorID(g, start_id);
    if (!start) {
        printf("ID invalido.\n");
        return false;
    }
    clearVisited(g);


    Vertice **fila = malloc(sizeof(Vertice *) * g->n_vertices);
    if (!fila) return false;

    int ini = 0, fim = 0;
    fila[fim++] = start;
    start->visited = true;
    printf("BFS a partir da antena %d\n", start_id);

    while (ini < fim) {
        Vertice *v = fila[ini++];
        printf("Visitado BFS: Antena %d [%c] em (%d,%d)\n",
               v->id, v->freq, v->x, v->y);
        for (Adj *a = v->lista; a; a = a->prox) {
            if (!a->dest->visited) {
                a->dest->visited = true;
                fila[fim++] = a->dest;
            }
        }
    }

    free(fila);
    return true;
}


static void listarCaminhosRec(Vertice *cur, Vertice *dst,
                              Vertice **stack, int depth) {
    cur->visited = true;
    stack[depth] = cur;

    if (cur == dst) {
        printf("Caminho: ");
        for (int i = 0; i <= depth; i++) {
            printf("%d [%c](%d,%d)",
                   stack[i]->id,
                   stack[i]->freq,
                   stack[i]->x,
                   stack[i]->y);
            if (i < depth) printf(" -> ");
        }
        printf("\n");
    } else {
        for (Adj *a = cur->lista; a; a = a->prox) {
            if (!a->dest->visited) {
                listarCaminhosRec(a->dest, dst, stack, depth + 1);
            }
        }
    }

    cur->visited = false; // backtrack
}

bool listarCaminhos(Grafo *g, int origem, int destino) {
    Vertice *src = getVerticePorID(g, origem);
    Vertice *dst = getVerticePorID(g, destino);
    if (!src || !dst) {
        printf("ID invalido.\n");
        return false;
    }
    if (src->freq != dst->freq) {
        printf("Antenas com frequencias diferentes nao estao ligadas.\n");
        return false;
    }

    clearVisited(g);
    Vertice **stack = malloc(sizeof(Vertice *) * g->n_vertices);
    if (!stack) return false;

    printf("Caminhos entre %d e %d:\n", origem, destino);
    listarCaminhosRec(src, dst, stack, 0);
    free(stack);
    return true;
}

void listarIntersecoes(Grafo *g, char freq1, char freq2) {
    if (freq1 == freq2) {
        printf("As frequencias devem ser diferentes.\n");
        return;
    }
    printf("Intersecoes entre antenas com frequencias '%c' e '%c':\n",
           freq1, freq2);

    for (Vertice *v = g->head; v; v = v->next) {
        if (v->freq == freq1) {
            for (Vertice *w = g->head; w; w = w->next) {
                if (w->freq == freq2) {
                    printf("Antena [%c] em (%d,%d)  <->  Antena [%c] em (%d,%d)\n",
                           freq1, v->x, v->y,
                           freq2, w->x, w->y);
                }
            }
        }
    }
}

bool removerVertice(Grafo *g, int id) {
    Vertice *alvo = getVerticePorID(g, id);
    if (!alvo) return false;

    for (Vertice *v = g->head; v; v = v->next) {
        if (v != alvo) {
            removerArestaDireta(v, alvo);
        }
    }

    Adj *a = alvo->lista;
    while (a) {
        Adj *aux = a->prox;
        free(a);
        a = aux;
    }

    Vertice *prev = NULL, *cur = g->head;
    while (cur) {
        if (cur == alvo) {
            if (prev) prev->next = cur->next;
            else      g->head = cur->next;
            free(cur);
            break;
        }
        prev = cur;
        cur  = cur->next;
    }

    g->n_vertices--;

    int contador = 0;
    for (Vertice *v = g->head; v; v = v->next) {
        v->id = contador++;
    }

    return true;
}
