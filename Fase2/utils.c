/**
 * @file utils.c
 * @author Daniel Vilaça (a16939@alunos.ipca.pt)
 * @brief
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */


#include <stdio.h>
#include "utils.h"

/// @brief Lê uma matriz de antenas a partir do ficheiro de texto e constrói o grafo
/// @param filename Nome do ficheiro da matriz de antenas
/// @param g Apontador para o grafo a ser preenchido
/// @return Return 1 se o carregamento for bem-sucedido ou 0 em caso de erro
int carregarMatrizParaGrafo(const char *filename, Grafo *g) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Erro ao abrir o ficheiro.\n");
        return 0;
    }

    char linha[256];
    int y = 0;
    while (fgets(linha, sizeof(linha), fp)) {
        for (int x = 0; linha[x] != '\0' && linha[x] != '\n'; x++) {
            if (linha[x] != '.') {
                adicionaVertice(g, x, y, linha[x]);
            }
        }
        y++;
    }
    fclose(fp);

    // Arestas com mesma frequência
    for (int i = 0; i < g->n_vertices; i++) {
        for (int j = i + 1; j < g->n_vertices; j++) {
            if (g->vertices[i].freq == g->vertices[j].freq) {
                adicionaAresta(g, i, j);
            }
        }
    }

    return 1;
}
