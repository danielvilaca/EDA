/**
 * @file main.c
 * @author Daniel Vilaça (a16939@alunos.ipca.pt)
 * @brief
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */


#include <stdio.h>
#include "grafo.h"
#include "utils.h"

int main() {
    Grafo g;
    inicializaGrafo(&g);

    if (!carregarMatrizParaGrafo("matriz.txt", &g)) {
        printf("Falha ao carregar a matriz.\n");
        return 1;
    }

    int opcao, id;
    do {
        printf("\n------ Menu ------\n");
        printf("1. Imprimir grafo\n");
        printf("2. DFS a partir de antena\n");
        printf("3. BFS a partir de antena\n");
        printf("4. Listar caminhos entre duas antenas\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                imprimeGrafo(&g);
                break;
            case 2:
                printf("ID da antena de partida (0 a %d): ", g.n_vertices - 1);
                scanf("%d", &id);
                dfs(&g, id);
                break;
            case 3:
                printf("ID da antena de partida (0 a %d): ", g.n_vertices - 1);
                scanf("%d", &id);
                bfs(&g, id);
                break;
            case 4:
                printf("ID da antena origem (0 a %d): ", g.n_vertices - 1);
                scanf("%d", &id);
                int destino;
                printf("ID da antena destino (0 a %d): ", g.n_vertices - 1);
                scanf("%d", &destino);
                listarCaminhos(&g, id, destino);
                break;
            case 0:
                printf("A sair...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
