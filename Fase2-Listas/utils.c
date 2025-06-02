/**
 * @file utils.c
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
#include "utils.h"
#include "grafo.h"


/**
 * @brief Carrega uma “matriz” de antenas de um ficheiro e constrói o grafo.
 *
 * @param filename Nome do ficheiro (.txt) que contém a matriz.
 * @param g Apontador para o grafo que será preenchido com vértices e arestas.
 * @return true Se o ficheiro foi aberto corretamente e o grafo foi construído.
 * @return false Se ocorrer erro ao abrir o ficheiro ou falha de alocação ao adicionar vértice.
 */
bool carregarMatrizParaGrafo(const char *filename, Grafo *g) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Erro ao abrir o ficheiro.\n");
        return false;
    }

    char linha[512];
    int y = 0;

    while (fgets(linha, sizeof linha, fp)) {
        for (int x = 0; linha[x] != '\0' && linha[x] != '\n'; x++) {
            if (linha[x] != '.') {
                if (adicionaVertice(g, x, y, linha[x]) < 0) {
                    fclose(fp);
                    return false;
                }
            }
        }
        y++;
    }
    fclose(fp);

    
    for (Vertice *v = g->head; v; v = v->next) {
        for (Vertice *w = v->next; w; w = w->next) {
            if (v->freq == w->freq) {
                adicionaAresta(g, v->id, w->id);
            }
        }
    }

    return true;
}
