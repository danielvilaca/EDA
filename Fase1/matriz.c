/**
 * @file matriz.c
 * @author Daniel Vilaça (a16939@alunos.ipca.pt)
 * @brief
 * @version 1.0
 * @date 2025-03-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "matriz.h"


/**
 * @brief Insere uma posição nefasta na lista ligada
 *
 * @param aux Apontador para o apontador da lista de efeitos nefastos
 * @param linha Linha da célula afetada
 * @param coluna Coluna da célula afetada
 */
void inserirNefasto(Node **aux, int linha, int coluna) {
    for (Node *n = *aux; n != NULL; n = n->next)
        if (n->linha == linha && n->coluna == coluna) return;

    Node *novo = (Node *)malloc(sizeof(Node));
    novo->linha = linha;
    novo->coluna = coluna;
    novo->next = *aux;
    *aux = novo;
}


/**
 * @brief Exibe a matriz no terminal, com as antenas e os efeitos nefastos causados por pares de antenas com a mesma frequência
 *
 * @param listaAntenas Lista de antenas a serem exibidas
 * @param linhas Número de linhas da matriz
 * @param colunas Número de colunas da matriz
 */
void exibirMatriz(Antena *listaAntenas, int linhas, int colunas) {
    char matriz[100][100]; // Máximo

    // Inicializar matriz com '.'
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            matriz[i][j] = '.';

    // Antenas na matriz
    for (Antena *a = listaAntenas; a != NULL; a = a->next)
        matriz[a->linha][a->coluna] = a->freq;

    // Gerar efeitos nefastos
    gerarEfeitosNefastos(listaAntenas, matriz, linhas, colunas);

    // Exibir matriz
    //setlocale(LC_ALL, "C");
    printf("\nMatriz:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++)
            printf("%c", matriz[i][j]);
        printf("\n");
    }

    // Listar antenas
    printf("\nAntenas:\n");
    for (Antena *a = listaAntenas; a != NULL; a = a->next)
        printf("Frequencia: %c | Linha: %d | Coluna: %d\n", a->freq, a->linha + 1, a->coluna + 1);

    // Listar efeitos nefastos
    printf("\nEfeitos nefastos:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == '#') {
                printf("Efeito\t\t| Linha: %d\t| Coluna: %d\n", i + 1, j + 1);
            }
        }
    }
}


/**
 * @brief Gera efeitos nefastos causados por pares de antenas com a mesma frequência
 *
 * @param listaAntenas Apontador Lista de antenas
 * @param matriz Matriz onde serão marcados os efeitos ("#")
 * @param linhas Número de linhas da matriz
 * @param colunas Número de colunas da matriz
 */
void gerarEfeitosNefastos(Antena *listaAntenas, char matriz[][100], int linhas, int colunas) {
    for (Antena *a1 = listaAntenas; a1 != NULL; a1 = a1->next) {
        for (Antena *a2 = a1->next; a2 != NULL; a2 = a2->next) {
            if (a1->freq == a2->freq) {
                int dx = a2->linha - a1->linha;
                int dy = a2->coluna - a1->coluna;

                // Geração antes da primeira antena
                int linhaAntes = a1->linha - dx;
                int colunaAntes = a1->coluna - dy;
                if (linhaAntes >= 0 && linhaAntes < linhas &&
                    colunaAntes >= 0 && colunaAntes < colunas) {
                    matriz[linhaAntes][colunaAntes] = '#';
                }

                // Geração depois da segunda antena
                int linhaDepois = a2->linha + dx;
                int colunaDepois = a2->coluna + dy;
                if (linhaDepois >= 0 && linhaDepois < linhas &&
                    colunaDepois >= 0 && colunaDepois < colunas) {
                    matriz[linhaDepois][colunaDepois] = '#';
                }
            }
        }
    }
}


/**
 * @brief Carrega uma matriz de um ficheiro, criando a lista de antenas a partir dos dados encontrados
 *
 * @param nomeFicheiro Path do ficheiro a ser carregado
 * @param aux Apontador para a lista onde as antenas serão armazenadas
 * @param linhas Apontador para armazenar o número de linhas da matriz carregada
 * @param colunas Apontador para armazenar o número de colunas da matriz carregada
 */
void carregarMatrizDoFicheiro(const char *nomeFicheiro, Antena **aux, int *linhas, int *colunas) {
    FILE *file = fopen(nomeFicheiro, "r");
    if (!file) {
        perror("Erro ao abrir ficheiro");
        exit(1);
    }

    char linha[256];
    int i = 0, maxCol = 0;
    while (fgets(linha, sizeof(linha), file)) {
        int j;
        for (j = 0; linha[j] != '\0' && linha[j] != '\n'; j++) {
            if (linha[j] != '.')
                inserirAntena(aux, linha[j], i, j);
        }
        if (j > maxCol) maxCol = j;
        i++;
    }
    *linhas = i;
    *colunas = maxCol;
    fclose(file);
}


/**
 * @brief Lista todas as posições afetadas por efeitos nefastos
 *
 * @param aux Lista ligada de posições nefastas
 */
void listarNefastos(Node *aux) {
    //setlocale(LC_ALL, "C");
    printf("%-10s %-10s\n", "Linha", "Coluna");
    printf("%-10s %-10s\n", "-----", "------");
    for (; aux; aux = aux->next)
        printf("%-10d %-10d\n", aux->linha, aux->coluna);
}


