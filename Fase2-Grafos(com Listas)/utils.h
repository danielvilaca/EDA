/**
 * @file utils.h
 * @author Daniel Vilaça (a16939@alunos.ipca.pt)
 * @brief
 * @version 1.0
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 */


#ifndef UTILS_H
#define UTILS_H

#include "grafo.h"


/**
 * @brief Lê um ficheiro-texto contendo uma matriz de antenas e preenche o grafo.
 *
 * @param filename Nome do ficheiro (.txt) que contém a matriz de antenas.
 * @param g Apontador para o grafo que será preenchido com vértices e arestas.
 * @return true Se o ficheiro for aberto e processado com sucesso.
 * @return false Se ocorrer erro ao abrir o ficheiro ou falha de alocação ao adicionar vértice.
 */
bool carregarMatrizParaGrafo(const char *filename, Grafo *g);

#endif
