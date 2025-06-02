/**
 * @file grafo.c
 * @author Daniel Vilaça (a16939@alunos.ipca.pt)
 * @brief
 * @version 1.0
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


/**
 * @brief Procura um vértice pelo seu ID dentro do grafo.
 *
 * @param g Apontador para o grafo onde se faz a procura.
 * @param id Identificador do vértice a ser encontrado.
 * @return Vertice* Apontador para o vértice encontrado, ou NULL se não existir.
 */
static Vertice *getVerticePorID(Grafo *g, int id) {
    for (Vertice *v = g->head; v; v = v->next) {
        if (v->id == id) return v;
    }
    return NULL;
}

/**
 * @brief Verifica se já existe uma aresta entre dois vértices.
 *
 * @param src Apontador para o vértice de origem.
 * @param dest Apontador para o vértice de destino.
 * @return true Se já existir uma aresta de src para dest.
 * @return false Caso não exista essa adjacência.
 */
static bool arestaExiste(const Vertice *src, const Vertice *dest) {
    for (Adj *a = src->lista; a; a = a->prox) {
        if (a->dest == dest) return true;
    }
    return false;
}

/**
 * @brief Remove a aresta direta de um vértice de origem para um vértice de destino.
 *
 * @param src Apontador para o vértice de origem.
 * @param dest Apontador para o vértice de destino cujas ligações devem ser removidas.
 */
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

/**
 * @brief Limpa a flag de visited de todos os vértices do grafo.
 *
 * @param g Apontador para o grafo cujos vértices terão a flag limpo.
 */
static void clearVisited(Grafo *g) {
    for (Vertice *v = g->head; v; v = v->next) {
        v->visited = false;
    }
}


/**
 * @brief Inicializa o grafo como vazio.
 *
 * @param g Apontador para o grafo a ser inicializado.
 */
void inicializaGrafo(Grafo *g) {
    g->head = NULL;
    g->n_vertices = 0;
}


/**
 * @brief Adiciona um novo vértice/antena ao grafo.
 *
 * @param g Apontador para o grafo onde o vértice será inserido.
 * @param x Coordenada x (coluna) da antena.
 * @param y Coordenada y (linha) da antena.
 * @param freq Char que representa a frequência/identificador da antena.
 * @return int ID atribuído ao novo vértice, ou -1 em caso de erro de alocação.
 */
int adicionaVertice(Grafo *g, int x, int y, char freq) {
    Vertice *novo = malloc(sizeof *novo);
    if (!novo) return -1;

    novo->id       = g->n_vertices;
    novo->x        = x;
    novo->y        = y;
    novo->freq     = freq;
    novo->lista    = NULL;
    novo->visited  = false;

    // Cabeça da lista
    novo->next     = g->head;
    g->head        = novo;
    g->n_vertices++;

    return novo->id;
}


/**
 * @brief Adiciona uma aresta entre dois vértices.
 *
 * @param g Apontador para o grafo que contém os vértices.
 * @param orig_id ID do vértice de origem.
 * @param dest_id ID do vértice de destino.
 * @return true Se a aresta for criada com sucesso ou já existir.
 * @return false Se "orig_id" ou "dest_id" forem inválidos, frequências diferentes, mesmo vértice, ou falha de memória.
 */
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


/**
 * @brief Imprime o grafo em formato legível.
 *
 * @param g Apontador para o grafo a ser impresso.
 */
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


/**
 * @brief Função recursiva auxiliar para Depth-First Search (DFS).
 *
 * @param v Apontador para o vértice atual na recursão.
 */
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


/**
 * @brief Executa Depth-First Search (DFS) a partir de um vértice dado.
 *
 * @param g Apontador para o grafo onde será feita a DFS.
 * @param start_id ID do vértice inicial da procura.
 * @return true Se a procura for executada (mesmo que encontre apenas um vértice).
 * @return false Se "start_id" não corresponder a nenhum vértice existente.
 */
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


/**
 * @brief Executa Breadth-First Search (BFS) a partir de um vértice dado.
 *
 * @param g Apontador para o grafo onde será feita a BFS.
 * @param start_id Identificador do vértice inicial da procura.
 * @return true Se a procura for executada (mesmo que visite apenas um vértice).
 * @return false Se `start_id` não corresponder a nenhum vértice ou falhar alocação.
 */
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


/**
 * @brief Função recursiva auxiliar para listar todos os caminhos simples entre dois vértices.
 *
 * @param cur Apontador para o vértice atual na recursão.
 * @param dst Apontador para o vértice de destino final.
 * @param stack Vetor de Apontadors para Vertice que armazena o caminho atual.
 * @param depth Profundidade/índice atual em `stack`.
 */
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


/**
 * @brief Lista todos os caminhos simples entre dois vértices de mesma frequência.
 *
 * @param g Apontador para o grafo onde serão procurados os caminhos.
 * @param origem ID do vértice de origem.
 * @param destino ID do vértice de destino.
 * @return true Se os caminhos foram listados (ou se pelo menos tentativa foi válida).
 * @return false Se IDs inválidos ou frequências diferentes.
 */
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


/**
 * @brief Lista todas as combinações de pares de antenas de frequências distintas.
 *
 * @param g Apontador para o grafo onde se procura as interseções.
 * @param freq1 Char da primeira frequência.
 * @param freq2 Char da segunda frequência.
 */
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


/**
 * @brief Remove um vértice do grafo, junto com todas as arestas incidentes.
 *
 * @param g Apontador para o grafo onde está o vértice.
 * @param id Identificador do vértice a ser removido.
 * @return true Se o vértice existia e foi removido com sucesso.
 * @return false Se não houver vértice com esse ID.
 */
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
