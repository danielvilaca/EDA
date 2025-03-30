/**
 * @file matriz.h
 * @author Daniel Vilaça (a16939@alunos.ipca.pt)
 * @brief
 * @version 1.0
 * @date 2025-03-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef MATRIZ_H
#define MATRIZ_H

#include "antena.h"


/**
 * @brief Estrutura de um nó da lista ligada de efeitos nefastos
 *
 */
typedef struct Node {
    int linha, coluna;
    struct Node *next;
} Node;


/**
 * @brief Exibe a matriz no terminal, com as antenas e os efeitos nefastos causados por pares de antenas com a mesma frequência
 *
 * @param listaAntenas Lista de antenas a serem exibidas
 * @param linhas Número de linhas da matriz
 * @param colunas Número de colunas da matriz
 */
void exibirMatriz(Antena *listaAntenas, int linhas, int colunas);

/**
 * @brief Gera efeitos nefastos causados por pares de antenas com a mesma frequência
 *
 * @param listaAntenas Apontador Lista de antenas
 * @param matriz Matriz onde serão marcados os efeitos ("#")
 * @param linhas Número de linhas da matriz
 * @param colunas Número de colunas da matriz
 */
void gerarEfeitosNefastos(Antena *listaAntenas, char matriz[][100], int linhas, int colunas);

/**
 * @brief Carrega uma matriz de um ficheiro, criando a lista de antenas a partir dos dados encontrados
 *
 * @param nomeFicheiro Path do ficheiro a ser carregado
 * @param listaAntenas Apontador para a lista de antenas
 * @param linhas Número de linhas da matriz
 * @param colunas Número de colunas da matriz
 */
void carregarMatrizDoFicheiro(const char *nomeFicheiro, Antena **listaAntenas, int *linhas, int *colunas);

/**
 * @brief Lista todas as posições afetadas por efeitos nefastos
 *
 * @param lista Apontador para a lista de efeitos nefastos
 */
void listarNefastos(Node *lista);



#endif
