/**
 * @file main.c
 * @author Daniel Vilaça (a16939@alunos.ipca.pt)
 * @brief
 * @version 1.0
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 */


#include <stdio.h>
#include <stdbool.h>
#include "grafo.h"
#include "utils.h"


/**
 * @brief 
 *
 * @param g
 */
static void clearFlags(Grafo *g) {
    for (Vertice *v = g->head; v; v = v->next) {
        v->visited = false;
    }
}


static void menu(void) {
    printf("\n------ Menu ------\n");
    printf("1. Carregar matriz de ficheiro\n");
    printf("2. Imprimir grafo\n");
    printf("3. DFS a partir de antena\n");
    printf("4. BFS a partir de antena\n");
    printf("5. Listar caminhos entre duas antenas\n");
    printf("6. Intersecoes entre duas frequencias distintas\n");
    printf("7. Adicionar antena\n");
    printf("8. Remover antena\n");
    printf("0. Sair\n");
    printf("Opcao: ");
}

int main(void) {
    Grafo g;
    inicializaGrafo(&g);

    int opcao;
    char filename[256];

    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Leitura de opcao falhou.\n");
            return 1;
        }

        switch (opcao) {
            case 1: {
                printf("Nome do ficheiro (ex: matriz.txt): ");
                scanf("%255s", filename);
                inicializaGrafo(&g);
                if (!carregarMatrizParaGrafo(filename, &g)) {
                    printf("Erro ao carregar matriz do ficheiro.\n");
                } else {
                    printf("Matriz carregada com %d antenas.\n", g.n_vertices);
                }
                break;
            }
            case 2:
                if (g.n_vertices == 0) {
                    printf("Grafo vazio.\n");
                } else {
                    imprimeGrafo(&g);
                }
                break;

            case 3: {
                int id;
                if (g.n_vertices == 0) {
                    printf("Grafo vazio.\n");
                    break;
                }
                printf("ID da antena de partida (0 a %d): ", g.n_vertices - 1);
                scanf("%d", &id);
                clearFlags(&g);
                if (!dfs(&g, id)) {
                    printf("Erro ao executar DFS. Verifique o ID introduzido.\n");
                }
                break;
            }

            case 4: {
                int id;
                if (g.n_vertices == 0) {
                    printf("Grafo vazio.\n");
                    break;
                }
                printf("ID da antena de partida (0 a %d): ", g.n_vertices - 1);
                scanf("%d", &id);
                clearFlags(&g);
                if (!bfs(&g, id)) {
                    printf("Erro ao executar BFS. Verifique o ID introduzido.\n");
                }
                break;
            }

            case 5: {
                int src, dst;
                if (g.n_vertices < 2) {
                    printf("Nao ha vertices suficientes.\n");
                    break;
                }
                printf("ID da antena origem (0 a %d): ", g.n_vertices - 1);
                scanf("%d", &src);
                printf("ID da antena destino (0 a %d): ", g.n_vertices - 1);
                scanf("%d", &dst);
                clearFlags(&g);
                if (!listarCaminhos(&g, src, dst)) {
                    printf("Nao foi possivel listar caminhos. IDs invalidos ou frequencias diferentes.\n");
                }
                break;
            }

            case 6: {
                char f1, f2;
                if (g.n_vertices < 2) {
                    printf("Nao ha vertices suficientes.\n");
                    break;
                }
                printf("Introduza a primeira frequencia: ");
                scanf(" %c", &f1);
                printf("Introduza a segunda frequencia: ");
                scanf(" %c", &f2);
                clearFlags(&g);
                listarIntersecoes(&g, f1, f2);
                break;
            }

            case 7: {
                int x, y;
                char freq;
                printf("Introduza a frequencia (caracter): ");
                scanf(" %c", &freq);
                printf("Coordenadas (x y): ");
                scanf("%d %d", &x, &y);

                int novo_id = adicionaVertice(&g, x, y, freq);
                if (novo_id < 0) {
                    printf("Falha ao inserir antena.\n");
                } else {

                    for (Vertice *v = g.head; v; v = v->next) {
                        if (v->id != novo_id && v->freq == freq) {
                            adicionaAresta(&g, novo_id, v->id);
                        }
                    }
                    printf("Antena inserida com ID %d.\n", novo_id);
                }
                break;
            }

            case 8: {
                int id;
                if (g.n_vertices == 0) {
                    printf("Grafo vazio.\n");
                    break;
                }
                printf("ID da antena a remover (0 a %d): ", g.n_vertices - 1);
                scanf("%d", &id);
                if (!removerVertice(&g, id)) {
                    printf("Antena não encontrada.\n");
                } else {
                    printf("Antena removida.\n");
                }
                break;
            }

            case 0:
                printf("A sair...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
