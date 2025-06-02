#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "grafo.h"

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
